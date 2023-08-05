#include "viewInteractStyle.h"

ViewInteractorStyle::ViewInteractorStyle()
  // : m_pOutline(vtkSmartPointer<vtkOutlineFilter>::New())
  // , m_pInteractor(vtkSmartPointer<vtkRenderWindowInteractor>::New())
  // , m_pPicker(vtkSmartPointer<vtkPropPicker>::New())
{
  // m_pInteractor->SetPicker(m_pPicker);
  // this->SetInteractor(m_pInteractor);
}

int ViewInteractorStyle::SetRenderer(vtkSmartPointer<vtkRenderer> pRenderer) {
  m_pRenderer = pRenderer;
  return 0;
}

void ViewInteractorStyle::OnLeftButtonDown() {
  auto currentTime = QDateTime::currentMSecsSinceEpoch();
  auto duration = currentTime - this->LastClickTime;
  if(duration < 500){
    int* pos = GetInteractor()->GetEventPosition();
    vtkSmartPointer<vtkPropPicker> pPicker = vtkSmartPointer<vtkPropPicker>::New();
    pPicker->Pick(pos[0], pos[1], 0, m_pRenderer);
    vtkActor* pActor = pPicker->GetActor();
    if(pActor != nullptr){
      if(pLastActor != pActor && pLastActor != nullptr){
        pLastActor->GetProperty()->SetColor(0.5, 0.5, 0.5);
        m_pBridge->CallDeactivateItemSig(pLastActor);
      }
      // qDebug() << __FUNCTION__ << pActor->GetPropertyKeys()->Get(ViewerControl::pCustomKey);
      pLastActor = pActor;
      pActor->GetProperty()->SetColor(1, 1, 0);
      m_pBridge->CallActivateItemSig(pLastActor);
      m_pRenderer->GetActiveCamera()->SetFocalPoint(pActor->GetCenter());
      double* p = m_pRenderer->GetActiveCamera()->GetPosition();
      qDebug() << QString("Camera Position: %1, %2, %3").arg(p[0]).arg(p[1]).arg(p[2]);
      m_pRenderer->GetRenderWindow()->Render();
    }
  }
  this->LastClickTime = currentTime;

  vtkInteractorStyleTrackballActor::OnLeftButtonDown();
}

void ViewInteractorStyle::SetBridge(Bridge * pBridge)
{
  m_pBridge = pBridge;
}

void ViewInteractorStyle::PickMesh(int x, int y) {

}

void ViewInteractorStyle::PickModel(int x, int y) {
}
