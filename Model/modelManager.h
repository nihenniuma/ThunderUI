#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <QMap>

#include "model.h"

class ModelManager : public QObject{
  Q_OBJECT
public:
  ModelManager();
  ~ModelManager();

  int RemoveModel(QString sModelName);
  int ClearModel();
  bool isModelExist(QString sModelName);
  int FindModelPtr(QString sModelName, Model* ptr);

  QMap<QString, Model*> m_ModelPtrMap;

signals:
  void ShowSig(Model* pModel);
  void AddTreeNodeSig(Model* pModel);
  void DeleteShowModelSig(Model* pModel);
  void CheckTreeItemSig(Model* pModel);
  void UncheckTreeItemSig(Model* pModel);

public slots:
  void ModelMgrAddModelSlot(Model* pModel);
  void DeleteModelSlot(Model* pModel);
  void FindModelPtrSlot(QString sModelName);
  void FindModelPtrAndActivateSlot(QString sModelName);
  void FindModelPtrAndDeactivateSlot(QString sModelName);
};

#endif