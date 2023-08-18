#include "viewerControl.h"

vtkInformationStringKey* ViewerControl::pCustomKey = vtkInformationStringKey::MakeKey("MyCustomKey", "ModelName");

ViewerControl::ViewerControl(QWidget* parent, ModelManager* pModelMgr, Bridge* pBridge)
  : QVTKOpenGLNativeWidget(parent)
  , m_pRenderWindow(this->GetRenderWindow())
  , m_pRenderWindowInteractor(this->GetInteractor())
  // , m_pReader(vtkSmartPointer<vtkSTLReader>::New())
  , m_pRenderer(vtkSmartPointer<vtkRenderer>::New())
  , m_pProperty(vtkSmartPointer<vtkProperty>::New())
  , m_pPNGWriter(vtkSmartPointer<vtkPNGWriter>::New())
  , m_pWindowToImageFilter(vtkSmartPointer<vtkWindowToImageFilter>::New())
  , m_pChosenActor(nullptr)
  , m_pViewInteractorStyle(new ViewInteractorStyle())
  , m_pModelMgr(pModelMgr)
  , m_pPlaneSource(vtkSmartPointer<vtkPlaneSource>::New())
  , m_pBridge(new Bridge())
  // , m_pInteractorStyleTrackballCamera(vtkInteractorStyleTrackballCamera::New())
  // , m_pAxesActor(vtkSmartPointer<vtkAxesActor>::New())
  , m_pCustomWidget(vtkCustomWidget::New())
{
  m_pRenderWindow->AddRenderer(m_pRenderer);
  m_pRenderWindowInteractor->SetRenderWindow(m_pRenderWindow);
  m_pViewInteractorStyle->SetRenderer(m_pRenderer);
  m_pViewInteractorStyle->SetCustomWidget(m_pCustomWidget);
  // m_pViewInteractorStyle->SetModelMgr(m_pModelMgr);
  m_pViewInteractorStyle->SetBridge(m_pBridge);
  // m_pRenderWindowInteractor->SetInteractorStyle(m_pInteractorStyleTrackballCamera);

  // 拾取开启
  m_pRenderWindowInteractor->SetInteractorStyle(m_pViewInteractorStyle);

  m_pProperty->SetEdgeColor(0, 0, 0);
	m_pProperty->SetEdgeVisibility(0);
	m_pProperty->VertexVisibilityOff();
	m_pProperty->SetBackfaceCulling(false);
	m_pProperty->SetAmbientColor(0.8,0.8,0.8);
	m_pProperty->SetAmbient(0.5);
	m_pProperty->SetDiffuse(0.5);
	// m_pProperty->SetColor(m_color.redF(), m_color.greenF(), m_color.blueF());
  m_pProperty->SetColor(0.5, 0.5, 0.5);

  InitViewer();
}

ViewerControl::~ViewerControl(){
  if(m_pRenderWindow != nullptr){
    m_pRenderWindow = nullptr;
  }
  
  if(m_pRenderWindowInteractor != nullptr){
    m_pRenderWindowInteractor = nullptr;
  }

  if(m_pModelMgr != nullptr){
    m_pModelMgr = nullptr;
  }
}

// void myfunc(vtkObject* caller, unsigned long eid, void* clientdata, void* calldata){
//   qDebug() << "6";
// }

int ViewerControl::InitViewer(ModelManager* pModelMgr) {
  if(pModelMgr != nullptr){
    m_pModelMgr = pModelMgr;
  }

  m_pRenderer->SetBackground(1, 1, 1);         // bottm
  m_pRenderer->SetBackground2(0.8, 0.8, 0.8);  // top
  m_pRenderer->SetGradientBackground(true);
  
  // camera
	vtkCamera *camera = m_pRenderer->GetActiveCamera();
  double* p = camera->GetPosition();
  qDebug() << QString("Camera Position: %1, %2, %3").arg(p[0]).arg(p[1]).arg(p[2]);
	// camera->SetParallelProjection(1);

  // m_pCustomWidget->SetInteractor(m_pRenderWindowInteractor);

  // InitGridRaft();
  InitCoords();

  // test
  // m_pSphere = vtkSphereSource::New();
  // m_pSphere->SetRadius(10);
  // m_pSphereMapper = vtkPolyDataMapper::New();
  // m_pSphereActor = vtkActor::New();

  // m_pSphereMapper->SetInputConnection(m_pSphere->GetOutputPort());
  // m_pSphereActor->SetMapper(m_pSphereMapper);
  // m_pRenderer->AddActor(m_pSphereActor);

  return 0;
}

