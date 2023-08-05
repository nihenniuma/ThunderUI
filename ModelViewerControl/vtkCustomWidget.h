#ifndef VTK_CUSTOM_WIDGET_H
#define VTK_CUSTOM_WIDGET_H

#include "vtkCustomRepresentation.h"

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
#include <vtkInteractionWidgetsModule.h>

class vtkCustomWidget : public vtkAbstractWidget{
public:
  static vtkCustomWidget* New();

  vtkTypeMacro(vtkCustomWidget, vtkAbstractWidget);

  void SetRepresentation(vtkCustomRepresentation* r)
  {
    this->Superclass::SetWidgetRepresentation(reinterpret_cast<vtkWidgetRepresentation*>(r));
  }

  void CreateDefaultRepresentation();
protected:
  vtkCustomWidget();
  ~vtkCustomWidget();

private:

};



#endif