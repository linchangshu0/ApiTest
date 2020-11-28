#ifndef COMMON_H
#define COMMON_H
#include <QMutex>

static QMutex g_mutex;

enum ITEM_TYPE {
    SERVER_ITEM,
    API_ITEM
};

enum REQUEST_TYPE {
    REQUEST_GET,
    REQUEST_POST,
    REQUEST_OPTIONS,
    REQUEST_DELETE,
    REQUEST_UPDATE
};

enum PARAM_TYPE {
    PARAM_NONE,
    PARAM_JSON,
    PARAM_FORMDATA
};

#endif // COMMON_H
