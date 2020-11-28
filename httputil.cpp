#include "httputil.h"

#include <QNetworkRequest>
#include <QUrl>

HttpUtil* HttpUtil::m_pInstance = nullptr;

HttpUtil::HttpUtil():
    m_pNetworkManager(nullptr)
{
    m_pNetworkManager = new QNetworkAccessManager();

    //connect(m_pNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(OnReplyFinished(QNetworkReply*)));
    connect(m_pNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(OnEventLoopFinished()));
}

void HttpUtil::DoGet(QString url, int requestType, int paramType) {
    QUrl qurl(url);
    QNetworkRequest req(qurl);
    if (requestType == REQUEST_GET) {
        m_pNetworkReply = m_pNetworkManager->get(req);
    }
    m_eventLoop.exec();
}

void HttpUtil::OnReplyFinished(QNetworkReply *reply) {
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(reply->error() == QNetworkReply::NoError && statusCode == 200) {
        qDebug() << "请求成功";
        m_bRequestResult = true;
    } else {
        qDebug() << "请求失败, error:" << reply->error() << " statusCode:" << statusCode;
        m_bRequestResult = false;
    }

    reply->deleteLater();
}

void HttpUtil::OnEventLoopFinished() {
    int statusCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(m_pNetworkReply->error() == QNetworkReply::NoError && statusCode == 200) {
        qDebug() << "OnEventLoopFinished 请求成功";
        m_bRequestResult = true;
    } else {
        qDebug() << "OnEventLoopFinished 请求失败, error:" << m_pNetworkReply->error() << " statusCode:" << statusCode;
        m_bRequestResult = false;
    }

    //m_pNetworkReply->deleteLater();
    //g_mutex.unlock();
    if (m_eventLoop.isRunning()) {
        m_eventLoop.exit(0);
    }
}
