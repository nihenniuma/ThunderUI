#include "vtkCustomRepresentation.h"

vtkCustomRepresentation::vtkCustomRepresentation()
  : AxisCircle(new vtkActor* [3])
  , AxisArrow(new vtkActor* [3])
  , AxisCircleMapper(new vtkPolyDataMapper* [3])
  , AxisPolygonSource(){
  
  double bounds[6] = {-0.5, 0.5, -0.5, 0.5, -0.5, 0.5};

  for(auto i=0;i<3;i++){
    this->AxisCircle[i]=vtkActor::New();
    this->AxisPolygonSource[i] = vtkRegularPolygonSource::New();
    this->AxisCircleMapper[i] = vtkPolyDataMapper::New();

    this->AxisPolygonSource[i]->SetNumberOfSides(100);    //多边形边数
    this->AxisPolygonSource[i]->SetRadius(g_circleRadius);       //半径
    this->AxisPolygonSource[i]->SetCenter(0, 0, 0);      //圆心

    this->AxisCircleMapper[i]->SetInputConnection(this->AxisPolygonSource[i]->GetOutputPort());
    this->AxisCircle[i]->SetMapper(this->AxisCircleMapper[i]);
    this->AxisCircle[i]->GetProperty()->SetOpacity(1);    //透明度
    this->AxisCircle[i]->GetProperty()->SetLineWidth(g_circleLineWidth);
    this->AxisCircle[i]->GetProperty()->SetRepresentationToWireframe();//图形不填充，只要边框
    this->AxisCircle[i]->GetProperty()->SetColor(g_normalColor[i][0],g_normalColor[i][1],g_normalColor[i][2]);    //颜色

    vtkNew<vtkMatrix4x4> initMatrix;
    this->AxisCircle[i]->SetUserMatrix(initMatrix);
  }

  this->CirclePicker = vtkCellPicker::New();
  this->CirclePicker->SetTolerance(0.001);
  for(int i=0;i<3;i++){
    this->CirclePicker->AddPickList(this->AxisCircle[i]);
  }
  this->CirclePicker->PickFromListOn();

  this->HandleAxis = new vtkAssembly* [3];
  for (int i=0; i<3; i++)
  {
    vtkNew<vtkLineSource> lineSource;
    vtkNew<vtkPolyDataMapper> lineMapper;
    vtkNew<vtkActor> lineActor;

    lineMapper->SetInputConnection(lineSource->GetOutputPort());
    lineActor->SetMapper(lineMapper);

    double point1[3];
    double point2[3];
    if(i==0){//x轴
      point1[0]=-g_axisLength;
      point1[1]=0;
      point1[2]=0;

      point2[0]=g_axisLength;
      point2[1]=0;
      point2[2]=0;
    }else if(i==1){//y轴
      point1[0]=0;
      point1[1]=-g_axisLength;
      point1[2]=0;

      point2[0]=0;
      point2[1]=g_axisLength;
      point2[2]=0;
    }else if(i==2){//z轴
      point1[0]=0;
      point1[1]=0;
      point1[2]=-g_axisLength;

      point2[0]=0;
      point2[1]=0;
      point2[2]=g_axisLength;
    }
    lineSource->SetPoint1(point1);
    lineSource->SetPoint2(point2);
    lineActor->GetProperty()->SetColor(g_normalColor[i][0],g_normalColor[i][1],g_normalColor[i][2]);
    lineActor->GetProperty()->SetLineWidth(g_axisLineWidth);

    //箭头
    vtkNew<vtkConeSource> coneSource1;
    vtkNew<vtkPolyDataMapper> coneMapper1;
    vtkNew<vtkActor> coneActor1;
    coneSource1->SetHeight( 0.2 );
    coneSource1->SetRadius( 0.04 );
    coneSource1->SetResolution( 10 );
    coneMapper1->SetInputConnection(coneSource1->GetOutputPort());
    coneActor1->SetMapper(coneMapper1);

    coneActor1->GetProperty()->SetColor(g_normalColor[i][0],g_normalColor[i][1],g_normalColor[i][2]);
    coneSource1->SetCenter(point2);

    if(i==0){//x轴

    }else if(i==1){//y轴
      coneActor1->SetOrigin(point2);
      coneActor1->RotateZ(90);
    }else if(i==2){//z轴
      coneActor1->SetOrigin(point2);
      coneActor1->RotateY(-90);
    }
    //
    vtkNew<vtkConeSource> coneSource2;
    vtkNew<vtkPolyDataMapper> coneMapper2;
    vtkNew<vtkActor> coneActor2;
    coneSource2->SetHeight( 0.2 );
    coneSource2->SetRadius( 0.04 );
    coneSource2->SetResolution( 30 );
    coneMapper2->SetInputConnection(coneSource2->GetOutputPort());
    coneActor2->SetMapper(coneMapper2);

    coneActor2->GetProperty()->SetColor(g_normalColor[i][0],g_normalColor[i][1],g_normalColor[i][2]);
    coneSource2->SetCenter(point1);

    if(i==0){//x轴
      coneActor2->SetOrigin(point1);
      coneActor2->RotateY(180);

      this->AxisPolygonSource[i]->SetNormal(1,0,0);
    }else if(i==1){//y轴
      coneActor2->SetOrigin(point1);
      coneActor2->RotateZ(-90);

      this->AxisPolygonSource[i]->SetNormal(0,1,0);
    }else if(i==2){//z轴
      coneActor2->SetOrigin(point1);
      coneActor2->RotateY(90);

      this->AxisPolygonSource[i]->SetNormal(0,0,1);
    }

    this->HandleAxis[i] = vtkAssembly::New();
    this->HandleAxis[i]->AddPart(lineActor);
    this->HandleAxis[i]->AddPart(coneActor1);
    this->HandleAxis[i]->AddPart(coneActor2);

    vtkNew<vtkMatrix4x4> initMatrix;
    this->HandleAxis[i]->SetUserMatrix(initMatrix);
  }

  //坐标轴拾取
  this->AxisPicker = vtkCellPicker::New();
  this->AxisPicker->SetTolerance(0.001);
  for (int i=0; i<3; i++)
  {
      this->AxisPicker->AddPickList(this->HandleAxis[i]);
  }
  this->AxisPicker->PickFromListOn();
  //
 
  // Internal data members for performance
  this->Transform = vtkTransform::New();
  this->PlanePoints = vtkPoints::New(VTK_DOUBLE);
  this->PlanePoints->SetNumberOfPoints(6);
  this->PlaneNormals = vtkDoubleArray::New();
  this->PlaneNormals->SetNumberOfComponents(3);
  this->PlaneNormals->SetNumberOfTuples(6);
  this->Matrix = vtkMatrix4x4::New();
}

void vtkCustomRepresentation::BuildRepresentation() {
  if (this->GetMTime() > this->BuildTime ||
    (this->Renderer && this->Renderer->GetVTKWindow() &&
      (this->Renderer->GetVTKWindow()->GetMTime() > this->BuildTime ||
        this->Renderer->GetActiveCamera()->GetMTime() > this->BuildTime)))
  {
    this->SizeHandles();
    this->BuildTime.Modified();
  }
}

void vtkCustomRepresentation::SizeHandles() {}
