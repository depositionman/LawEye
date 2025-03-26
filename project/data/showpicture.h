#ifndef SHOWPICTURE_H
#define SHOWPICTURE_H

#include <QString>

class ShowPicture
{
public:
    ShowPicture();
    ShowPicture(QString imgPath, QString name);
    QString imgPath() const;
    void setImgPath(const QString &imgPath);

    QString name() const;
    void setName(const QString &name);

private:
    QString imgPath_;
    QString name_;
};

#endif // SHOWPICTURE_H
