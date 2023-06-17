#ifndef TREE_WIDGET_H
#define TREE_WIDGET_H

#include "modelManager.h"

#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QCheckBox>

class treeWidgetManager : public QObject{
    Q_OBJECT
public:
    treeWidgetManager();
    treeWidgetManager(QTreeWidget* treeWidget);
    ~treeWidgetManager();

    int initTreeWidgetManager(QTreeWidget* m_pTreeWidget, modelManager* m_pModelManager);
    int setTreeNode();
    int bind();
    int setParentStatus(QTreeWidgetItem* parent);
    QTreeWidget* pTreeWidget;
    modelManager* pModelManager;
    QTreeWidgetItem* pTopTreeNode;

signals:
    void clearModelSig(QString sModelName);
    void logOutputSig(QString sMsg);

public slots:
    int addNode(QString sModelName, QTreeWidgetItem* iNewTreeItem);
    // 用来实现点击外面的Models节点改变所有model的节点checkbox状态用的
    void setItemStatus(QTreeWidgetItem*, int);
    void deleteModel();
};
#endif