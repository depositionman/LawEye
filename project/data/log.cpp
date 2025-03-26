#include "log.h"

Log::Log(QString time, QString equipmentNumber, QString policeNumber, QString operationType)
{
    time_ = time;
    equipmentNumber_ = equipmentNumber;
    policeNumber_ = policeNumber;
    operationType_ = operationType;
}

QString Log::time() const
{
    return time_;
}

void Log::setTime(const QString &time)
{
    time_ = time;
}

QString Log::equipmentNumber() const
{
    return equipmentNumber_;
}

void Log::setEquipmentNumber(const QString &equipmentNumber)
{
    equipmentNumber_ = equipmentNumber;
}

QString Log::policeNumber() const
{
    return policeNumber_;
}

void Log::setPoliceNumber(const QString &policeNumber)
{
    policeNumber_ = policeNumber;
}

QString Log::operationType() const
{
    return operationType_;
}

void Log::setOperationType(const QString &operationType)
{
    operationType_ = operationType;
}
