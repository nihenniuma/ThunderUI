#ifndef VIEWER_H
#define VIEWER_H

#include "modelManager.h"
//#include "ui_viewer.h"
// #include "logic.h"

#include <QDebug>
#include <QVTKWidget.h>
#include <vtkSTLReader.h>
#include <vtkRenderer.h>
#include <vtkRenderView.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkSmartPointer.h>
#include <vtkConeSource.h>

class Viewer : public QWidget{
    Q_OBJECT

public:
    explicit Viewer(QWidget* parent = nullptr);
    ~Viewer();

    int initViewer(QVTKWidget* pVTKWidget);
    int setVTKWidget(QVTKWidget* pVTKWidget);

    // showModel
    int show();
    int showModel();
    int appendModel2Screen(QVector<Model*> vModels);
    int appendModel2Screen(Model* model);

    QVTKWidget* m_pVTKWidget = nullptr;
    QMap<QString, Model> m_CurViewMap;

public slots:
    // void showModelSlot(Model& model);

private:
    ModelManager* m_pModelManager = nullptr;
    vtkSmartPointer<vtkRenderer> m_pRenderer = nullptr;
    // vtkSmartPointer<vtkSTLReader> m_pSTLReader = nullptr;
};

#endif
