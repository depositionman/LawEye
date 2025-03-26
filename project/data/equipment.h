#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>

class Equipment
{
public:
    Equipment(){}
    Equipment(int id, QString name, QString number, int status);
    int id() const;
    void setId(int id);


    QString name() const;
    void setName(const QString &name);

    QString number() const;
    void setNumber(const QString &number);

    int status() const;
    void setStatus(int status);

private:
    int id_;
    QString name_;
    QString number_;
    int status_;
};

#endif // EQUIPMENT_H
