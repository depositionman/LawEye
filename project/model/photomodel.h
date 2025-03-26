#ifndef PHOTOMODEL_H
#define PHOTOMODEL_H

#include "util/sqliteutil.h"

class PhotoModel
{
public:
    PhotoModel();
    int appendPhotoInfo(QString photoName, QString photoPath, QString shootTime, QString policeNumber);
    int queryMaxPhotoId(char **&result, int &row, int &col);
    int queryAllPhotoInfo(char **&result, int &row, int &col);
    int pageQueryPhotoInfo(int num, int startRow,char **&result, int &row, int &col);
    int queryTimeWithinAllPhoto(QString startTime, QString endTime, int num, int startRow, char **&result, int &row, int &col);
};

#endif // PHOTOMODEL_H
