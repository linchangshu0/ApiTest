#ifndef APIITEM_H
#define APIITEM_H

#include <QStandardItem>
#include <QJsonObject>

class ApiItem : public QStandardItem
{
public:
    ApiItem();
    ApiItem(QString name);

    void SetApiType(int type);
    void SetHttpUrl(QString url);
    void SetRequestType(int type);
    void SetParamsType(int type);
    void SetJsonParams(QJsonObject param);
    void SetFormDataParams(QString param);

    void SetTestResult(bool b);

    QString GetHttpUrl();
    int GetRequestType();
    int GetParamsType();

private:
    int         m_eType;
    QString     m_strName;
    QString     m_strHttpUrl;
    int         m_eRequestType;
    int         m_eParamsType;
    //统一使用QJsonObject保存参数
    QJsonObject m_param;

    bool        m_bTestResult;
};

#endif // APIITEM_H
