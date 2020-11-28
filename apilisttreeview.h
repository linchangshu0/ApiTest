#ifndef APILISTTREEVIEW_H
#define APILISTTREEVIEW_H

#include "serverconfigdialog.h"
#include "apiconfigdialog.h"
#include "apimodel.h"
#include "apiitemdelegate.h"
#include "apiitem.h"
#include "common.h"

#include <QTreeView>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QStandardItem>

class ApiListTreeView : public QTreeView
{
    Q_OBJECT

public:
    ApiListTreeView();
    ~ApiListTreeView();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void OnItemClicked(const QModelIndex &index);
    void OnAddServer();
    void OnAddApi();
    void OnTestApi();
    void OnTestAll();

private:
    QMenu                   *m_pMenu;       //主菜单
    QAction                 *m_pAddServer;  //添加服务名称
    QAction                 *m_pAddApi;     //在服务下面添加API接口
    QAction                 *m_pTestApi;    //测试当前接口
    QAction                 *m_pTestAll;    //测试所有接口
    ServerConfigDialog      *m_pServerConfigDialog;
    ApiModel                *m_pModel;
    QVector<ApiItem*>       m_vecServerItems;
    QVector<QVector<ApiItem*>> m_vvecApiItems;
    ApiConfigDialog         *m_pApiConfigDialog;
    QModelIndex             m_selectedIndex;
    ApiItemDelegate         *m_pItemDelegate;
};

#endif // APILISTTREEVIEW_H
