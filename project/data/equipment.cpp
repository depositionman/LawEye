#include "equipment.h"

Equipment::Equipment(int id, QString name, QString number, int status)
{

}

int Equipment::id() const
{
    return id_;
}

void Equipment::setId(int id)
{
    id_ = id;
}

QString Equipment::name() const
{
    return name_;
}

void Equipment::setName(const QString &name)
{
    name_ = name;
}

QString Equipment::number() const
{
    return number_;
}

void Equipment::setNumber(const QString &number)
{
    number_ = number;
}

int Equipment::status() const
{
    return status_;
}

void Equipment::setStatus(int status)
{
    status_ = status;
}
