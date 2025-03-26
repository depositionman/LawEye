#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QString>
#include "util/simpleQtLogger.h"
#include "util/sqliteutil.h"

class LogModel
{
public:
    LogModel();
    int appendLogInfo(QString operationType,QString writeTime,QString equipmentNumber,QString policeNumber);
    int queryTenLog(int num, int startRow, char **&result, int &row, int &col);
    int queryCountLog(char **&result, int &row, int &col);
};

#endif // LOGMODEL_H
