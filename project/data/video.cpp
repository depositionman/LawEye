#include "video.h"

Video::Video()
{

}

Video::Video(int id, QString name, QString path, QString videoTime, QString shootTime, QString policeNumber, QString firstPhotoPath)
{
    id_ = id;
    name_ = name;
    path_ = path;
    videoTime_ = videoTime;
    shootTime_ = shootTime;
    policeNumber_ = policeNumber;
    firstPhotoPath_ = firstPhotoPath;
}

int Video::id() const
{
    return id_;
}

void Video::setId(int id)
{
    id_ = id;
}

QString Video::name() const
{
    return name_;
}

void Video::setName(const QString &name)
{
    name_ = name;
}

QString Video::path() const
{
    return path_;
}

void Video::setPath(const QString &path)
{
    path_ = path;
}

QString Video::videoTime() const
{
    return videoTime_;
}

void Video::setVideoTime(const QString &videoTime)
{
    videoTime_ = videoTime;
}

QString Video::policeNumber() const
{
    return policeNumber_;
}

void Video::setPoliceNumber(const QString &policeNumber)
{
    policeNumber_ = policeNumber;
}

QString Video::firstPhotoPath() const
{
    return firstPhotoPath_;
}

void Video::setFirstPhotoPath(const QString &firstPhotoPath)
{
    firstPhotoPath_ = firstPhotoPath;
}

QString Video::shootTime() const
{
    return shootTime_;
}

void Video::setShootTime(const QString &shootTime)
{
    shootTime_ = shootTime;
}
