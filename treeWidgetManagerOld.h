#ifndef TREE_WIDGET_H
#define TREE_WIDGET_H

#include "modelManager.h"

#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QCheckBox>

// class TreeWidgetManager : public QObject{
//     Q_OBJECT
// public:
//     TreeWidgetManager();
//     TreeWidgetManager(ModelManager* pModelMgr);
//     TreeWidgetManager(QTreeWidget* treeWidget);
//     ~TreeWidgetManager();

//     int initTreeWidgetManager(QTreeWidget* pTreeWidget, ModelManager* pModelManager);
//     int setTreeNode();
//     int bind();
//     int setParentStatus(QTreeWidgetItem* parent);
//     QTreeWidget* m_pTreeWidget;
//     ModelManager* m_pModelMgr;
//     QTreeWidgetItem* m_pTopTreeNode;

// signals:
//     void removeModelSig(QString sModelName);
//     // void logOutputSig(QString sMsg);

// public slots:
//     int addNode(QString sModelName, QTreeWidgetItem* iNewTreeItem);
//     // 用来实现点击外面的Models节点改变所有model的节点checkbox状态用的
//     void setItemStatus(QTreeWidgetItem*, int);
//     void deleteModel();
// };


#endif