#include "treeview.h"

#include <QFile>
#include <QDebug>
#include <QAbstractItemView>

ApiTreeView::ApiTreeView(): QTreeView (),
    m_pMenu(nullptr),
    m_pAddServer(nullptr),
    m_pAddApi(nullptr),
    m_pTestApi(nullptr),
    m_pTestAll(nullptr),
    m_pServerConfigDialog(nullptr),
    m_pModel(nullptr),
    m_pApiConfigDialog(nullptr)
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

    QStringList headers;
    headers << "Title" << "Description";

    QString filePath = APPLICATION_DIR + "/default.txt";
    qDebug() << "file:" << filePath;
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    m_pModel = new TreeModel(headers, file.readAll());
    file.close();

    this->setModel(m_pModel);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    setAlternatingRowColors(true);

    for (int column = 0; column < m_pModel->columnCount(); ++column)
        resizeColumnToContents(column);

    connect(m_pAddServer, SIGNAL(triggered(bool)), this, SLOT(OnAddServer()));
    connect(m_pAddApi, SIGNAL(triggered(bool)), this, SLOT(OnAddApi()));
    connect(m_pTestApi, SIGNAL(triggered(bool)), this, SLOT(OnTestApi()));
    connect(m_pTestAll, SIGNAL(triggered(bool)), this, SLOT(OnTestAll()));
    connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(OnDoubleClicked(const QModelIndex &)));
}

ApiTreeView::~ApiTreeView() {
    delete m_pMenu;
    delete m_pModel;
    delete m_pAddServer;
    delete m_pAddApi;
    delete m_pServerConfigDialog;
    delete m_pApiConfigDialog;
}

void ApiTreeView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_selectedIndex = indexAt(event->pos());
        if (m_selectedIndex.isValid()) {
            setCurrentIndex(m_selectedIndex);
            int row = m_selectedIndex.row();
            int col = m_selectedIndex.column();
            //qDebug() << "mousePress row:" << row << " col:" << col << " rowCount:" << m_pModel->rowCount() << " columnCount:" << m_pModel->columnCount();
            if (isExpanded(m_selectedIndex)) {
                collapse(m_selectedIndex);
            } else {
                expand(m_selectedIndex);
            }
        }
    }
    event->accept();
}

void ApiTreeView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        m_selectedIndex = indexAt(event->pos());
        if (m_selectedIndex.isValid()) {
            setCurrentIndex(m_selectedIndex);
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
    event->accept();
}

void ApiTreeView::OnAddServer() {
    //弹出服务名称配置窗口
    if (nullptr == m_pServerConfigDialog) {
        m_pServerConfigDialog = new ServerConfigDialog();
    }
    int nRet = m_pServerConfigDialog->exec();
    if (nRet == QDialog::Accepted) {
        QVariant serverName(m_pServerConfigDialog->GetServerName());
        QString serverDesc(m_pServerConfigDialog->GetServerDesc());

        int totalRow = m_pModel->rowCount();
        QModelIndex index = m_pModel->index(0, 0).parent();
        qDebug() << "totalRow:" << totalRow << " index:" << index.row() << " data:" << index.data().toString();
        if (m_pModel->insertRow(totalRow, index)) {
            QModelIndex child = m_pModel->index(totalRow, 0, index);
            QModelIndex child2 = m_pModel->index(totalRow, 1, index);
            if (!child.isValid()) {
                qDebug() << "add server child not valid.";
                return;
            }
            if (!child2.isValid()) {
                qDebug() << "add server child not valid.";
                return;
            }
            m_pModel->setData(child, serverName, Qt::EditRole);
            m_pModel->setData(child2, serverDesc, Qt::EditRole);
            m_pModel->setItemType(child, SERVER_ITEM);
            m_pModel->setItemType(child2, SERVER_ITEM);
        } else {
            qDebug() << "2.add server failed.";
        }
    }
}

