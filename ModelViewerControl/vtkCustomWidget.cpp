#include "vtkCustomWidget.h"

vtkStandardNewMacro(vtkCustomWidget);

void vtkCustomWidget::CreateDefaultRepresentation() {
  if (!this->WidgetRep)
  {
    this->WidgetRep = vtkCustomRepresentation::New();
  }

}

vtkCustomWidget::vtkCustomWidget() {
  
}
