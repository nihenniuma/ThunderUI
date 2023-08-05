#include "logic.h"

Logic::Logic()
  : m_pViewerControl(new ViewerControl())
{

}

Logic::~Logic() {
    

}

int Logic::initUI() {
    return 0;
}

int Logic::bindUi() {
    if(m_pMainWindow == nullptr){
        qDebug() << __FUNCTION__ << "m_pMainWindow is nullptr!";
        return -1;
    }
    // 绑定打开文件的操作
    connect(m_pMainWindow->m_pUi->actionopen_file, &QAction::triggered, this, &Logic::addModel);
    connect(m_pMainWindow->m_pUi->openFileButton, &QPushButton::clicked, this, &Logic::addModel);
    
    // 绑定清空log栏
    connect(m_pMainWindow->m_pUi->clearLogButton, &QPushButton::clicked, m_pMainWindow->m_pUi->logTextOutput, &QTextBrowser::clear);
    // 绑定保存log栏
    connect(m_pMainWindow->m_pUi->clearLogButton, SIGNAL(QPushButton::clicked()), m_pLogSys, SLOT(LogSys::saveLog()));
    // 绑定删除选中model的按钮
    connect(m_pMainWindow->m_pUi->clearModelButton, &QPushButton::clicked, m_pTreeWidgetMgr, &TreeWidgetManager::deleteModel);
    // qDebug() << __FUNCTION__ << "connect!";
    // connect(m_pModelMgr, SIGNAL(showModelSig(Model& model)), m_pViewer, SLOT(showModelSlot(Model& model)));
    connect(m_pModelMgr, SIGNAL(traverseModelSig()), this, SLOT(traverseModelSlot()));
}

int Logic::initViewerControl() {
    return 0; 
}

int Logic::addModel() {
    // 选择文件读取
    QFileDialog* qfd = new QFileDialog(m_pMainWindow);
    qfd->setAttribute(Qt::WA_DeleteOnClose); // 对话框关闭时，自动销毁对话框的内存,避免内存泄漏
    QString sFilePath = qfd->getOpenFileName(m_pMainWindow, "打开文件", "/mnt/e/stlFile/", "(*.stl *.STL *.conf *.CONF)");
    if(sFilePath.mid(sFilePath.indexOf('.')).toLower() == QString(".stl")){
        if(m_pModelMgr->initAndAddModel(sFilePath) != 0){
            qDebug() << __FUNCTION__ << "addModel Fail!";
            return -1;
        }else{
            qDebug() << __FUNCTION__ << "addModel success!";
        }
        return 0;
    }else{
        // .conf
        QFile qf(sFilePath);
        qf.open(QIODevice::ReadOnly);
        QTextStream qts(&qf);
        QStringList sList = qts.readAll().split('\n');
        for(QString iter : sList){
            if(m_pModelMgr->initAndAddModel(iter) != 0){
                qDebug() << __FUNCTION__ << "addModel Fail!";
            }else{
                qDebug() << __FUNCTION__ << "addModel success!";
            }
        }
        return 0;
    }
    // vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
	// vtkSmartPointer<vtkSTLReader> reader1 = vtkSmartPointer<vtkSTLReader>::New();
	// reader->SetFileName("ghost.stl");
	// reader1->SetFileName("dice.stl");
	// reader->Update();
	// reader1->Update();

	// // 创建渲染器、渲染窗口和交互器
	// vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	// vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	// renderWindow->AddRenderer(renderer);
	// vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	// interactor->SetRenderWindow(renderWindow);

	// // 创建vtkPolyDataMapper和vtkActor
	// vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	// vtkSmartPointer<vtkPolyDataMapper> mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
	// mapper->SetInputConnection(reader->GetOutputPort());
	// mapper1->SetInputConnection(reader1->GetOutputPort());
	// vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	// vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
	// actor->SetMapper(mapper);
	// actor1->SetMapper(mapper1);
	// actor->SetPosition(0.5, 0.5, 0.5);

	// // 将actor添加到渲染器中
	// renderer->AddActor(actor);
	// renderer->AddActor(actor1);

	// // 设置背景颜色
	// renderer->SetBackground(0.2, 0.3, 0.4);

	// // 渲染和启动交互
	// renderWindow->Render();
	// interactor->Start();
}

int Logic::initModelMgr() {

    return 0; 
}

int Logic::initLogSys() {
    if(m_pLogSys->initLogSys(m_pMainWindow->m_pUi->logTextOutput) == -1) return -1;
    return 0; 
}

int Logic::initTreeWidgetMgr() {
    if(m_pTreeWidgetMgr == nullptr){
        qDebug() << __FUNCTION__ << "m_pTreeWidgetMgr is nullptr!";
        return -1;
    }
    if(m_pTreeWidgetMgr->initTreeWidgetManager(m_pMainWindow->m_pUi->treeWidget, m_pModelMgr) == -1){
        qDebug() << __FUNCTION__ << "m_pTreeWidgetMgr->initTreeWidgetManager failed!";
        return -1;
    }
    return 0; 
}

void Logic::initSlot() {
    if(initModelMgr() == -1){
        qDebug() << __FUNCTION__ << "initModelMgr failed!";
        return;
    }else{
        qDebug() << __FUNCTION__ << "initModelMgr success!";
    }

    if(initLogSys() == -1){
        qDebug() << __FUNCTION__ << "initTreeWidgetMgr failed!";
        return;
    }else{
        qDebug() << __FUNCTION__ << "initTreeWidgetMgr success!";
    }

    if(initTreeWidgetMgr() == -1){
        qDebug() << __FUNCTION__ << "initTreeWidgetMgr failed!";
        return;
    }else{
        qDebug() << __FUNCTION__ << "initTreeWidgetMgr success!";
    }

    if(initLogSys() == -1){
        qDebug() << __FUNCTION__ << "initLogSys failed!";
        return;
    }else{
        qDebug() << __FUNCTION__ << "initLogSys success!";
    }

    if(initViewer() == -1){
        qDebug() << __FUNCTION__ << "initViewer failed!";
        return;
    }else{
        qDebug() << __FUNCTION__ << "initViewer success!";
    }
}

int Logic::setPtr(void* pMainWindow) { 
    if(pMainWindow == nullptr){
        qDebug() << __FUNCTION__ << "Ptr sent was nullptr!";
        return -1;
    }
    m_pMainWindow = reinterpret_cast<MainWindow*>(pMainWindow);
    bindUi();
    return 0; 
}

void Logic::traverseModelSlot(){
    if(m_pModelMgr == nullptr){
        qDebug() << __FUNCTION__ << "m_pModelMgr is nullptr!";
        return;
    }
    qDebug() << __FUNCTION__ << "m_pModelMgr exists";
    QVector<Model*> vModels;
    m_pModelMgr->traverseModel(vModels);
    qDebug() << __FUNCTION__ << QString("vModels.size = %1").arg(vModels.size());
    if(m_pViewer == nullptr){
        qDebug() << __FUNCTION__ << "m_pViewer is nullptr!";
        return;
    }
    qDebug() << __FUNCTION__ << "m_pViewer exists";
    m_pViewer->appendModel2Screen(vModels);
}