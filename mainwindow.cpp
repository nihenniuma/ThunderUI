#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) 
    : QMainWindow(parent),
      m_pUi(new Ui::MainWindow),
      m_pModelManager(new ModelManager()),
      m_pLogSys(new LogSys()),
      m_pTreeWidgetManager(new TreeWidgetManager())
{
    m_pUi->setupUi(this);
    initUi();

    // 初始化按钮的图标
    initButtonIcon();

    // create logic
    createLogic();
}

MainWindow::~MainWindow()
{
    delete m_pUi;
}

int MainWindow::initUi(){

    return 0;
}

int MainWindow::createLogic() {
    m_pLogic = new Logic();
    initLogic();
    return 0;
}

void MainWindow::msgOutput(QString msg) {
    if(msg.contains("Debug:")){
        msg = "<font color=\"#000000\">" + msg + "</font> ";
    }else if (msg.contains("Info:")) {
        msg = "<font color=\"#0000FF\">" + msg + "</font> ";
    }else if (msg.contains("Warning:")) {
        msg = "<font color=\"#FF00FF\">" + msg + "</font> ";
    }else if (msg.contains("Critical:")) {
        msg = "<font color=\"#FF0000\">" + msg + "</font> ";
    }else if (msg.contains("Fatal:")) {
        msg = "<font color=\"#FF0000\">" + msg + "</font> ";
    }else {
        msg = "<font color=\"#000000\">" + msg + "</font> ";
    }
    //不同线程直接调用会导致程序崩溃，改用信号槽的方式
    //ui->textEdit_msgOut->append(msg);
    emit appendTextSig(msg);
}

int MainWindow::initLogic(){
    m_pLogic->m_pLogSys = this->m_pLogSys;
    m_pLogic->m_pModelMgr = this->m_pModelManager;
    m_pLogic->m_pTreeWidgetMgr = this->m_pTreeWidgetManager;
    m_pLogic->m_pViewer = this->m_pViewer;
    m_pLogic->setPtr(reinterpret_cast<void*>(this));
    connect(this, SIGNAL(initSig()), m_pLogic, SLOT(initSlot()));
    emit initSig();
    return 0;
}

int MainWindow::bindTask() { return 0; }

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
    // connect(m_pModelManager, SIGNAL(logOutputSig(QString)), m_pLogSys, SLOT(outputLog(QString)));
    // 绑定TreeWidgetManager的日志打印输出
    // connect(m_pTreeWidgetManager, SIGNAL(logOutputSig(QString)), m_pLogSys, SLOT(outputLog(QString)));
    // 绑定删除选中model的按钮
    connect(m_pUi->clearModelButton, SIGNAL(clicked()), m_pTreeWidgetManager, SLOT(deleteModel()));
    // redirect log to textBrowser
    connect(this, &MainWindow::msgOutput, m_pUi->logTextOutput, &QTextBrowser::append);
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

int MainWindow::initViewer() { 
    m_pViewer = new Viewer();
    if(m_pUi != nullptr){
        m_pViewer->initViewer(m_pUi->qvtkWidget);
    }else{
        qDebug() << __FUNCTION__ << "Ui hasn't been initialized!";
        return -1;
    }
    return 0; 
}

void MainWindow::readModel()
{
    // // 选择文件读取
    // QFileDialog* qfd = new QFileDialog(this);
    // qfd->setAttribute(Qt::WA_DeleteOnClose); // 对话框关闭时，自动销毁对话框的内存,避免内存泄漏
    // QString sFilePath = qfd->getOpenFileName(this, "打开文件", "/mnt/e/stlFile/", "(*.stl *.STL *.conf *.CONF)");
    // if(sFilePath.mid(sFilePath.indexOf('.')).toLower() == QString(".stl")){
    //     m_pModelManager->addModel(sFilePath, );
    // }
    // emit showModelSig();
    // return;
}

void MainWindow::deactivateModel()
{
}

void MainWindow::activateModel()
{
}
