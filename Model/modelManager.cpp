#include "modelManager.h"

ModelManager::ModelManager(){}

ModelManager::~ModelManager(){
  ClearModel();
}

int ModelManager::RemoveModel(QString sModelName){
  if(!isModelExist(sModelName)){
    qDebug() << __FUNCTION__ << QString(
                                "Model named %1 does not exist!")
                                .arg(sModelName);
    return -1;
  }
  QMap<QString, Model*>::iterator iter = m_ModelPtrMap.find(sModelName);
  m_ModelPtrMap.erase(iter);
  return 0;
}

int ModelManager::ClearModel() {
  for(auto iter = m_ModelPtrMap.begin(); iter != m_ModelPtrMap.end(); iter++){
    Model* p = iter.value();
    delete p;
    // p->Delete();

    p = nullptr;
  }
  m_ModelPtrMap.clear();
  return 0; 
}

int ModelManager::FindModelPtr(QString sModelName, Model* ptr) {
  std::cout << sModelName.toStdString() << std::endl;
  QMap<QString, Model*>::iterator iter = m_ModelPtrMap.find(sModelName);
  if(iter == m_ModelPtrMap.end()){
    qDebug() << __FUNCTION__ << QString(
                                "%1 not found!")
                                .arg(sModelName);
    return -1;
  }
  return 0; 
}

bool ModelManager::isModelExist(QString sModelName){
  if(m_ModelPtrMap.find(sModelName) != m_ModelPtrMap.end()){
    return true;
  }
  return false;
}

void ModelManager::ModelMgrAddModelSlot(Model* pModel){
  if(pModel == nullptr){
    qDebug() << __FUNCTION__ << "Model Ptr is nullptr!";
    return;
  }
  
  if(m_ModelPtrMap.contains(pModel->getModelName())){
    qDebug() << __FUNCTION__ << QString(
                                "Same model named %1 has existed!")
                                .arg(pModel->getModelName());
    return;
  }

  m_ModelPtrMap.insert(pModel->getModelName(), pModel);
  // tell treeWidget show node
  emit AddTreeNodeSig(pModel);
  // show model in display
  emit ShowSig(pModel);
  return;
}

void ModelManager::DeleteModelSlot(Model* pModel){
  QString sModelName = pModel->getModelName();
  QMap<QString, Model*>::iterator iter = m_ModelPtrMap.find(sModelName);
  if(iter == m_ModelPtrMap.end()){
    qDebug() << __FUNCTION__ << QString(
                                "%1 not found!")
                                .arg(sModelName);
    return;
  }
  m_ModelPtrMap.erase(iter);

  if(pModel == nullptr){
    qDebug() << __FUNCTION__ << "pModel is nullptr!";
    return;
  }
  delete pModel;
  // pModel->Delete();

  qDebug() << __FUNCTION__ << QString(
                              "%1 deleted successfully!")
                              .arg(sModelName);
}

void ModelManager::FindModelPtrSlot(QString sModelName){
  QMap<QString, Model*>::iterator iter = m_ModelPtrMap.find(sModelName);
  if(iter == m_ModelPtrMap.end()){
    qDebug() << __FUNCTION__ << QString(
                                "%1 not found!")
                                .arg(sModelName);
    return;
  }
  emit DeleteShowModelSig(iter.value());
}

void ModelManager::FindModelPtrAndActivateSlot(QString sModelName) {
  QMap<QString, Model*>::iterator iter = m_ModelPtrMap.find(sModelName);
  if(iter == m_ModelPtrMap.end()){
    qDebug() << __FUNCTION__ << QString(
                                "%1 not found!")
                                .arg(sModelName);
    return;
  }
  iter.value()->CustomWidgetOn();
  emit CheckTreeItemSig(iter.value());
}

void ModelManager::FindModelPtrAndDeactivateSlot(QString sModelName) {
  QMap<QString, Model*>::iterator iter = m_ModelPtrMap.find(sModelName);
  if(iter == m_ModelPtrMap.end()){
    qDebug() << __FUNCTION__ << QString(
                                "%1 not found!")
                                .arg(sModelName);
    return;
  }
  iter.value()->CustomWidgetOff();
  emit UncheckTreeItemSig(iter.value());
}
