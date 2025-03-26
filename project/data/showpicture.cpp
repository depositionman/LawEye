#include "showpicture.h"

ShowPicture::ShowPicture()
{

}

ShowPicture::ShowPicture(QString imgPath, QString name)
{
    imgPath_ = imgPath;
    name_ = name;
}

QString ShowPicture::imgPath() const
{
    return imgPath_;
}

void ShowPicture::setImgPath(const QString &imgPath)
{
    imgPath_ = imgPath;
}

QString ShowPicture::name() const
{
    return name_;
}

void ShowPicture::setName(const QString &name)
{
    name_ = name;
}
