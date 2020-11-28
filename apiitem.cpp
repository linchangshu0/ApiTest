#include "apiitem.h"

ApiItem::ApiItem() :
    QStandardItem ()
{

}

ApiItem::ApiItem(QString name) :QStandardItem (name) {
    m_strName = name;
}

void ApiItem::SetApiType(int type) {
    m_eType = type;
}

void ApiItem::SetHttpUrl(QString url) {
    m_strHttpUrl = url;
}

void ApiItem::SetRequestType(int type) {
    m_eRequestType = type;
}

void ApiItem::SetParamsType(int type) {
    m_eParamsType = type;
}

void ApiItem::SetJsonParams(QJsonObject param) {

}

void ApiItem::SetFormDataParams(QString param) {

}

void ApiItem::SetTestResult(bool b) {
    m_bTestResult = b;
    if (b) {
        setBackground(QBrush(Qt::green));
    } else {
        setBackground(QBrush(Qt::red));
    }
}

QString ApiItem::GetHttpUrl() {
    return m_strHttpUrl;
}

int ApiItem::GetRequestType() {
    return m_eRequestType;
}

int ApiItem::GetParamsType() {
    return m_eParamsType;
}

