#ifndef VTK_CUSTOM_REPRESENTATION_H
#define VTK_CUSTOM_REPRESENTATION_H

#include <vtkWidgetRepresentation.h>
#include <vtkAbstractWidget.h>
#include <vtkWidgetRepresentation.h>
#include <vtkActor.h>
#include <vtkRegularPolygonSource.h>
#include <vtkMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkConeSource.h>
#include <vtkCellPicker.h>
#include <vtkLineSource.h>
#include <vtkAssembly.h>
#include <vtkMatrix4x4.h>
#include <vtkTransform.h>
#include <vtkPoints.h>
#include <vtkDoubleArray.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkWindow.h>
#include <vtkInteractionWidgetsModule.h>

class vtkCustomRepresentation : public vtkWidgetRepresentation{
public:
  static vtkCustomRepresentation* New();

  vtkTypeMacro(vtkCustomRepresentation, vtkWidgetRepresentation);

  void BuildRepresentation();
  void SizeHandles();

protected:
  vtkCustomRepresentation();
  ~vtkCustomRepresentation();


private:
  vtkActor** AxisCircle = nullptr;
  vtkActor** AxisArrow = nullptr;
  vtkPolyDataMapper** AxisCircleMapper = nullptr;
  vtkRegularPolygonSource** AxisPolygonSource = nullptr;
  vtkAssembly** HandleAxis = nullptr;
  vtkCellPicker* CirclePicker = nullptr;
  vtkCellPicker* AxisPicker = nullptr;
  vtkTransform* Transform = nullptr;
  vtkPoints* PlanePoints = nullptr;
  vtkDoubleArray* PlaneNormals = nullptr;
  vtkMatrix4x4* Matrix = nullptr;

  double g_normalColor[3][3];
  double g_circleRadius = 10;
  double g_circleLineWidth = 1;
  double g_axisLength = 5;
  double g_axisLineWidth = 1;
};
#endif