int ViewerControl::InitGridRaft() { 
  vtkSmartPointer<vtkPlaneSource> m_pPlaneSource = vtkSmartPointer<vtkPlaneSource>::New();
  m_pPlaneSource->SetXResolution(10);
  m_pPlaneSource->SetYResolution(10);
  m_pPlaneSource->SetOrigin(0, 0, 0);
  m_pPlaneSource->SetPoint1(1000, 0, 0);
  m_pPlaneSource->SetPoint2(0, 1000, 0);

  vtkSmartPointer<vtkPolyDataMapper> pMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  pMapper->SetInputConnection(m_pPlaneSource->GetOutputPort());

  vtkSmartPointer<vtkActor> pActor = vtkSmartPointer<vtkActor>::New();
  pActor->SetMapper(pMapper);
  pActor->GetProperty()->SetEdgeColor(0, 0, 0);
  pActor->GetProperty()->SetLineWidth(2);
  pActor->GetProperty()->LightingOff();
  pActor->GetProperty()->SetOpacity(0.5);
  pActor->GetProperty()->EdgeVisibilityOn();
  double* coord = pActor->GetCenter();
  pActor->SetPosition(-coord[0], -coord[1], -coord[2]);
  // pActor->PickableOff();

  // m_pBoxWidget = vtkSmartPointer<vtkBoxWidget>::New();
  // m_pBoxWidget->SetInteractor(m_pRenderWindowInteractor);
  // m_pBoxWidget->SetProp3D(pActor);
  // m_pBoxWidget->On();
  
  /*----------------------test-------------------------------*/
  // vtkSmartPointer<vtkRegularPolygonSource> circle = vtkSmartPointer<vtkRegularPolygonSource>::New();
  // circle->SetRadius(100);
  // circle->SetNumberOfSides(100);
  // circle->SetCenter(0, 0, 0);
  // vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  // mapper->SetInputConnection(circle->GetOutputPort());
  // vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  // actor->SetMapper(mapper);
  // actor->GetProperty()->SetColor(1, 0, 1);
  // m_pRenderer->AddActor(actor);
  /*-----------------------------------------------------*/
  
  m_pRenderer->AddActor(pActor);
  m_pRenderer->ResetCamera();
  m_pRenderWindow->Render();
  return 0; 
}

int ViewerControl::InitCoords() { 
  m_pAxesActor = vtkSmartPointer<vtkAxesActor>::New();
  m_pWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  m_pWidget->SetOutlineColor(0.93, 0.57, 0.13);
  m_pWidget->SetOrientationMarker(m_pAxesActor);
  m_pWidget->SetInteractor(m_pRenderWindowInteractor);
  m_pWidget->SetViewport(0.0, 0.0, 0.4, 0.4);
  m_pWidget->SetEnabled(1);
  m_pWidget->InteractiveOn();
  return 0; 
}

int ViewerControl::InitBoxWidget() { 
  // vtkSmartPointer<vtkBoxWidget> boxWidget = vtkSmartPointer<vtkBoxWidget>::New();
  // boxWidget->SetInteractor(m_pRenderWindowInteractor);
  // boxWidget->SetProp3D();
  // boxWidget->On();

  // vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
  // boxWidget->AddObserver(vtkCommand::InteractionEvent, [&transform, &boxWidget](vtkObject* caller, unsigned long eventId, void* clientData, void* callData) {
  //     boxWidget->GetTransform(transform);
  //     boxWidget->GetProp3D()->SetUserTransform(transform);
  // });
  return 0;
}

int ViewerControl::InitCustomWidget() { 
  // m_pCustomWidget = new vtkCustomWidget();
  return 0; 
}