void ApiTreeView::OnAddApi() {
    //弹出接口配置窗口
    if (nullptr == m_pApiConfigDialog) {
        m_pApiConfigDialog = new ApiConfigDialog();
    }
    int nRet = m_pApiConfigDialog->exec();
    if (nRet == QDialog::Accepted) {
        QString apiName = m_pApiConfigDialog->GetApiName();
        QString apiUrl = m_pApiConfigDialog->GetUrl();
        int requestType = m_pApiConfigDialog->GetRequestType();
        int paramType = m_pApiConfigDialog->GetParamsType();
        //QJsonObject param = m_pApiConfigDialog->GetParams();
        qDebug() << "apiName:" << apiName << " apiUrl:" << apiUrl;
        if (m_selectedIndex.column() != 0) {
            m_selectedIndex = m_pModel->index(m_selectedIndex.row(), 0, m_selectedIndex.parent());
        }
        QModelIndex index = m_selectedIndex;
        if (m_selectedIndex.parent().isValid()) {
            QModelIndex parent = m_selectedIndex.parent();
            qDebug() << "parent data:" << parent.data();
            if (parent.data().toString() == "Title" || parent.data().toString() == "Description") {
                //do nothing
            } else {
                index = parent;
            }
        }
        int indexRow = m_pModel->rowCount(index);
        qDebug() << "index row:" << indexRow << " data:" << index.data();
        if (m_pModel->insertRow(indexRow, index)) {
            QModelIndex child = m_pModel->index(indexRow, 0, index);
            QVariant val1(apiName);
            QModelIndex child2 = m_pModel->index(indexRow, 1, index);
            QVariant val2(apiUrl);
            qDebug() << "child valid:" << child.isValid() << " child2 valid:" << child2.isValid();
            m_pModel->setData(child, val1);
            m_pModel->setData(child2, val2);
            QJsonObject param;
            m_pModel->setItemType(child, API_ITEM, requestType, paramType, param);
            m_pModel->setItemType(child2, API_ITEM, requestType, paramType, param);
        } else {
            qDebug() << "add api failed.";
        }
    }
}

void ApiTreeView::OnTestApi() {
    if (m_selectedIndex.parent().isValid()) {
        int row = m_selectedIndex.row();
        int col = m_selectedIndex.column();
        QString apiName, apiUrl;
        if (col == 0) {
            apiName = m_selectedIndex.data().toString();
            apiUrl = m_pModel->index(row, 1, m_selectedIndex.parent()).data().toString();
        } else {
            apiName = m_pModel->index(row, 0, m_selectedIndex.parent()).data().toString();
            apiUrl = m_selectedIndex.data().toString();
        }
        HttpUtil::Instance()->DoGet(apiUrl, REQUEST_GET, PARAM_NONE);
        int iRet = HttpUtil::Instance()->GetRequestResult();
        qDebug() << "url:" << apiUrl << " 请求结果:" << (iRet == 0 ? "成功" : "失败");
        m_pModel->SetRequestResult(m_selectedIndex, iRet);
    }
}

void ApiTreeView::OnTestAll() {
    int serverRow = m_pModel->rowCount();
    for (int i = 0; i < serverRow; ++i) {
        QModelIndex index = m_pModel->index(i, 0);
        int childRow = m_pModel->rowCount(index);
        for (int j = 0; j < childRow; ++j) {
            QModelIndex child = m_pModel->index(j, 1, index);
            QString url = child.data().toString();
            if (!url.isEmpty()) {
                TreeItem *item = m_pModel->getItem(child);
                if (item->GetRequestType() == REQUEST_GET) {
                    HttpUtil::Instance()->DoGet(url, REQUEST_GET, item->GetParamsType());
                    int iRet = HttpUtil::Instance()->GetRequestResult();
                    qDebug() << "url:" << url << " 请求结果:" << (iRet == 0 ? "成功" : "失败");
                    m_pModel->SetRequestResult(child, iRet);
                }
            }
        }
    }
}

void ApiTreeView::OnDoubleClicked(const QModelIndex &index) {
    qDebug() << "OnDoubleClicked";
    TreeItem *item = m_pModel->getItem(index);
    if (item->GetItemType() == SERVER_ITEM) {

    } else if (item->GetItemType() == API_ITEM) {
        if (m_pApiConfigDialog == nullptr) {
            m_pApiConfigDialog = new ApiConfigDialog();
        }
        QString apiName = item->GetApiDesc();
        QString url = item->GetHttpUrl();
        int requestType = item->GetRequestType();
        int paramType = item->GetParamsType();
        QJsonObject obj = item->GetParams();
        m_pApiConfigDialog->SetApiName(apiName);
        m_pApiConfigDialog->SetUrl(url);
        m_pApiConfigDialog->SetRequestType(requestType);
        m_pApiConfigDialog->SetParamsType(paramType);
        m_pApiConfigDialog->exec();
    } else {
        //do nothing
    }
}


