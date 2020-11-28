#include "apimodel.h"

ApiModel::ApiModel()
{
    setColumnCount(2);
    setHorizontalHeaderLabels(QStringList()<< QStringLiteral("服务或接口名") << QStringLiteral("服务描述或接口链接"));
}
