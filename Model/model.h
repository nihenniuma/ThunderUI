#ifndef MODEL_H
#define MODEL_H

#include <QDebug>
#include <QString>
#include <QTreeWidgetItem>
#include <vtkPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSTLReader.h>
#include <vtkDataSetMapper.h>
#include <vtkOutlineFilter.h>
#include <vtkAssembly.h>
#include <vtkProperty.h>
#include "vtkCustomWidget.h"

class Model {
public:
  Model(vtkSmartPointer<vtkPolyData> pVTKPolyData);
  ~Model();

  void CustomWidgetOn();
  void CustomWidgetOff();

  int generate();
  // get model data out
  int getData(vtkSmartPointer<vtkPolyData>& pVTKPolyData);
  int getActor(vtkSmartPointer<vtkActor>& pVTKActor);
  // int getAssembly(vtkSmartPointer<vtkAssembly>& pAssembly);
  int getTreeWidgetItem(QTreeWidgetItem* parent, QTreeWidgetItem** ppTreeWidgetItem);
  int getTreeWidgetItem(QTreeWidgetItem** ppTreeWidgetItem);
  int turnActive();
  int turnDeActive();
  bool isActive();
  int setModelName(QString sName);
  int setModelPath(QString sPath);

  int setActor(vtkActor* pActor);
  int setPolyData(vtkPolyData* pData);
  int setPolyData(vtkSmartPointer<vtkPolyData> pData);
  int setMapper(vtkDataSetMapper* pMapper);
  QString getModelName();
  QString getModelPath();

  bool bActive = true;
  QString sModelName;
  QString sModelPath;
  QTreeWidgetItem* m_pTreeWidgetItem = nullptr;

  vtkSmartPointer<vtkDataSetMapper> m_pMapper = nullptr;
  // vtkSmartPointer<vtkActor> m_pActor = nullptr;
  vtkActor* m_pActor = nullptr;
  vtkSmartPointer<vtkPolyData> m_pPolyData = nullptr;

  vtkCustomWidget* m_pCustomWidget = nullptr;
  // vtkSmartPointer<vtkOutlineFilter> m_pOutlineFilter = nullptr;
  // vtkSmartPointer<vtkAssembly> m_pAssembly = nullptr;
  // vtkSmartPointer<vtkActor> m_pOutlineActor = nullptr;
  // vtkSmartPointer<vtkDataSetMapper> m_pOutlineMapper = nullptr;

// protected:
//   Model::Model();
//   Model::~Model();

// protected:
//   vtkActor* Device = nullptr;
//   vtkSmartPointer<vtkPolyDataMapper> pMapper = nullptr;
//   vtkSmartPointer<vtkPolyData> pData = nullptr;
};
#endif