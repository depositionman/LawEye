#ifndef SETTINGMODEL_H
#define SETTINGMODEL_H

#include <QString>
#define EXIST 2
#define NOTEXIST 3

class SettingModel
{
public:
    SettingModel();
    int appendSettingInfo(QString videoPath, QString photoPath, QString equipmentNumber);
    int querySettingInfoByNumber(QString number, char **&result, int &row, int &col);
    int changeSettingInfoByNumber(QString videoPath, QString photoPath,QString number, char **&result, int &row, int &col);
};

#endif // SETTINGMODEL_H
