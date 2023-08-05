#ifndef MAIN_WIN_H
#define MAIN_WIN_H

#include "viewer.h"
#include "./ui_mainwindow.h"
#include "modelManager.h"
#include "logSys.h"
#include "treeWidgetManager.h"
#include "logic.h"

#include <QMainWindow>
#include <QButtonGroup>
#include <QTextBrowser>
#include <QToolBar>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <string>
#include <QVBoxLayout>
#include <QTreeView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Logic;
class Viewer;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    int initLogic();
    int bindTask();
    int bindUi();
    int initButtonIcon();
    int initLogSys();
    int initTreeWidget();
    int initViewer();
    int initUi();
    int createLogic();
    void msgOutput(QString msg);

signals:
    void readModelSig();
    void deactivateModelSig();
    void activateModelSig();
    void deleteModelSig();
    void clearLogSig();
    void showModelSig();
    void appendTextSig(QString);
    void initSig();

public slots:
    void readModel();
    void deactivateModel();
    void activateModel();
    // void deleteModel(); // 删除的话需要删掉树状结构里的模型和模型管理类中的模型数据
    // void clearLog();
    // void logOutput(QString msg);

public:
    Logic* m_pLogic = nullptr;
    ModelManager* m_pModelManager = nullptr;
    LogSys* m_pLogSys = nullptr;
    TreeWidgetManager* m_pTreeWidgetManager = nullptr;
    Viewer* m_pViewer = nullptr;
    Ui::MainWindow *m_pUi = nullptr;
};

#endif