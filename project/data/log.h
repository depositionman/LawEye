#ifndef LOG_H
#define LOG_H

#include <QString>

class Log
{
public:
    Log(QString time = "",QString equipmentNumber = "",QString policeNumber = "",QString operationType = "");
    QString time() const;
    void setTime(const QString &time);

    QString equipmentNumber() const;
    void setEquipmentNumber(const QString &equipmentNumber);

    QString policeNumber() const;
    void setPoliceNumber(const QString &policeNumber);

    QString operationType() const;
    void setOperationType(const QString &operationType);

private:
    QString time_;
    QString equipmentNumber_;
    QString policeNumber_;
    QString operationType_;
};

#endif // LOG_H
