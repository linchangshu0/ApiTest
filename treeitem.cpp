#include "treeitem.h"
#include "common.h"

#include <QColor>

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
{
    parentItem = parent;
    itemData = data;

    m_eRequestType = REQUEST_GET;
    m_eParamsType = PARAM_NONE;

    m_iTestResult = -1;
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

TreeItem *TreeItem::child(int number)
{
    return childItems.value(number);
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

QVariant TreeItem::getBackground(int column) const {
    if (m_eType == SERVER_ITEM) {
        return QVariant();
    }
    if (m_iTestResult == -1) {
        return QVariant();
    }
    if (m_iTestResult == 0) {
        return QColor(Qt::green);
    }
    return QColor(Qt::red);
}

bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool TreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (TreeItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

bool TreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (TreeItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

bool TreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

bool TreeItem::insertRow(int row, QVector<QVariant> &vals) {
    if (row < 0 || vals.size() <= 0) {
        return false;
    }

    TreeItem *item = new TreeItem(vals, this);
    for (int i = 0; i < vals.size(); ++i) {
        item->setData(i, vals[i]);
    }
    childItems.insert(row, item);
    return true;
}

void TreeItem::SetApiType(int type) {
    m_eType = type;
}

void TreeItem::SetApiDesc(QString apiName) {
    m_strApiName = apiName;
}

void TreeItem::SetHttpUrl(QString url) {
    m_strHttpUrl = url;
}

void TreeItem::SetRequestType(int type) {
    m_eRequestType = type;
}

void TreeItem::SetParamsType(int type) {
    m_eParamsType = type;
}

void TreeItem::SetParams(QJsonObject params) {
    m_param = params;
}

void TreeItem::SetJsonParams(QJsonObject param) {

}

void TreeItem::SetFormDataParams(QString param) {

}

void TreeItem::SetTestResult(int b) {
    m_iTestResult = b;
}

QString TreeItem::GetHttpUrl() {
    return m_strHttpUrl;
}

int TreeItem::GetRequestType() {
    return m_eRequestType;
}

int TreeItem::GetParamsType() {
    return m_eParamsType;
}
