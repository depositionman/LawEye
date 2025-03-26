#include "logmodel.h"

LogModel::LogModel()
{

}

int LogModel::appendLogInfo(QString operationType, QString writeTime, QString equipmentNumber, QString policeNumber)
{
    QString sql = QString("INSERT INTO tbl_log (operationType,writeTime,equipment_number,police_number) "
                          "VALUES('%1','%2','%3','%4');")
            .arg(operationType).arg(writeTime).arg(equipmentNumber).arg(policeNumber);
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("appendLogInfo is error(LogModel)");
    }
    return res;
}

int LogModel::queryTenLog(int num, int startRow, char **&result, int &row, int &col)
{
    QString sql = QString("select * from tbl_log ORDER BY log_id DESC LIMIT %1 OFFSET %2;")
            .arg(num).arg(startRow);
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryTenLog is error(LogModel)");
    }
    return res;
}

int LogModel::queryCountLog(char **&result, int &row, int &col)
{
    QString sql = QString("select COUNT(log_id) from tbl_log;");
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryCountLog is error(LogModel)");
    }
    return res;
}
