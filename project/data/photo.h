#ifndef PHOTO_H
#define PHOTO_H

#include <QString>

class Photo
{
public:
    Photo();
    Photo(int id, QString name, QString path, QString shootTime, QString policeNumber);
    QString name() const;
    void setName(const QString &name);

    QString path() const;
    void setPath(const QString &path);

private:
    int id_;
    QString name_;
    QString path_;
    QString shootTime_;
    QString policeNumber_;
};

#endif // PHOTO_H
