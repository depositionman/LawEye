#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H

#include "model/settingmodel.h"
#include "data/setting.h"

class SettingController
{
public:
    SettingController();
    int addSettingInfo(QString videoPath, QString photoPath, QString equipmentNumber);
    Setting getSettingInfoByNumber(QString number);
    int changeSettingInfoByNumber(QString videoPath, QString photoPath,QString number);
    int querySettingInfoByNumber(QString number);
};

#endif // SETTINGCONTROLLER_H
