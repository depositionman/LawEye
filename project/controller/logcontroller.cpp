#include "logcontroller.h"
#include "data/log.h"
#include <QDebug>

LogController::LogController()
{

}

int LogController::appendLogInfo(QString operationType, QString writeTime, QString equipmentNumber, QString policeNumber)
{
    LogModel logModel;
    int res = logModel.appendLogInfo(operationType,writeTime,equipmentNumber,policeNumber);
    if(res != SQLITE_OK)
    {
//        L_INFO("appendLogInfo is error(LogController)");
    }
    return res;
}

QList<Log> LogController::queryTenLog(int num, int startRow)
{
    LogModel logModel;
    QList<Log> logList;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = logModel.queryTenLog(num, startRow,result, row, col);
    if(res == SQLITE_OK)
    {
        for(int i = 1; i <= row; ++i){
            logList.append(Log(result[i*col+2], result[i*col+3], result[i*col+4],result[i*col+1]));
        }
//        L_INFO("gain queryTenLog is success(LogController)");
    }
    return logList;
}

int LogController::queryCountLog()
{
    LogModel logModel;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = logModel.queryCountLog(result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryCountLog is error(LogController)");
    }
    return atoi(result[col]);
}
