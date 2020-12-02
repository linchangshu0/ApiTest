#ifndef APITREEVIEW_H
#define APITREEVIEW_H

#include "serverconfigdialog.h"
#include "apiconfigdialog.h"
#include "treemodel.h"
#include "treeitem.h"
#include "common.h"
#include "httputil.h"

#include <QTreeView>
#include <QMenu>
#include <QAction>
#include <QVector>
#include <QMouseEvent>

class ApiTreeView : public QTreeView
{
    Q_OBJECT

public:
    ApiTreeView();
    ~ApiTreeView();

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void OnAddServer();
    void OnAddApi();
    void OnTestApi();
    void OnTestAll();
    void OnDoubleClicked(const QModelIndex &index);

private:
    QMenu                   *m_pMenu;       //主菜单
    QAction                 *m_pAddServer;  //添加服务名称
    QAction                 *m_pAddApi;     //在服务下面添加API接口
    QAction                 *m_pTestApi;    //测试当前接口
    QAction                 *m_pTestAll;    //测试所有接口
    ServerConfigDialog      *m_pServerConfigDialog;
    TreeModel               *m_pModel;
    ApiConfigDialog         *m_pApiConfigDialog;
    QModelIndex             m_selectedIndex;
};

#endif // APITREEVIEW_H
