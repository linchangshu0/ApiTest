#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVector>
#include <QVariant>
#include <QJsonObject>

class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parent = 0);
    ~TreeItem();

    TreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    QVariant getBackground(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    TreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);
    bool insertRow(int row, QVector<QVariant> &vals);

    void SetApiType(int type);
    void SetApiDesc(QString apiName);
    void SetHttpUrl(QString url);
    void SetRequestType(int type);
    void SetParamsType(int type);
    void SetParams(QJsonObject params);
    void SetJsonParams(QJsonObject param);
    void SetFormDataParams(QString param);

    void SetTestResult(int b);

    int GetItemType() { return m_eType; }
    QString GetApiDesc()    {   return m_strApiName;    }
    QString GetHttpUrl();
    int GetRequestType();
    int GetParamsType();
    QJsonObject GetParams() { return m_param;   }

private:
    QList<TreeItem*> childItems;
    QVector<QVariant> itemData;
    TreeItem    *parentItem;
    QString     m_strApiName;
    int         m_eType;
    QString     m_strName;
    QString     m_strHttpUrl;
    int         m_eRequestType;
    int         m_eParamsType;
    //统一使用QJsonObject保存参数
    QJsonObject m_param;

    int         m_iTestResult;
};

#endif // TREEITEM_H
