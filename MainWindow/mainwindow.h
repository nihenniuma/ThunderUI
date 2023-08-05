#ifndef MAIN_WIN_H
#define MAIN_WIN_H

// #include "viewer.h"
#include "ui_mainwindow.h"
#include "ModelViewerControl/viewerControl.h"
#include "LogSys/logSys.h"
#include "TreeWidget/treeWidgetManager.h"
#include "MainWindow/mainwindow.h"

#include <QMutex>
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

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    int bindTask();
    int bindUI();
    int initButtonIcon();
    int initLogSys();
    int initTreeWidget();
    int initUi();
    static void MsgRedirection(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
    void AddModelSig();
    void readModelSig();
    void deactivateModelSig();
    void activateModelSig();
    void deleteModelSig();
    void clearLogSig();
    void showModelSig();
    void appendTextSig(QString);
    void initSig();

public slots:
    void ClearLogSlot();
    void SaveLogSlot();
    void AddModelSlot();
    // void readModelSlot();
    void deactivateModel();
    void activateModel();

public:
    LogSys* m_pLogSys = nullptr;
    TreeWidgetManager* m_pTreeWidgetManager = nullptr;
    ViewerControl* m_pViewerControl = nullptr;
    ModelManager* m_pModelMgr = nullptr;
    Bridge* m_pBridge = nullptr;

    static QString sTextBrowserLogFile;
    static Ui::MainWindow *m_pUi;
    static QMutex* mutex;
};

#endif