#include "settingmodel.h"
#include <QString>
#include "util/sqliteutil.h"
//#include "util/simpleQtLogger.h"

SettingModel::SettingModel()
{

}

int SettingModel::appendSettingInfo(QString videoPath, QString photoPath, QString equipmentNumber)
{
    QString sql = QString("INSERT INTO tbl_setting (videoPath,photoPath,equipment_number) VALUES('%1','%2','%3');")
            .arg(videoPath).arg(photoPath).arg(equipmentNumber);
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("appendSettingInfo is error(SettingModel)");
    }
    return res;
}

int SettingModel::querySettingInfoByNumber(QString number, char **&result, int &row, int &col)
{
    QString sql = QString("SELECT * FROM tbl_setting WHERE equipment_number = '%1';").arg(number);
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("querySettingInfoByBumber is error");
    }
    else
    {
        if(row != 0) {
//            L_INFO("Setting exist");
            return EXIST;
        }
        else{
//            L_INFO("Setting not exist");
            return NOTEXIST;
        }
    }
    return res;
}

int SettingModel::changeSettingInfoByNumber(QString videoPath, QString photoPath, QString number, char **&result, int &row, int &col)
{
    QString sql = QString("UPDATE tbl_setting (videoPath,photoPath) VALUES('%1','%2') WHERE equipment_number = '%3';")
            .arg(videoPath).arg(photoPath).arg(number);
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("changeSettingInfoByNumber is error(SettingModel)");
    }
    return res;
}
