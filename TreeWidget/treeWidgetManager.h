#ifndef TREE_WIDGET_MANAGER_H
#define TREE_WIDGET_MANAGER_H

#include "treeWidgetManager.h"
#include "modelManager.h"

#include <QMenu>
#include <QAction>
#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QCheckBox>
#include <QStyleFactory>

class TreeWidgetManager : public QObject{
  Q_OBJECT
public:
  TreeWidgetManager(ModelManager* pModelMgr, QTreeWidget* pTreeWidget);
  ~TreeWidgetManager();

  int UpdateItemCheck(QTreeWidgetItem* pItem);

  QTreeWidget* m_pTreeWidget = nullptr;
  ModelManager* m_pModelMgr = nullptr;
  QTreeWidgetItem* m_pRootItem = nullptr;

signals:
  void DeleteModel2ModelMgrSig(QString sModelName);

public slots:
  void AddTreeNodeSlot(Model* pModel);
  void ShowContexMenu(const QPoint &pos);
  void CheckTreeItemSlot(Model* pModel);
  void UncheckTreeItemSlot(Model* pModel);
};

#endif