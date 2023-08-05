#include "treeWidgetManager.h"

TreeWidgetManager::TreeWidgetManager(ModelManager* pModelMgr, QTreeWidget* pTreeWidget)
  : m_pModelMgr(pModelMgr)
  , m_pTreeWidget(pTreeWidget)
  , m_pRootItem(new QTreeWidgetItem(m_pTreeWidget, QStringList() << "All")){
  // init manager
  m_pTreeWidget->addTopLevelItem(m_pRootItem);
  m_pTreeWidget->setColumnCount(1);
  m_pRootItem->setCheckState(0, Qt::Checked);

  m_pTreeWidget->setStyle(QStyleFactory::create("windows"));

  // make children node status change as parent node changes
  connect(m_pTreeWidget, &QTreeWidget::itemChanged, 
    [&](QTreeWidgetItem* item, int column){
      if(column == 0){
        UpdateItemCheck(item);
      }
    }
  );

  m_pTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(m_pTreeWidget, &QTreeWidget::customContextMenuRequested, this, &TreeWidgetManager::ShowContexMenu);
  connect(this, SIGNAL(DeleteModel2ModelMgrSig(QString)), m_pModelMgr, SLOT(FindModelPtrSlot(QString)));
}

TreeWidgetManager::~TreeWidgetManager(){
  if(m_pTreeWidget != nullptr){
    if(m_pRootItem != nullptr){
      m_pTreeWidget->removeItemWidget(m_pRootItem, 0);
      delete m_pRootItem;
      m_pRootItem = nullptr;
    }
    m_pTreeWidget = nullptr;
  }

  if(m_pModelMgr != nullptr){
    m_pModelMgr = nullptr;
  }
}

int TreeWidgetManager::UpdateItemCheck(QTreeWidgetItem* pItem) {
  // get status of parent check
  Qt::CheckState state = pItem->checkState(0);

  // update all children's check to parent's
  for(int i = 0; i < pItem->childCount(); ++i){
    QTreeWidgetItem* childItem = pItem->child(i);
    childItem->setCheckState(0, state);
  }
  return 0;
}

void TreeWidgetManager::ShowContexMenu(const QPoint& pos) {
  QMenu contextMenu(m_pTreeWidget);

  QAction actionDelete("delete", m_pTreeWidget);
  connect(&actionDelete, &QAction::triggered, this,
    [&](){
      QList<QTreeWidgetItem*> ItemList = m_pTreeWidget->selectedItems();
      for(QTreeWidgetItem* pItem : ItemList){
        if(pItem == m_pRootItem){
          qDebug() << __FUNCTION__ << "Root item can't be deleted!";
          return;
        }
        m_pRootItem->removeChild(pItem);
        QString sModelName = pItem->text(0);
        emit DeleteModel2ModelMgrSig(sModelName);
      }
  });
  contextMenu.addAction(&actionDelete);

  contextMenu.exec(m_pTreeWidget->mapToGlobal(pos));
}

void TreeWidgetManager::CheckTreeItemSlot(Model* pModel) {
  if(pModel == nullptr){
    qDebug() << __FUNCTION__ << "pModel is nulllptr!";
    return;
  }
  QTreeWidgetItem* pItem = nullptr;
  if(pModel->getTreeWidgetItem(&pItem) != 0){
    qDebug() << __FUNCTION__ << "No TreeWidgetItem in pModel!";
    return;
  }

  if(pItem == nullptr){
    qDebug() << __FUNCTION__ << "pItem is nullptr!";
    return;
  }
  pItem->setCheckState(0, Qt::CheckState::Checked);

  // if(pModel->m_pTreeWidgetItem == nullptr){
  //   qDebug() << __FUNCTION__ << "pModel->m_pTreeWidgetItem is nullptr!";
  //   return;
  // }
  // pModel->m_pTreeWidgetItem->setCheckState(0, Qt::CheckState::Checked);
}

void TreeWidgetManager::UncheckTreeItemSlot(Model* pModel) {
  if(pModel == nullptr){
    qDebug() << __FUNCTION__ << "pModel is nulllptr!";
    return;
  }
  QTreeWidgetItem* pItem = nullptr;
  if(pModel->getTreeWidgetItem(&pItem) != 0){
    qDebug() << __FUNCTION__ << "No TreeWidgetItem in pModel!";
    return;
  }

  if(pItem == nullptr){
    qDebug() << __FUNCTION__ << "pItem is nullptr!";
    return;
  }
  pItem->setCheckState(0, Qt::CheckState::Unchecked);

  // if(pModel->m_pTreeWidgetItem == nullptr){
  //   qDebug() << __FUNCTION__ << "pModel->m_pTreeWidgetItem is nullptr!";
  //   return;
  // }
  // pModel->m_pTreeWidgetItem->setCheckState(0, Qt::CheckState::Unchecked);
}

void TreeWidgetManager::AddTreeNodeSlot(Model* pModel){
  if(pModel == nullptr){
    qDebug() << __FUNCTION__ << "pModel is nullptr. Add tree node failed!";
    return;
  }

  if(m_pRootItem == nullptr){
    qDebug() << __FUNCTION__ << "m_pRootItem is nullptr!";
    return;
  }
  // QTreeWidgetItem** ppItem = nullptr;
  QTreeWidgetItem* pItem = nullptr;
  if(pModel->getTreeWidgetItem(m_pRootItem, &pItem) != 0){
    qDebug() << __FUNCTION__ << "Can't get TreeWidgetItem from model!";
    return;
  }
  // if(ppItem == nullptr){
  //   qDebug() << __FUNCTION__ << "ppItem is nullptr!";
  //   return;
  // }

  // QTreeWidgetItem* pItem = *ppItem;
  if(pItem == nullptr){
    qDebug() << __FUNCTION__ << "pItem is nullptr!";
    return;
  }

  m_pRootItem->addChild(pItem);
  m_pRootItem->setExpanded(true);
}
