#ifndef SHOWVIDEO_H
#define SHOWVIDEO_H

#include <QString>

class ShowVideo
{
public:
    ShowVideo();
    ShowVideo(QString firstPhotoPath, QString Path, QString Name);
    QString firstPhotoPath() const;
    void setFirstPhotoPath(const QString &firstPhotoPath);

    QString Path() const;
    void setPath(const QString &Path);

    QString Name() const;
    void setName(const QString &Name);

private:
    QString firstPhotoPath_;
    QString Path_;
    QString Name_;
};

#endif // SHOWVIDEO_H
