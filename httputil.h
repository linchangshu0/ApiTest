#ifndef HTTPUTIL_H
#define HTTPUTIL_H

#include "common.h"

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

class HttpUtil : QObject
{
    Q_OBJECT

public:
    static HttpUtil* Instance() {
        if (m_pInstance == nullptr) {
            m_pInstance = new HttpUtil();
        }
        return m_pInstance;
    }

    bool GetRequestResult() {   return m_bRequestResult; }
    void DoGet(QString url, int requestType, int paramType);

private slots:
    void OnReplyFinished(QNetworkReply *reply);
    void OnEventLoopFinished();

private:
    HttpUtil();
    static HttpUtil *m_pInstance;
    QNetworkAccessManager   *m_pNetworkManager;
    bool            m_bRequestResult;
    QEventLoop      m_eventLoop;
    QNetworkReply   *m_pNetworkReply;
};

#endif // HTTPUTIL_H