int ViewerControl::AddModel(QString sPath) {
  // if(m_pReader == nullptr){
  //   qDebug() << __FUNCTION__ << "m_pReader is nullptr";
  //   return -1;
  // }

  if(m_pModelMgr == nullptr){
    qDebug() << __FUNCTION__ << "m_pModelMgr is nullptr!";
    return -1;
  }
  // m_pReader->SetFileName(sPath.toStdString().c_str());
  // m_pReader->Update();

  vtkSmartPointer<vtkSTLReader> pReader = vtkSmartPointer<vtkSTLReader>::New();
  pReader->SetFileName(sPath.toStdString().c_str());
  pReader->Update();

  // vtkSmartPointer<Model> pModel = vtkSmartPointer<Model>::New();
  // vtkSmartPointer<vtkDataSetMapper> pMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  // pMapper->SetInputConnection(m_pReader->GetOutputPort());
  // pModel->SetMapper(pMapper);

  // Model* pModel = new Model();
  // vtkSmartPointer<vtkPolyData> pData = m_pReader->GetOutput();
  // pModel->setPolyData(pData);
  // pModel->generate();

  Model* pModel = new Model(pReader->GetOutput());
  // Model* pModel = new Model(m_pReader->GetOutput());

  // vtkSmartPointer<vtkActor> pActor;
  // if(pModel->getActor(pActor) != 0){
  //   delete pModel;
  //   qDebug() << __FUNCTION__ << "Can't get Actor from model!";
  //   return -1;
  // }
  // m_pRenderer->AddActor(pActor);
  // pActor->SetProperty(m_pProperty);

  pModel->setModelPath(sPath);
  QString sModelName = sPath.right(sPath.length() - sPath.lastIndexOf('/') - 1);
  pModel->setModelName(sModelName);
  pModel->turnActive();
  m_vShowModel.push_back(pModel);
  emit ModelMgrAddModelSig(pModel);
  return 0;
}

// void ViewerControl::PickModelCallBack(vtkObject* caller, unsigned long eid, void* clientdata, void* calldata) {
//   vtkRenderWindowInteractor* pInteractor = static_cast<vtkRenderWindowInteractor*>(caller);
//   int* pos = pInteractor->GetEventPosition();

//   vtkSmartPointer<vtkPropPicker> pPicker = vtkSmartPointer<vtkPropPicker>::New();
//   pPicker->Pick(pos[0], pos[1], 0, pInteractor->FindPokedRenderer(pos[0], pos[1]));

//   vtkActor* pActor = pPicker->GetActor();
//   if(pActor != nullptr){
//     if(m_pChosenActor != nullptr){
//       m_pChosenActor->GetProperty()->EdgeVisibilityOff();
//     }
//     m_pChosenActor = pActor;

//     vtkProperty* pProperty = m_pChosenActor->GetProperty();
//     pProperty->SetEdgeColor(0.0, 1.0, 0.0);
//     pProperty->EdgeVisibilityOn();
//   }
// }

void ViewerControl::ShowSlot(Model* pModel) {
  if(!pModel->isActive()){
    qDebug() << __FUNCTION__ << QString(
                                "Model is deactive! Model name: %1")
                                .arg(pModel->getModelName());
    return;
  }

  vtkSmartPointer<vtkActor> pActor;
  // vtkSmartPointer<vtkAssembly> pAssembly;
  if(pModel->getActor(pActor) != 0){
    qDebug() << __FUNCTION__ << QString(
                                "Can't get Actor! Model name: %1")
                                .arg(pModel->getModelName());
    return;
  }

  pModel->m_pCustomWidget->SetInteractor(m_pRenderWindowInteractor);

  vtkNew<vtkMatrix4x4> Initial;
  pActor->SetUserMatrix(Initial);

  // set information -Model Name
  pActor->SetPropertyKeys(vtkSmartPointer<vtkInformation>::New());
  pActor->GetPropertyKeys()->Set(this->pCustomKey, pModel->getModelName().toStdString().c_str());

  vtkSmartPointer<vtkProperty> pProperty = vtkSmartPointer<vtkProperty>::New();
  pProperty->DeepCopy(m_pProperty);
  pActor->SetProperty(pProperty);
  m_pRenderer->AddActor(pActor);
  m_pRenderer->ResetCamera();
  m_pRenderWindow->Render();
}

void ViewerControl::ResetCameraSlot() {
  if(m_pRenderer == nullptr){
    qDebug() << __FUNCTION__ << "m_pRenderer is nullptr!";
    return;
  }
  m_pRenderer->ResetCamera();
  vtkCamera *camera = m_pRenderer->GetActiveCamera();
  double* p = camera->GetPosition();
  qDebug() << QString("Camera Position: %1, %2, %3").arg(p[0]).arg(p[1]).arg(p[2]);
  m_pRenderWindow->Render();
}

