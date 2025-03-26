#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H

#include "model/logmodel.h"
#include "data/log.h"

class LogController
{
public:
    LogController();
    int appendLogInfo(QString operationType,QString writeTime,QString equipmentNumber,QString policeNumber);
    QList<Log> queryTenLog(int num, int startRow);
    int queryCountLog();
};

#endif // LOGCONTROLLER_H
