#include "./ui_mainwindow.h"
#include "mainWin.h"

#include <QMainWindow>
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
#include <QtQuickWidgets/QtQuickWidgets>
#include <QTreeView>

MainWindow::MainWindow(QWidget* parent) 
    : QMainWindow(parent),
      m_pUi(new Ui::MainWindow),
      m_pModelManager(new modelManager()),
      m_pLogSys(new LogSys()),
      m_pTreeWidgetManager(new treeWidgetManager()),
      m_pModelViewer(new modelViewer())
{
    m_pUi->setupUi(this);

    initUi();
    
    // 把textOutput控件给LogSys进行管理
    initLogSys();

    // 初始化按钮的图标
    initButtonIcon();

    // 初始化树形结构
    initTreeWidget();

    // 绑定信号槽
    bindUi();

}

MainWindow::~MainWindow()
{
    delete m_pUi;
}

int MainWindow::initUi(){
    return 0;
}

int MainWindow::bindTask()
{

    return 0;
}

int MainWindow::bindUi()
{
    // 绑定打开文件的操作
    connect(m_pUi->actionopen_file, SIGNAL(triggered()), this, SLOT(readModel()));
    connect(m_pUi->openFileButton, SIGNAL(clicked()), this, SLOT(readModel()));

    // 绑定优化按钮
    
    // 绑定清空log栏
    connect(m_pUi->clearLogButton, SIGNAL(clicked()), m_pUi->logTextOutput, SLOT(clear()));
    // 绑定保存log栏
    connect(m_pUi->clearLogButton, SIGNAL(clicked()), m_pLogSys, SLOT(saveLog()));
    // 绑定modelManager日志打印输出
    connect(m_pModelManager, SIGNAL(logOutputSig(QString)), m_pLogSys, SLOT(outputLog(QString)));
    // 绑定TreeWidgetManager的日志打印输出
    connect(m_pTreeWidgetManager, SIGNAL(logOutputSig(QString)), m_pLogSys, SLOT(outputLog(QString)));
    // 绑定删除选中model的按钮
    connect(m_pUi->clearModelButton, SIGNAL(clicked()), m_pTreeWidgetManager, SLOT(deleteModel()));
    return 0;
}

int MainWindow::initButtonIcon()
{
    m_pUi->openFileButton->setIcon(QIcon(":/icons/download12/folder-open.svg"));
    m_pUi->openFileButton->setFlat(true);
    m_pUi->clearLogButton->setIcon(QIcon(":/icons/download12/clear-format.svg"));
    m_pUi->clearLogButton->setFlat(true);
    m_pUi->saveLogButton->setIcon(QIcon(":/icons/download12/save.svg"));
    m_pUi->saveLogButton->setFlat(true);
    m_pUi->optimizeOriButton->setIcon(QIcon(":/icons/download12/lightning.svg"));
    m_pUi->optimizeOriButton->setFlat(true);
    m_pUi->setBottomButton->setIcon(QIcon(":/icons/download12/magic-wand.svg"));
    m_pUi->setBottomButton->setFlat(true);
    m_pUi->clearModelButton->setIcon(QIcon(":/icons/download12/clear.svg"));
    m_pUi->clearModelButton->setFlat(true);
    return 0;
}

int MainWindow::initLogSys()
{
    if(m_pLogSys->initLogSys(m_pUi->logTextOutput) == -1) return -1;
    return 0;
}

int MainWindow::initTreeWidget()
{
    if(m_pTreeWidgetManager->initTreeWidgetManager(m_pUi->treeWidget, m_pModelManager) == -1){
        return -1;
    }
    return 0;
}

void MainWindow::readModel()
{
    // 选择文件读取
    QFileDialog* qfd = new QFileDialog(this);
    qfd->setAttribute(Qt::WA_DeleteOnClose); // 对话框关闭时，自动销毁对话框的内存,避免内存泄漏
    QString sFilePath = qfd->getOpenFileName(this, "打开文件", "/mnt/e/stlFile/", "(*.stl *.STL *.conf *.CONF)");
    if(sFilePath.mid(sFilePath.indexOf('.')).toLower() == QString(".stl")){
        m_pModelManager->initModel(sFilePath);
    }
    return;
}

void MainWindow::deactivateModel()
{
}

void MainWindow::activateModel()
{
}

// void MainWindow::clearLog()
// {

// }

// void MainWindow::logOutput(QString msg)
// {
//     std::cout << msg.toStdString();
//     QString strDateTime = QDateTime::currentDateTime().toString("HH:mm:ss");
//     QString output = strDateTime + ':' + msg;
//     m_pUi->logTextOutput->insertPlainText(output);
//     return;
// }
