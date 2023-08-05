#ifndef VIEWER_CONTROL_H
#define VIEWER_CONTROL_H

// #include <vtkAutoInit.h>
// VTK_MODULE_INIT(vtkRenderingOpenGL2)
// VTK_MODULE_INIT(vtkInteractionStyle)
// VTK_MODULE_INIT(vtkRenderingContextOpenGL2)
// VTK_MODULE_INIT(vtkRenderingFreeType)

#include <functional>
#include <QTextStream>
#include <QMap>
#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkBoxWidget.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkMapper.h>
#include <vtkRenderer.h>
#include <vtkSTLReader.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkProp.h>
#include <vtkCamera.h>
#include <vtkProp3D.h>
#include <vtkPNGWriter.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPropPicker.h>
#include <vtkInformation.h>
#include <vtkCallbackCommand.h>
#include <vtkInformationStringKey.h>
#include <vtkPlaneSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkBoxWidget.h>
#include <vtkRegularPolygonSource.h>

#include "Model/modelManager.h"
#include "viewInteractStyle.h"
#include "bridge.h"
#include "vtkCustomWidget.h"

class Bridge;
class ViewInteractorStyle;

class ViewerControl : public QVTKOpenGLNativeWidget{
  Q_OBJECT
public:
  ViewerControl(QWidget* parent, ModelManager* pModelMgr, Bridge* pBridge);
  ~ViewerControl();

  int InitViewer(ModelManager* pModelMgr = nullptr);
  int InitGridRaft();
  int InitCoords();
  int InitBoxWidget();
  int InitCustomWidget();
  int AddModel(QString sPath);

  // void PickModelCallBack(vtkObject* caller, unsigned long eid, void* clientdata, void* calldata);
signals:
  void ModelMgrAddModelSig(Model* pModel);
  void TellModelMgrDeleteModelSig(Model* pModel);

public slots:
  void ReadModelSlot();
  void ShowSlot(Model* pModel);
  void ResetCameraSlot();
  void ZoomInSlot();
  void ZoomOutSlot();
  void ScreenShotSlot();
  void DeleteShowModelSlot(Model* pModel);

private:
  vtkSmartPointer<vtkRenderer> m_pRenderer = nullptr;
  // vtkSmartPointer<vtkSTLReader> m_pReader = nullptr;
  vtkSmartPointer<vtkActor> m_pChosenActor = nullptr; // actor records chosen model actor
  vtkSmartPointer<vtkPolyData> m_pPolyData = nullptr;
  vtkSmartPointer<vtkProperty> m_pProperty = nullptr;
  vtkSmartPointer<vtkPolyDataMapper> m_pMapper = nullptr;
  vtkSmartPointer<vtkPNGWriter> m_pPNGWriter = nullptr;
  vtkSmartPointer<vtkWindowToImageFilter> m_pWindowToImageFilter = nullptr;
  vtkSmartPointer<vtkPlaneSource> m_pPlaneSource = nullptr;
  vtkSmartPointer<vtkAxesActor> m_pAxesActor = nullptr;
  vtkSmartPointer<vtkOrientationMarkerWidget> m_pWidget = nullptr;
  vtkSmartPointer<vtkBoxWidget> m_pBoxWidget = nullptr;

  vtkRenderWindow* m_pRenderWindow = nullptr;
  vtkRenderWindowInteractor* m_pRenderWindowInteractor = nullptr;
  ViewInteractorStyle* m_pViewInteractorStyle = nullptr;
  vtkCustomWidget* m_pCustomWidget = nullptr;
  vtkInteractorStyleTrackballCamera* m_pInteractorStyleTrackballCamera = nullptr;

  QColor m_color;
  QVector<Model*> m_vShowModel;
  ModelManager* m_pModelMgr = nullptr;

  double pos[3] = {10, 10, 10};
  // static QString Key;
public:
  Bridge* m_pBridge = nullptr;
  static vtkInformationStringKey* pCustomKey;
};

#endif