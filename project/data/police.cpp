#include "police.h"

Police::Police(int id, QString name, QString number, QString pwd, int status, QString createTime)
{
    id_ = id;
    name_ = name;
    number_ = number;
    pwd_ = pwd;
    status_ = status;
    createTime_ = createTime;
}

int Police::id() const
{
    return id_;
}

void Police::setId(int id)
{
    id_ = id;
}

QString Police::name() const
{
    return name_;
}

void Police::setName(const QString &name)
{
    name_ = name;
}

QString Police::number() const
{
    return number_;
}

void Police::setNumber(const QString &number)
{
    number_ = number;
}

QString Police::pwd() const
{
    return pwd_;
}

void Police::setPwd(const QString &pwd)
{
    pwd_ = pwd;
}

int Police::status() const
{
    return status_;
}

void Police::setStatus(int status)
{
    status_ = status;
}

QString Police::createTime() const
{
    return createTime_;
}

void Police::setCreateTime(const QString &createTime)
{
    createTime_ = createTime;
}
