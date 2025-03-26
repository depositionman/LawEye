#ifndef VIDEO_H
#define VIDEO_H

#include <QString>

class Video
{
public:
    Video();
    Video(int id, QString name, QString path, QString videoTime, QString shootTime, QString policeNumber, QString firstPhotoPath);
    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString path() const;
    void setPath(const QString &path);

    QString videoTime() const;
    void setVideoTime(const QString &videoTime);

    QString policeNumber() const;
    void setPoliceNumber(const QString &policeNumber);

    QString firstPhotoPath() const;
    void setFirstPhotoPath(const QString &firstPhotoPath);

    QString shootTime() const;
    void setShootTime(const QString &shootTime);

private:
    int id_;
    QString name_;
    QString path_;
    QString videoTime_;
    QString shootTime_;
    QString policeNumber_;
    QString firstPhotoPath_;
};

#endif // VIDEO_H
