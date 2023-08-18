#ifndef VIEW_INTERACTOR_H
#define VIEW_INTERACTOR_H

#include "viewerControl.h"
#include "bridge.h"
#include "CustomWidget/vtkCustomWidget.h"

#include <QDateTime>
#include <QDebug>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkOutlineFilter.h>
#include <vtkMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkVolume.h>
#include <vtkVolumeOutlineSource.h>
#include <vtkInformation.h>
#include <vtkCamera.h>

class ViewerControl;
class Bridge;

class ViewInteractorStyle : public vtkInteractorStyleTrackballActor{
public:
  ViewInteractorStyle();
  ~ViewInteractorStyle(){};

  int SetRenderer(vtkSmartPointer<vtkRenderer> pRenderer);
  int SetCustomWidget(vtkCustomWidget* pCustomWidget);
  // int SetModelMgr(ModelManager* pModelMgr);

  virtual void OnLeftButtonDown();
  void SetBridge(Bridge* pBridge);

private:
  void PickMesh(int x, int y);
  void PickModel(int x, int y);

private:
  vtkSmartPointer<vtkActor> m_pSelectedActor = nullptr;
  vtkSmartPointer<vtkActor> m_pPreActor =nullptr;
  vtkSmartPointer<vtkRenderer> m_pRenderer = nullptr;
  vtkSmartPointer<vtkOutlineFilter> m_pOutline = nullptr;
  vtkSmartPointer<vtkRenderWindowInteractor> m_pInteractor = nullptr;
  vtkSmartPointer<vtkPropPicker> m_pPicker = nullptr;
  vtkCustomWidget* m_pCustomWidget = nullptr;

  vtkActor* pLastActor = nullptr;
  bool bLeftBtnPressed = false;
  qint64 LastClickTime;
  Bridge* m_pBridge = nullptr;
  // ModelManager* m_pModelMgr = nullptr;
  // Model* preModel = nullptr;
};

#endif