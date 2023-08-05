#include "bridge.h"

Bridge::Bridge() {}

Bridge::~Bridge() {}

void Bridge::CallActivateItemSig(vtkActor* pActor) {
  QString sModelName(pActor->GetPropertyKeys()->Get(ViewerControl::pCustomKey));
  emit FindModelPtrAndActivateSig(sModelName);
}

void Bridge::CallDeactivateItemSig(vtkActor* pActor) {
  QString sModelName(pActor->GetPropertyKeys()->Get(ViewerControl::pCustomKey));
  emit FindModelPtrAndDeactivateSig(sModelName);
}
