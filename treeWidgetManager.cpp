#include "treeWidgetManager.h"
#include <iostream>

treeWidgetManager::treeWidgetManager()
    : pTreeWidget(nullptr),
    pModelManager(nullptr),
    pTopTreeNode(nullptr)
{
}

treeWidgetManager::treeWidgetManager(QTreeWidget *treeWidget)
    : pTreeWidget(treeWidget),
    pModelManager(nullptr),
    pTopTreeNode(nullptr)
{
}

treeWidgetManager::~treeWidgetManager()
{
}

int treeWidgetManager::bind(){
    connect(pModelManager, SIGNAL(addNodeSig(QString, QTreeWidgetItem*)), this, SLOT(addNode(QString, QTreeWidgetItem*)));
    connect(pTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(setItemStatus(QTreeWidgetItem*, int)));
    connect(this, SIGNAL(clearModelSig(QString)), pModelManager, SLOT(clearModel(QString)));
    return 0;
}

// 该函数实现的功能是子节点全打上勾，父节点打钩，全空，父节点为空
int treeWidgetManager::setParentStatus(QTreeWidgetItem *item)
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

void treeWidgetManager::setItemStatus(QTreeWidgetItem* item, int col) {
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

void treeWidgetManager::deleteModel()
{
    // 这个函数拿到的是所有被选中，就是被单击到的（蓝色），而不是勾选的
    QList<QTreeWidgetItem*> resList = pTreeWidget->selectedItems();
    for(auto iter : resList){
        if(iter->text(0) == QString("Models")){
            break;
        }
        emit clearModelSig(iter->text(0));
        delete iter;
    }
}

int treeWidgetManager::initTreeWidgetManager(QTreeWidget *m_pTreeWidget, modelManager* m_pModelManager)
{
    if(m_pTreeWidget == nullptr || m_pModelManager == nullptr) return -1;
    pTreeWidget = m_pTreeWidget;
    pModelManager = m_pModelManager;
    // 初始化一个顶层节点，接下来的模型都放置在其下
    pTopTreeNode = new QTreeWidgetItem(pTreeWidget);
    pTopTreeNode->setText(0, "Models");
    pTopTreeNode->setCheckState(0, Qt::Checked);
    // 信号槽绑定
    bind();
    return 0;
}

int treeWidgetManager::setTreeNode()
{
    return 0;
}

int treeWidgetManager::addNode(QString sModelName, QTreeWidgetItem* iNewTreeItem){
    // std::cout << "settxt" << std::endl;
    if (pModelManager == nullptr) {
        return -1;
    }
    if (pModelManager->isModelExist(sModelName) != 0) {
        return -1;
    }
    if (pTopTreeNode == nullptr) {
        return -1;
    }
    if(iNewTreeItem == nullptr) {
        return -1;
    }
    iNewTreeItem->setText(0, sModelName);
    iNewTreeItem->setCheckState(0, Qt::Checked);
    pTopTreeNode->addChild(iNewTreeItem);
    pTreeWidget->expandAll();
    return 0;
}
