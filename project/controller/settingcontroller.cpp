#include "settingcontroller.h"
#include "util/sqliteutil.h"
//#include "util/simpleQtLogger.h"
#include <QDebug>

SettingController::SettingController()
{

}

int SettingController::addSettingInfo(QString videoPath, QString photoPath, QString equipmentNumber)
{
    SettingModel settingModel;
    int res = settingModel.appendSettingInfo(videoPath, photoPath, equipmentNumber);
    if(res != SQLITE_OK)
    {
//        L_INFO("add SettingInfo is error(SettingController)");
    }
    return res;
}

Setting SettingController::getSettingInfoByNumber(QString number)
{
    Setting settingInfo;
    SettingModel settingModel;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    if(settingModel.querySettingInfoByNumber(number, result, row, col) == EXIST)
    {
        settingInfo.setVideoPath(result[col+1]);
        settingInfo.setPhotoPath(result[col+2]);
//        L_INFO("getSettingInfoByNumber is success");
    }
    return settingInfo;
}

int SettingController::changeSettingInfoByNumber(QString videoPath, QString photoPath, QString number)
{
    SettingModel settingModel;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = settingModel.changeSettingInfoByNumber(videoPath, photoPath, number,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("changeSettingInfoByNumber is error(SettingController)");
    }
    return res;
}

int SettingController::querySettingInfoByNumber(QString number)
{
    Setting settingInfo;
    SettingModel settingModel;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = settingModel.querySettingInfoByNumber(number, result, row, col);
    return res;
}
