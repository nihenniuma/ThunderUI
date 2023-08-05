#include "modelManager.h"

ModelManager::ModelManager(){}

// ModelManager::ModelManager(vtkSmartPointer<vtkSTLReader> pReader) : m_pReader(pReader){}

// ModelManager::ModelManager(vtkSTLReader* pReader) : m_pReader(pReader){}

ModelManager::~ModelManager(){
  // this->clear();
  // if(m_pReader != nullptr){
  //   m_pReader->Delete();
  //   m_pReader = nullptr;
  // }
}

int ModelManager::initAndAddModel(QString sPath){
  Model::m_pReader->SetFileName(sPath.toStdString().c_str());
  Model::m_pReader->Update();
  Model* model = new Model();

  // model->m_pMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  model->m_pMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  model->m_pPolyData = Model::m_pReader->GetOutput();
  // model->m_pMapper->SetInputData(model->m_pPolyData);
  model->m_pMapper->SetInputConnection(Model::m_pReader->GetOutputPort());
  
  model->m_pActor = vtkSmartPointer<vtkActor>::New();
  model->m_pActor->SetMapper(model->m_pMapper);

  model->setModelPath(sPath);
  model->setModelName(sPath.right(sPath.length() - sPath.lastIndexOf('/') - 1)); // this will short sPath
  model->turnActive();

  m_ModelMap.insert(model->sModelName, model);

  emit traverseModelSig();
  return 0;
}

// int ModelManager::addModel(QString sPath, Model* model) {
//   // if(m_pReader == nullptr){
//   //   qDebug() << __FUNCTION__ << "STLReader is nullptr! Stop addModel";
//   //   return -1;
//   // }
//   // m_pReader->SetFileName(sPath.toStdString().c_str()); // read Model
//   // m_pReader->Update();
  
//   // // init model
//   // vtkSmartPointer<vtkPolyData> pVertex = m_pReader->GetOutput(); // get data
//   // Model* model = new Model(pVertex); // store in model
  
//   // init normals
//   // int nRet = model->generateNormals();

//   // if(nRet != 0){
//   //   qDebug() << __FUNCTION__ << "generateNormals failed!";
//   //   return -1;
//   // }else{
//   //   qDebug() << __FUNCTION__ << "generateNormals success!";
//   // }
//   model->setModelPath(sPath);
//   model->setModelName(sPath.right(sPath.length() - sPath.lastIndexOf('/') - 1)); // this will short sPath
//   return 0;
// }

int ModelManager::remove(QString sName) { 
  auto iter = m_ModelMap.find(sName);
  if(iter != m_ModelMap.end()){
    m_ModelMap.erase(iter);
    qDebug() << __FUNCTION__ << QString("%1 has been deleted!").arg(sName);
    return 0;
  }else{
    qDebug() << __FUNCTION__ << QString("%1 Not Found! Can't delete!").arg(sName);
    return -1;
  }
}

int ModelManager::clear() {
  m_ModelMap.clear();
  return 0; 
}

// int ModelManager::reload(QString sName) { 
//   auto iter = m_ModelMap.find(sName);
//   return reload(iter);
// }

// int ModelManager::reload(QMap<QString, Model*>::iterator& iter) {
//   if(iter == m_ModelMap.end()){
//     qDebug() << __FUNCTION__ << QString("%1 Not Found! Can't reload!").arg(iter->getModelName());
//     return -1;
//   }else{
//     qDebug() << __FUNCTION__ << QString("%1 has been reloaded!").arg(iter->getModelName());
//   }
//   // reload file
//   m_pReader->SetFileName(iter->getModelPath().toStdString().c_str());
//   vtkSmartPointer<vtkPolyData> pData = m_pReader->GetOutput();

//   // reload data
//   // iter->setVertex(pData);
//   // iter->generateNormals();
//   return 0; 
// }

// int ModelManager::reloadAll() {
//   for(auto iter = m_ModelMap.begin(); iter != m_ModelMap.end(); iter++){
//     if(reload(iter) != 0){
//       qDebug() << __FUNCTION__ << QString(
//                                         "Model: %1, Path: %2, can't reload!")
//                                         .arg(iter.key())
//                                         .arg(iter.value().getModelPath());
//     }
//   }
//   return 0; 
// }

int ModelManager::update2File(QString sPath) {

  return 0;
}

int ModelManager::update2FileAll() { return 0; }

void ModelManager::removeModel(QString sName){
  remove(sName);
}

bool ModelManager::isModelExist(QString sName){
  return m_ModelMap.find(sName) != m_ModelMap.end();
}

int ModelManager::traverseModel(QVector<Model*>& vModels){
  for(auto iter = m_ModelMap.begin(); iter != m_ModelMap.end(); iter++){
    if(iter.value()->isActive()){
      vModels.append(iter.value());
    }
  }
  return 0;
}


