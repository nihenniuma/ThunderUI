#include "model.h"


// vtkStandardNewMacro(Model);

// Model::Model() {}

Model::Model(vtkSmartPointer<vtkPolyData> pVTKPolyData)
  : m_pPolyData(pVTKPolyData)
  , m_pActor(vtkSmartPointer<vtkActor>::New())
  , m_pMapper(vtkSmartPointer<vtkDataSetMapper>::New())
  // , m_pAssembly(vtkSmartPointer<vtkAssembly>::New())
  // , m_pOutlineActor(vtkSmartPointer<vtkActor>::New())
  // , m_pOutlineFilter(vtkSmartPointer<vtkOutlineFilter>::New()) 
{
  m_pMapper->SetInputData(m_pPolyData);
  m_pActor->SetMapper(m_pMapper);
}

Model::~Model(){
  if(m_pTreeWidgetItem != nullptr){
    delete m_pTreeWidgetItem;
  }
}

int Model::generate() {
  if(m_pPolyData == nullptr){
    qDebug() << __FUNCTION__ << "No PolyData!";
    return -1;
  }
  m_pMapper->SetInputData(m_pPolyData);
  this->setMapper(m_pMapper);
  return 0; 
}

int Model::turnActive() { 
  this->bActive = true;
  return 0;
}

int Model::turnDeActive() { 
  this->bActive = false;
  return 0; 
}

bool Model::isActive() { 
  if(this->bActive){
    return true;
  }
  return false; 
}

int Model::setModelName(QString sName) { 
  this->sModelName = sName;
  return 0; 
}

int Model::setModelPath(QString sPath) {
  this->sModelPath = sPath;
  return 0;
}

QString Model::getModelName() {
  return this->sModelName; 
}

QString Model::getModelPath() {
  return this->sModelPath; 
}

// Model::Model() {
//   pMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//   this->Device = vtkActor::New();
// }

// Model::~Model(){
//   this->Device->Delete();
// }

int Model::setActor(vtkActor* pActor) { 
  m_pActor = pActor;  
  return 0; 
}

int Model::setPolyData(vtkPolyData* pData) { 
  m_pPolyData = pData;
  return 0; 
}

int Model::setPolyData(vtkSmartPointer<vtkPolyData> pData) {
  m_pPolyData = pData;
  return 0; 
}

int Model::setMapper(vtkDataSetMapper* pMapper) {
  m_pMapper = pMapper;
  return 0; 
}

int Model::getData(vtkSmartPointer<vtkPolyData>& pVTKPolyData) {
  if(m_pPolyData == nullptr) return -1;
  pVTKPolyData = m_pPolyData;
  return 0;
}

int Model::getActor(vtkSmartPointer<vtkActor>& pVTKActor) { 
  if(m_pActor == nullptr){
    return -1;
  }
  pVTKActor = m_pActor;
  return 0; 
}

// int Model::getAssembly(vtkSmartPointer<vtkAssembly>& pAssembly) {
//   if(m_pAssembly == nullptr){
//     return -1;
//   }
//   pAssembly = m_pAssembly;
//   return 0; 
// }

// include init item
/* this two function is very important(about c++ property!!!) */
/* ---------------------------------------------------------- */
/* ---------------------------------------------------------- */
int Model::getTreeWidgetItem(QTreeWidgetItem* parent, QTreeWidgetItem** ppTreeWidgetItem) {
  if(m_pTreeWidgetItem == nullptr && parent == nullptr){
    qDebug() << __FUNCTION__ << "m_pTreeWidgetItem is nullptr!";
    return -1;
  }
  if(m_pTreeWidgetItem == nullptr){
    m_pTreeWidgetItem = new QTreeWidgetItem(parent, QStringList() << this->sModelName);
    m_pTreeWidgetItem->setCheckState(0, Qt::Checked);
  }
  *ppTreeWidgetItem = m_pTreeWidgetItem;
  return 0; 
}

int Model::getTreeWidgetItem(QTreeWidgetItem** ppTreeWidgetItem) {
  *ppTreeWidgetItem = m_pTreeWidgetItem;  
  return 0; 
}
/* ---------------------------------------------------------- */
/* ---------------------------------------------------------- */
/* ---------------------------------------------------------- */

// int Model::RenderOpaqueGeometry(vtkViewport* viewport){
//   return vtkActor::RenderOpaqueGeometry(viewport);
// }
// int Model::RenderTranslucentPolygonalGeometry(vtkViewport* viewport) {
//   return vtkActor::RenderTranslucentPolygonalGeometry(viewport);
// }
// void Model::ReleaseGraphicsResources(vtkWindow* window){
//   vtkActor::ReleaseGraphicsResources(window);
// };
