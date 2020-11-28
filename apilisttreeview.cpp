#include "apilisttreeview.h"
#include "httputil.h"

#include <QDebug>

ApiListTreeView::ApiListTreeView():
    m_pMenu(nullptr),
    m_pAddServer(nullptr),
    m_pAddApi(nullptr),
    m_pTestApi(nullptr),
    m_pTestAll(nullptr),
    m_pServerConfigDialog(nullptr),
    m_pModel(nullptr),
    m_pApiConfigDialog(nullptr),
    m_pItemDelegate(nullptr)
{
    m_pMenu = new QMenu();
    m_pAddServer = new QAction("添加服务");
    m_pAddApi = new QAction("添加接口");
    m_pTestApi = new QAction("测试当前接口");
    m_pTestAll = new QAction("测试所有接口");
    m_pAddApi->setEnabled(false);
    m_pTestApi->setEnabled(false);
    m_pTestAll->setEnabled(false);

    m_pMenu->addAction(m_pAddServer);
    m_pMenu->addAction(m_pAddApi);
    m_pMenu->addAction(m_pTestApi);
    m_pMenu->addAction(m_pTestAll);

    m_pModel = new ApiModel();

    m_pItemDelegate = new ApiItemDelegate();

    this->setModel(m_pModel);
    this->setItemDelegate(m_pItemDelegate);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(OnItemClicked(const QModelIndex &)));
    connect(m_pAddServer, SIGNAL(triggered(bool)), this, SLOT(OnAddServer()));
    connect(m_pAddApi, SIGNAL(triggered(bool)), this, SLOT(OnAddApi()));
    connect(m_pTestApi, SIGNAL(triggered(bool)), this, SLOT(OnTestApi()));
    connect(m_pTestAll, SIGNAL(triggered(bool)), this, SLOT(OnTestAll()));
}

ApiListTreeView::~ApiListTreeView() {
    delete m_pMenu;
    delete m_pModel;
    delete m_pAddServer;
    delete m_pAddApi;
    delete m_pServerConfigDialog;
    delete m_pApiConfigDialog;
}

void ApiListTreeView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_selectedIndex = indexAt(event->pos());
        if (m_selectedIndex.isValid()) {
            int row = m_selectedIndex.row();
            int col = m_selectedIndex.column();
            qDebug() << "mousePress row:" << row << " col:" << col << " rowCount:" << m_pModel->rowCount() << " columnCount:" << m_pModel->columnCount();
            if (m_selectedIndex.flags())
            expand(m_selectedIndex);
        }
    }
    event->ignore();
}

void ApiListTreeView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        m_selectedIndex = indexAt(event->pos());
        if (m_selectedIndex.isValid()) {
            m_pAddApi->setEnabled(true);
        } else {
            m_pAddApi->setEnabled(false);
        }
        if (m_selectedIndex.isValid() && m_selectedIndex.parent().isValid()) {
            m_pTestApi->setEnabled(true);
            m_pTestAll->setEnabled(true);
        } else {
            m_pTestApi->setEnabled(false);
            m_pTestAll->setEnabled(false);
        }
        m_pMenu->exec(event->globalPos());
    }
    if (event->button() == Qt::LeftButton) {
    }
    event->ignore();
}

void ApiListTreeView::OnItemClicked(const QModelIndex &index) {
    int row = index.row();
    int col = index.column();
    qDebug() << "OnItemClicked row:" << row << " col:" << col << " rowCount:" << m_pModel->rowCount();
}

void ApiListTreeView::OnAddServer() {
    //弹出服务名称配置窗口
    if (nullptr == m_pServerConfigDialog) {
        m_pServerConfigDialog = new ServerConfigDialog();
    }
    int nRet = m_pServerConfigDialog->exec();
    if (nRet == QDialog::Accepted) {
        QString serverName = m_pServerConfigDialog->GetServerName();
        ApiItem *serverItem = new ApiItem(serverName);
        ApiItem *serverDesc = new ApiItem(m_pServerConfigDialog->GetServerDesc());
        m_pModel->appendRow(serverItem);
        m_pModel->setItem(serverItem->index().row(), 1, serverDesc);
        m_vecServerItems.push_back(serverItem);
    }
}

void ApiListTreeView::OnAddApi() {
    //弹出接口配置窗口
    if (nullptr == m_pApiConfigDialog) {
        m_pApiConfigDialog = new ApiConfigDialog();
    }
    int nRet = m_pApiConfigDialog->exec();
    if (nRet == QDialog::Accepted) {
        QString apiName = m_pApiConfigDialog->GetApiName();
        QString apiUrl = m_pApiConfigDialog->GetUrl();
        ApiItem *apiItem = new ApiItem(apiName);
        apiItem->SetHttpUrl(m_pApiConfigDialog->GetUrl());
        apiItem->SetRequestType(m_pApiConfigDialog->GetRequestType());
        ApiItem *urlItem = new ApiItem(apiUrl);
        int row = m_selectedIndex.row();
        if (m_selectedIndex.parent().isValid()) {
            row = m_selectedIndex.parent().row();
        }
        if (m_vecServerItems.size() > row) {
            m_vecServerItems[row]->appendRow(apiItem);
            m_vecServerItems[row]->setChild(apiItem->index().row(), 1, urlItem);
        }
        if (m_vvecApiItems.size() < (row + 1)) {
            QVector<ApiItem*> vecItems;
            vecItems.push_back(apiItem);
            m_vvecApiItems.push_back(vecItems);
        } else {
            m_vvecApiItems[row].push_back(apiItem);
        }
    }
}

void ApiListTreeView::OnTestApi() {
    if (m_selectedIndex.parent().isValid()) {
        int parentRow = m_selectedIndex.parent().row();
        int row = m_selectedIndex.row();
        qDebug() << "parent row:" << parentRow;
        ApiItem *item = m_vvecApiItems[parentRow][row];
        qDebug() << "item name:" << (item != nullptr ? item->text() : "为空");
        if (item != nullptr) {
            QString url = item->GetHttpUrl();
            int requestType = item->GetRequestType();
            int paramsType = item->GetParamsType();
            if (requestType == REQUEST_GET) {
                qDebug() << "url:" << url;
                HttpUtil::Instance()->DoGet(url, requestType, paramsType);
                bool testResult = HttpUtil::Instance()->GetRequestResult();
                qDebug() << "get result:" << testResult;
                item->SetTestResult(testResult);
            }
        }
    }
}

void ApiListTreeView::OnTestAll() {

}


