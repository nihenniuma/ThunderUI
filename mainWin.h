#ifndef MAIN_WIN_H
#define MAIN_WIN_H

#include "modelManager.h"
#include "logSys.h"
#include "treeWidgetManager.h"
#include "modelViewer.h"

#include <QMainWindow>
#include <QButtonGroup>
#include <QTextBrowser>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    int bindTask();
    int bindUi();
    int initButtonIcon();
    int initLogSys();
    int initTreeWidget();
    int initUi();

signals:
    void readModelSig();
    void deactivateModelSig();
    void activateModelSig();
    void deleteModelSig();
    void clearLogSig();

public slots:
    void readModel();
    void deactivateModel();
    void activateModel();
    // void deleteModel(); // 删除的话需要删掉树状结构里的模型和模型管理类中的模型数据
    // void clearLog();
    // void logOutput(QString msg);

public:
    modelManager* m_pModelManager;
    LogSys* m_pLogSys;
    treeWidgetManager* m_pTreeWidgetManager;
    modelViewer* m_pModelViewer;
private:
    Ui::MainWindow *m_pUi;
};

#endif
