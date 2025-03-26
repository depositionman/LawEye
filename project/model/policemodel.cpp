#include "policemodel.h"
#include "util/sqliteutil.h"
//#include "util/simpleQtLogger.h"

PoliceModel::PoliceModel()
{

}

int PoliceModel::queryPoliceByNumberPwd(QString number, QString pwd)
{

    QString sql = QString("SELECT * FROM tbl_police WHERE police_number = '%1' and police_pwd = '%2';").arg(number).arg(pwd);
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryPoliceByNumberPwd is error");
    }
    else
    {
        if(row != 0) {
//            L_INFO("police exist");
            return EXIST;
        }
        else{
//            L_INFO("police not exist");
            return NOTEXIST;
        }
    }
    return res;
}
