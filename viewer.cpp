#include "viewer.h"

Viewer::Viewer(QWidget* parent)
    : QWidget(parent)
    , m_pRenderer(vtkSmartPointer<vtkRenderer>::New())
{
}

Viewer::~Viewer() {}

// int Viewer::setLogic(Logic *pLogic) {
//     m_pLogic = pLogic;
//     return 0; 
// }

int Viewer::initViewer(QVTKWidget* pVTKWidget) { 
  if(setVTKWidget(pVTKWidget) == -1){
    qDebug() << __FUNCTION__ << "setVTKWidget failed!"; 
    return -1;
  }

  if(m_pRenderer == nullptr){
    qDebug() << __FUNCTION__ << "m_pRenderer is nullptr!";
    return -1;
  }

  m_pRenderer->SetUseDepthPeeling(1);
  m_pRenderer->SetMaximumNumberOfPeels(100);
  m_pRenderer->SetOcclusionRatio(0.1);

  // set QVTKWidget renderer
  m_pVTKWidget->GetRenderWindow()->AddRenderer(m_pRenderer);
  // vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	// interactor->SetRenderWindow(m_pVTKWidget->GetRenderWindow());
  // interactor->Start();
  // set background color
  // if(m_pRenderer != nullptr){
  //   m_pRenderer->SetBackground(255, 255, 255);
  // }
  return 0;
} 
// }void Viewer::showModelSlot(Model& model){
//   qDebug() << __FUNCTION__ << "show model";
//   appendModel2Screen(model);
// }


// int Viewer::show() {
//   vtkSmartPointer<vtkPolyData> pData = vtkSmartPointer<vtkPolyData>::New();
//   if (readModel("~/stlfiles/Bunny-LowPoly.stl") == -1) {
//     qDebug() << "readModel failed!";
//   }
//   return showModel();
// }

// int Viewer::show(){
//   if(m_pVTKWidget != nullptr){
//     m_pVTKWidget->GetRenderWindow()->Render();
//     return 0;
//   }else{
//     qDebug() << __FUNCTION__ << "m_pVTKWidget is nullptr! Can't show!";
//     return -1;
//   }
// }

int Viewer::appendModel2Screen(QVector<Model*> vModels) { 
  qDebug() << __FUNCTION__ << QString("vModels.size = %1").arg(vModels.size());
  for(int i = 0; i < vModels.size(); ++i){
    if(appendModel2Screen(vModels.at(i)) != 0){
      qDebug() << __FUNCTION__ << QString("%1 append to screen failed!").arg(vModels.at(i)->sModelName);
    }else{
      qDebug() << __FUNCTION__ << QString("%1 append to screen success!").arg(vModels.at(i)->sModelName);
    }
  }
  return 0; 
}

int Viewer::appendModel2Screen(Model* pModel) {
  if(m_pRenderer == nullptr){
    qDebug() << __FUNCTION__ << "m_pRender is nullptr!";
    return -1;
  }
  m_pRenderer->AddActor(pModel->m_pActor);
  if(m_pVTKWidget == nullptr){
    qDebug() << __FUNCTION__ << "m_pVTKWidget is nullptr!";
    return -1;
  }
  m_pRenderer->SetBackground(0.2, 0.3, 0.4);
  m_pVTKWidget->GetRenderWindow()->Render();
  return 0;
}

// int Viewer::showModel() {
//   vtkSmartPointer<vtkPolyDataMapper> mapper =
//       vtkSmartPointer<vtkPolyDataMapper>::New();
//   mapper->SetInputConnection(m_pSTLReader->GetOutputPort());

//   vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//   actor->SetMapper(mapper);

//   m_pRenderer->AddActor(actor);

//   if (m_pVTKWidget != nullptr) {
//     m_pVTKWidget->GetRenderWindow()->AddRenderer(m_pRenderer);
//     m_pVTKWidget->GetRenderWindow()->Render();
//     return 0;
//   } else {
//     return -1;
//   }
// }

// int Viewer::appendModel2Screen(Model* model) {
//   if(m_CurViewMap.find(model.getModelName()) != m_CurViewMap.end()){
//     /*-------------------------------------*/
//     /*-------------------------------------*/
//     /*-------------------------------------*/
//     /*------ Waiting for modify -----------*/
//     QString sName = model.getModelName();
//     int index = sName.lastIndexOf('_');
//     if(index == -1){
//       // no '_'
//       sName = sName + QString("_2");
//     }else if(index+1 < sName.size()){
//       int start = index+1;
//       int end = sName.lastIndexOf('.');
//       int num = sName.mid(start, end-start).toInt();
//       num++;
//       sName = sName + QString("_%1").arg(num);
//     }
//     model.setModelName(sName);
//     /*-------------------------------------*/
//     /*-------------------------------------*/
//     /*-------------------------------------*/
//   }
//   m_CurViewMap.insert(model.getModelName(), model); // insert to map

//   // init m_pVTKWidget
//   vtkSmartPointer<vtkActor> pActor;
//   int nRet = model.getActor(pActor);
//   if(nRet == -1){
//     qDebug() << __FUNCTION__ << "Can't get Actor!";
//     return -1;
//   }
//   if(m_pRenderer == nullptr){
//     qDebug() << __FUNCTION__ << "Render is nullptr!";
//     return -1;
//   }
//   m_pRenderer->AddActor(pActor);

//   if(m_pVTKWidget != nullptr){
//     m_pVTKWidget->GetRenderWindow()->Render();
//     return 0;
//   }else{
//     qDebug() << __FUNCTION__ << "m_pVTKWidget is nullptr! Can't show!";
//     return -1;
//   }

  // return this->show(); 
// }

// int Viewer::readModel(QString sPath) { 
//   // read stl file
//   if(m_pSTLReader == nullptr){
//     qDebug() << "vtkSTLReader hasn't been initialized!";
//     return -1;
//   }
//   m_pSTLReader->SetFileName(sPath.toStdString().c_str());
  
//   return 0;
// }

int Viewer::setVTKWidget(QVTKWidget* pVTKWidget) {
  m_pVTKWidget = pVTKWidget;
  if(m_pVTKWidget == nullptr){
    qDebug() << __FUNCTION__ << "VTKWidget is nullptr";
    return -1;
  }
  return 0; 
}

// void Viewer::showModelSlot(Model& model){
//   qDebug() << __FUNCTION__ << "show model";
//   appendModel2Screen(model);
// }
