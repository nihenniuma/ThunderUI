#include "mainwindow.h"

QString MainWindow::sTextBrowserLogFile = "LogFromTextBrowser.log";
Ui::MainWindow* MainWindow::m_pUi = new Ui::MainWindow();
QMutex* MainWindow::mutex = new QMutex();

MainWindow::MainWindow(QWidget* parent) 
  : QMainWindow(parent)
  , m_pLogSys(new LogSys())
  , m_pModelMgr(new ModelManager())
  , m_pBridge(new Bridge())
  , m_pViewerControl(new ViewerControl(this, m_pModelMgr, m_pBridge))
{
  m_pUi->setupUi(this);
  qInstallMessageHandler(MsgRedirection);

  m_pTreeWidgetManager = new TreeWidgetManager(m_pModelMgr, m_pUi->treeWidgetModels);
  // 初始化按钮的图标
  initButtonIcon();
  bindUI();
  m_pUi->ViewerLayout->addWidget(m_pViewerControl);
  // show vtk
}

MainWindow::~MainWindow(){
  qInstallMessageHandler(nullptr);
  if(m_pLogSys != nullptr){
    delete m_pLogSys;
  }

  if(m_pViewerControl != nullptr){
    delete m_pViewerControl;
  }

  if(m_pModelMgr != nullptr){
    delete m_pModelMgr;
  }
}

int MainWindow::initUi(){
  if(initButtonIcon() == -1){
    qDebug() << __FUNCTION__ << "init failed!";
    return -1;
  }
  qDebug() << __FUNCTION__ << "init successed!";
  return 0;
}

int MainWindow::bindTask() { return 0; }

int MainWindow::bindUI()
{
  // 绑定打开文件的操作
  connect(m_pUi->actionOpenFile, SIGNAL(triggered()), m_pViewerControl, SLOT(ReadModelSlot()));
  connect(m_pUi->actionOpenFile_2, SIGNAL(triggered()), m_pViewerControl, SLOT(ReadModelSlot()));

  // 绑定优化按钮
  
  // 绑定清空log栏
  connect(m_pUi->PushButtonClearLog, SIGNAL(clicked()), this, SLOT(ClearLogSlot()));
  // 绑定保存log栏
  connect(m_pUi->PushButtonSaveLog, SIGNAL(clicked()), this, SLOT(SaveLogSlot()));

  // add model & show model
  connect(m_pViewerControl, SIGNAL(ModelMgrAddModelSig(Model*)), m_pModelMgr, SLOT(ModelMgrAddModelSlot(Model*)));
  connect(m_pModelMgr, SIGNAL(ShowSig(Model*)), m_pViewerControl, SLOT(ShowSlot(Model*)));
  // center model
  connect(m_pUi->actionCenterModel, SIGNAL(triggered()), m_pViewerControl, SLOT(ResetCameraSlot()));
  // zoom in
  connect(m_pUi->actionZoomIn, SIGNAL(triggered()), m_pViewerControl, SLOT(ZoomInSlot()));
  // zoom out
  connect(m_pUi->actionZoomOut, SIGNAL(triggered()), m_pViewerControl, SLOT(ZoomOutSlot()));
  // screenshot
  connect(m_pUi->actionScreenShot, SIGNAL(triggered()), m_pViewerControl, SLOT(ScreenShotSlot()));

  // TreeWidget
  connect(m_pModelMgr, SIGNAL(AddTreeNodeSig(Model*)), m_pTreeWidgetManager, SLOT(AddTreeNodeSlot(Model*)));
  connect(m_pModelMgr, SIGNAL(CheckTreeItemSig(Model*)), m_pTreeWidgetManager, SLOT(CheckTreeItemSlot(Model*)));
  connect(m_pModelMgr, SIGNAL(UncheckTreeItemSig(Model*)), m_pTreeWidgetManager, SLOT(UncheckTreeItemSlot(Model*)));

  // delete model
  connect(m_pModelMgr, SIGNAL(DeleteShowModelSig(Model*)), m_pViewerControl, SLOT(DeleteShowModelSlot(Model*)));
  connect(m_pViewerControl, SIGNAL(TellModelMgrDeleteModelSig(Model*)), m_pModelMgr, SLOT(DeleteModelSlot(Model*)));

  connect(m_pViewerControl->m_pBridge, SIGNAL(FindModelPtrAndActivateSig(QString)), m_pModelMgr, SLOT(FindModelPtrAndActivateSlot(QString)));
  connect(m_pViewerControl->m_pBridge, SIGNAL(FindModelPtrAndDeactivateSig(QString)), m_pModelMgr, SLOT(FindModelPtrAndDeactivateSlot(QString)));
  return 0;
}

int MainWindow::initButtonIcon()
{
  m_pUi->PushButtonClearLog->setIcon(QIcon(":/icons/download12/clear-format.svg"));
  m_pUi->PushButtonClearLog->setFlat(true);
  m_pUi->PushButtonClearLog->setIconSize(QSize(50, 50));
  m_pUi->PushButtonSaveLog->setIcon(QIcon(":/icons/download12/save.svg"));
  m_pUi->PushButtonSaveLog->setFlat(true);
  m_pUi->PushButtonSaveLog->setIconSize(QSize(50, 50));
  return 0;
}

int MainWindow::initLogSys()
{
    if(m_pLogSys->initLogSys(m_pUi->textBrowser) == -1) return -1;
    return 0;
}

void MainWindow::AddModelSlot(){
}

void MainWindow::deactivateModel()
{
}

void MainWindow::activateModel()
{
}

void MainWindow::MsgRedirection(QtMsgType type, const QMessageLogContext &context, const QString &msg){
  // 加锁
  // mutex->lock();
  QByteArray localMsg = msg.toLocal8Bit();
  //信息分类
  QString strMsg("");
  switch(type)
  {
  case QtDebugMsg:
      strMsg = QString("Debug:");
      break;
  case QtInfoMsg:
      strMsg = QString("Info:");
      break;
  case QtWarningMsg:
      strMsg = QString("Warning:");
      break;
  case QtCriticalMsg:
      strMsg = QString("Critical:");
      break;
  case QtFatalMsg:
      strMsg = QString("Fatal:");
      break;

      default:
          break;
  }
  // 设置输出信息格式
  QString strDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
  QString strMessage = QString("%1 %2:%3").arg(strDateTime).arg(strMsg).arg(localMsg.constData());
  // 输出信息到UI
  m_pUi->textBrowser->append(strMessage);

  // 解锁
  mutex->unlock();
}

void MainWindow::ClearLogSlot(){
  if(m_pUi->textBrowser == nullptr){
    qDebug() << __FUNCTION__ << "m_pUi->textBrowser is nullptr!";
    return;
  }
  m_pUi->textBrowser->clear();
}

void MainWindow::SaveLogSlot(){
  if(m_pUi->textBrowser == nullptr){
    qDebug() << __FUNCTION__ << "m_pUi->textBrowser is nullptr!";
    return;
  }
  QFile f(sTextBrowserLogFile);
  f.open(QIODevice::WriteOnly);
  QString sLog = m_pUi->textBrowser->toPlainText();
  QTextStream out(&f);
  out << sLog;
  f.close();
  QMessageBox::information(this, QString("Cautions!"), QString("Log has been saved!"), QMessageBox::Ok);
}