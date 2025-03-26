#include "setting.h"

Setting::Setting(int id, QString videoPath, QString photoPath, QString equipmentNumber)
{
    id_ = id;
    videoPath_ = videoPath;
    photoPath_ = photoPath;
    equipmentNumber_ = equipmentNumber;
}

int Setting::id() const
{
    return id_;
}

void Setting::setId(int id)
{
    id_ = id;
}

QString Setting::videoPath() const
{
    return videoPath_;
}

void Setting::setVideoPath(const QString &videoPath)
{
    videoPath_ = videoPath;
}

QString Setting::photoPath() const
{
    return photoPath_;
}

void Setting::setPhotoPath(const QString &photoPath)
{
    photoPath_ = photoPath;
}

QString Setting::equipmentNumber() const
{
    return equipmentNumber_;
}

void Setting::setEquipmentNumber(const QString &equipmentNumber)
{
    equipmentNumber_ = equipmentNumber;
}
