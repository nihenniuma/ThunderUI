#include "treeWidgetManager.h"
#include <iostream>

TreeWidgetManager::TreeWidgetManager()
    : m_pTreeWidget(nullptr)
    , m_pModelMgr(nullptr)
    , m_pTopTreeNode(nullptr)
{
}

TreeWidgetManager::TreeWidgetManager(ModelManager * pModelMgr)
    : m_pTreeWidget(nullptr)
    , m_pModelMgr(pModelMgr)
    , m_pTopTreeNode(nullptr)
{
}

TreeWidgetManager::TreeWidgetManager(QTreeWidget *treeWidget)
    : m_pTreeWidget(treeWidget)
    , m_pModelMgr(nullptr)
    , m_pTopTreeNode(nullptr)
{
}

TreeWidgetManager::~TreeWidgetManager()
{
}

int TreeWidgetManager::bind(){
    // connect(m_pModelMgr, SIGNAL(addNodeSig(QString, QTreeWidgetItem*)), this, SLOT(addNode(QString, QTreeWidgetItem*)));
    connect(m_pTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(setItemStatus(QTreeWidgetItem*, int)));
    // connect(this, SIGNAL(removeModelSig(QString)), m_pModelMgr, SLOT(removeModel(QString)));
    return 0;
}

// 该函数实现的功能是子节点全打上勾，父节点打钩，全空，父节点为空
int TreeWidgetManager::setParentStatus(QTreeWidgetItem *item)
{
    QTreeWidgetItem* parent = item->parent();
    if (parent == nullptr) {
        return -1;
    }
    int num = parent->childCount();
    if(num == 0) {
        return -1;
    }
    
    int count = 0;
    for(int i = 0; i < num; ++i) {
        if(parent->child(i)->checkState(0) == Qt::Checked){
            ++count;
        }
    }
    if(count == 0){
        // 说明全是unChecked
        parent->setCheckState(0, Qt::Unchecked);
    }else if(count == num){
        parent->setCheckState(0, Qt::Checked);
    }
    // 其他情况不变
    return 0;
}

void TreeWidgetManager::setItemStatus(QTreeWidgetItem* item, int col) {
    int num = item->childCount();
    if (item->checkState(0) == Qt::Unchecked) {
        for(int i = 0; i < num; ++i){
            item->child(i)->setCheckState(0, Qt::Unchecked);
        }
    }else if(item->checkState(0) == Qt::Checked) {
        for(int i = 0; i < num; ++i){
            item->child(i)->setCheckState(0, Qt::Checked);
        }
    }
    setParentStatus(item);
    return;
}

void TreeWidgetManager::deleteModel()
{
    // 这个函数拿到的是所有被选中，就是被单击到的（蓝色），而不是勾选的
    QList<QTreeWidgetItem*> resList = m_pTreeWidget->selectedItems();
    for(auto iter : resList){
        if(iter->text(0) == QString("Models")){
            break;
        }
        emit removeModelSig(iter->text(0));
        delete iter;
    }
}

int TreeWidgetManager::initTreeWidgetManager(QTreeWidget *pTreeWidget, ModelManager* pModelManager)
{
    if(pTreeWidget == nullptr){
        qDebug() << __FUNCTION__ << "pTreeWidget input is nullptr!";
        return -1;
    }
    if(pModelManager == nullptr){
        qDebug() << __FUNCTION__ << "pModelMgr input is nullptr!";
        return -1;
    }
    
    m_pTreeWidget = pTreeWidget;
    m_pModelMgr = pModelManager;
    // 初始化一个顶层节点，接下来的模型都放置在其下
    m_pTopTreeNode = new QTreeWidgetItem(pTreeWidget);
    m_pTopTreeNode->setText(0, "Models");
    m_pTopTreeNode->setCheckState(0, Qt::Checked);
    // 信号槽绑定
    bind();
    return 0;
}

int TreeWidgetManager::setTreeNode()
{
    return 0;
}

int TreeWidgetManager::addNode(QString sModelName, QTreeWidgetItem* iNewTreeItem){
    // std::cout << "settxt" << std::endl;
    if (m_pModelMgr == nullptr) {
        return -1;
    }
    if (m_pModelMgr->isModelExist(sModelName)) {
        return -1;
    }
    if (m_pTopTreeNode == nullptr) {
        return -1;
    }
    if(iNewTreeItem == nullptr) {
        return -1;
    }
    iNewTreeItem->setText(0, sModelName);
    iNewTreeItem->setCheckState(0, Qt::Checked);
    m_pTopTreeNode->addChild(iNewTreeItem);
    m_pTreeWidget->expandAll();
    return 0;
}
