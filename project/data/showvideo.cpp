#include "showvideo.h"

ShowVideo::ShowVideo()
{

}

ShowVideo::ShowVideo(QString firstPhotoPath, QString Path, QString Name)
{
    firstPhotoPath_ = firstPhotoPath;
    Path_ = Path;
    Name_ = Name;
}

QString ShowVideo::firstPhotoPath() const
{
    return firstPhotoPath_;
}

void ShowVideo::setFirstPhotoPath(const QString &firstPhotoPath)
{
    firstPhotoPath_ = firstPhotoPath;
}

QString ShowVideo::Path() const
{
    return Path_;
}

void ShowVideo::setPath(const QString &Path)
{
    Path_ = Path;
}

QString ShowVideo::Name() const
{
    return Name_;
}

void ShowVideo::setName(const QString &Name)
{
    Name_ = Name;
}
