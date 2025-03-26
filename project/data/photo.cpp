#include "photo.h"

Photo::Photo()
{

}

Photo::Photo(int id, QString name, QString path, QString shootTime, QString policeNumber)
{
    id_ = id;
    path_ = path;
    shootTime_ = shootTime;
    policeNumber_ = policeNumber;
    name_ = name;
}

QString Photo::name() const
{
    return name_;
}

void Photo::setName(const QString &name)
{
    name_ = name;
}

QString Photo::path() const
{
    return path_;
}

void Photo::setPath(const QString &path)
{
    path_ = path;
}
