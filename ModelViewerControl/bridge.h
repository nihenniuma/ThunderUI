#ifndef BRIDGE_H
#define BRIDGE_H

#include "Model/model.h"
#include "Model/modelManager.h"
#include "viewerControl.h"

#include <vtkObject.h>
#include <vtkActor.h>
#include <vtkInformation.h>
#include <QObject>
#include <QString>

class ViewerControl;

class Bridge : public QObject{
  Q_OBJECT
public:
  Bridge();
  ~Bridge();
  void CallActivateItemSig(vtkActor* pActor);
  void CallDeactivateItemSig(vtkActor* pActor);

signals:
  void ChangeItemSig(Model* pModel);
  void FindModelPtrAndActivateSig(QString sModelName);
  void FindModelPtrAndDeactivateSig(QString sModelName);

public slots:




};



#endif