#include "apimodel.h"

ApiModel::ApiModel()
{
    setColumnCount(2);
    setHorizontalHeaderLabels(QStringList()<< QStringLiteral("服务") << QStringLiteral("链接"));
}
