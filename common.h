#ifndef COMMON_H
#define COMMON_H
#include <QMutex>
#include <QString>

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

extern QString APPLICATION_DIR;

#endif // COMMON_H
