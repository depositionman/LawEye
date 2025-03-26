#ifndef PHOTOCONTROLLER_H
#define PHOTOCONTROLLER_H

#include "model/photomodel.h"
#include <QList>
#include "data/photo.h"
#include "model/photomodel.h"

class PhotoController
{
public:
    PhotoController();
    int appendPhotoInfo(QString photoName, QString photoPath, QString shootTime, QString policeNumber);
    int queryMaxPhotoId();
    QList<Photo> queryAllPhotoInfo();
    QList<Photo> pageQueryPhotoInfo(int num, int startRow);
    QList<Photo> queryTimeWithinAllPhoto(QString startTime, QString endTime, int num, int startRow);
};

#endif // PHOTOCONTROLLER_H
