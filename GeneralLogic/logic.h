#ifndef LOGIC_H
#define LOGIC_H

#include "mainwindow.h"
#include "logSys.h"
#include "treeWidgetManager.h"
#include "viewerControl.h"

class MainWindow;

class Logic : public QObject{
    Q_OBJECT
public:
    explicit Logic();
    ~Logic();
    int initUI();

    // MainWindow
    int setPtr(void* pMainWindow);
    int bindUi();

    // ViewerControl
    int initViewerControl();

    int initViewer();
    int appendModel2Viewer(Model* model);

    // ModelMgr
    int initModelMgr();
    int addModel();

    // LogSys
    int initLogSys();

    // TreeWidgetMgr
    int initTreeWidgetMgr();

    // General
signals:

public slots:
    // void showModelSlot();
    void traverseModelSlot();
    void initSlot();

public:
    LogSys* m_pLogSys = nullptr;
    TreeWidgetManager* m_pTreeWidgetMgr = nullptr;
    ModelManager* m_pModelMgr = nullptr;
    MainWindow* m_pMainWindow = nullptr;
    ViewerControl* m_pViewerControl = nullptr;
};

#endif