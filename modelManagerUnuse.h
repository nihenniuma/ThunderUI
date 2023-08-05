#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "model.h"
#include "treeWidgetManager.h"

#include <QMap>
#include <QVector>
#include <QObject>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkSTLReader.h>
#include <vtkAlgorithm.h>

class Model;

class ModelManager : public QObject{
  Q_OBJECT
public:
  ModelManager();
  // ModelManager(vtkSmartPointer<vtkSTLReader> pReader);
  // ModelManager(vtkSTLReader* pReader);
  ~ModelManager();

  // init
  int initAndAddModel(QString sPath);
  // int addModel(QString sPath, Model& model);
  int remove(QString sName); // delete one model
  int clear(); // delete all models
  // int reload(QString sName); // reload model from file
  // int reload(QMap<QString, Model>::iterator& iter);
  int reloadAll();
  int update2File(QString sPath); // write new data to stl file
  int update2FileAll();
  int setLogic();

  // transform
  int rotate(QString sName);
  int rotateAll();
  int move(QString sName);
  int moveAll();

  // state
  int deactivate();
  int deactivateAll();
  int activate();
  int activateAll();
  bool isModelExist(QString sName);
  
  // viewer
  // void showModel(Model& model);
  int traverseModel(QVector<Model*>& vModels);

signals:
  void addNodeSig(QString, QTreeWidgetItem*);
  void traverseModelSig();

public slots:
  void removeModel(QString sName);

private:
  QMap<QString, Model*> m_ModelMap; // store Models

};

#endif