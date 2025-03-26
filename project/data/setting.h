#ifndef SETTING_H
#define SETTING_H

#include <QString>

class Setting
{
public:
    Setting(){}
    Setting(int id, QString videoPath, QString photoPath, QString equipmentNumber);
    int id() const;
    void setId(int id);

    QString videoPath() const;
    void setVideoPath(const QString &videoPath);

    QString photoPath() const;
    void setPhotoPath(const QString &photoPath);

    QString equipmentNumber() const;
    void setEquipmentNumber(const QString &equipmentNumber);

private:
    int id_;
    QString videoPath_;
    QString photoPath_;
    QString equipmentNumber_;
};

#endif // SETTING_H
