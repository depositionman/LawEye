#ifndef POLICE_H
#define POLICE_H

#include <QString>

class Police
{
public:
    Police(){}
    Police(int id, QString name, QString number, QString pwd, int status, QString createTime);
    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString number() const;
    void setNumber(const QString &number);

    QString pwd() const;
    void setPwd(const QString &pwd);

    int status() const;
    void setStatus(int status);

    QString createTime() const;
    void setCreateTime(const QString &createTime);

private:
    int id_;
    QString name_;
    QString number_;
    QString pwd_;
    int status_;
    QString createTime_;
};

#endif // POLICE_H