void ViewerControl::ZoomInSlot() {
  if(m_pRenderer == nullptr){
    qDebug() << __FUNCTION__ << "m_pRenderer is nullptr";
    return;
  }

  if(m_pRenderWindow == nullptr){
    qDebug() << __FUNCTION__ << "m_pRenderWindow is nullptr";
    return;
  }
  vtkCamera* pCamera = m_pRenderer->GetActiveCamera();
  pCamera->Dolly(1.5);
  m_pRenderer->ResetCameraClippingRange();

  m_pRenderWindow->Render();
}

void ViewerControl::ZoomOutSlot() {
  if(m_pRenderer == nullptr){
    qDebug() << __FUNCTION__ << "m_pRenderer is nullptr";
    return;
  }

  if(m_pRenderWindow == nullptr){
    qDebug() << __FUNCTION__ << "m_pRenderWindow is nullptr";
    return;
  }
  vtkCamera* pCamera = m_pRenderer->GetActiveCamera();
  pCamera->Dolly(0.75);
  m_pRenderer->ResetCameraClippingRange();

  m_pRenderWindow->Render();
}

void ViewerControl::ScreenShotSlot() {
  if(m_pPNGWriter == nullptr){
    qDebug() << __FUNCTION__ << "m_pPNGWriter is nullptr!";
    return;
  }
  if(m_pWindowToImageFilter == nullptr){
    qDebug() << __FUNCTION__ << "m_pWindowToImageFilter is nullptr!";
    return;
  }
  m_pWindowToImageFilter->SetInput(m_pRenderWindow);
  m_pWindowToImageFilter->Update();

  QString sPhotoName = QDateTime::currentDateTime().toString("hh_mm_ss")+ ".png";

  m_pPNGWriter->SetFileName(sPhotoName.toStdString().c_str());
  m_pPNGWriter->SetInputConnection(m_pWindowToImageFilter->GetOutputPort());
  m_pPNGWriter->Write();

  QMessageBox::information(this, QString("Cautions!"), QString("Screen Shot has been saved!"), QMessageBox::Ok);
  return;
}

void ViewerControl::ReadModelSlot(){
  // 选择文件读取
  QFileDialog* qfd = new QFileDialog();
  qfd->setAttribute(Qt::WA_DeleteOnClose); // 对话框关闭时，自动销毁对话框的内存,避免内存泄漏
  QString sFilePath = qfd->getOpenFileName(this, "打开文件", "/mnt/e/stlFile/", "(*.stl *.STL *.conf *.CONF)");
  if(sFilePath == ""){
    // qDebug() << __FUNCTION__ << "Didn't choose file!";
    return;
  }
  if(sFilePath.mid(sFilePath.indexOf('.')).toLower() == QString(".stl")){
    if(this->AddModel(sFilePath) != 0){
      qDebug() << __FUNCTION__ << "addModel Fail!";
      return;
    }else{
      qDebug() << __FUNCTION__ << "addModel success!";
    }
  }else{
    // .conf
    QFile qf(sFilePath);
    qf.open(QIODevice::ReadOnly);
    QTextStream qts(&qf);
    QStringList sList = qts.readAll().split('\n');
    for(QString iter : sList){
      if(this->AddModel(iter) != 0){
        qDebug() << __FUNCTION__ << "addModel Fail!";
      }else{
        qDebug() << __FUNCTION__ << "addModel success!";
      }
    }
  }
  return;
}

void ViewerControl::DeleteShowModelSlot(Model* pModel){
  if(pModel == nullptr){
    qDebug() << __FUNCTION__ << "pModel is nullptr!";
    return;
  }

  vtkSmartPointer<vtkActor> pActor;
  if(pModel->getActor(pActor) != 0){
    qDebug() << __FUNCTION__ << "Can't get Actor!";
    return;
  }
  if(m_pRenderer == nullptr){
    qDebug() << __FUNCTION__ << "m_pRenderer is nullptr!";
    return;
  }
  m_pRenderer->RemoveActor(pActor);
  m_pRenderWindow->Render();
  
  for(auto iter = m_vShowModel.begin(); iter != m_vShowModel.end(); iter++){
    if(*iter == pModel){
      m_vShowModel.erase(iter);
      break;
    }
  }

  emit TellModelMgrDeleteModelSig(pModel);
}