#include "photocontroller.h"
#include "util/sqliteutil.h"
//#include "util/simpleQtLogger.h"

PhotoController::PhotoController()
{

}

int PhotoController::queryMaxPhotoId()
{
    PhotoModel photoModel;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = photoModel.queryMaxPhotoId(result, row, col);
    return atoi(result[col]);
}

QList<Photo> PhotoController::queryAllPhotoInfo()
{
    PhotoModel photoModel;
    QList<Photo> photoList;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = photoModel.queryAllPhotoInfo(result, row, col);
    if(res == SQLITE_OK)
    {
        for(int i = 1; i <= row; ++i){
            photoList.append(Photo(atoi(result[i*col]), result[i*col+1], result[i*col+2], result[i*col+3], result[i*col+4]));
        }
//        L_INFO("gain queryAllPhotoInfo is success(PhotoController)");
    }
    return photoList;
}

QList<Photo> PhotoController::pageQueryPhotoInfo(int num, int startRow)
{
    PhotoModel photoModel;
    QList<Photo> photoList;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = photoModel.pageQueryPhotoInfo(num, startRow,result, row, col);
    if(res == SQLITE_OK)
    {
        for(int i = 1; i <= row; ++i){
            photoList.append(Photo(atoi(result[i*col]), result[i*col+1], result[i*col+2], result[i*col+3], result[i*col+4]));
        }
//        L_INFO("gain pageQueryPhotoInfo is success(PhotoController)");
    }
    return photoList;
}

QList<Photo> PhotoController::queryTimeWithinAllPhoto(QString startTime, QString endTime, int num, int startRow)
{
    PhotoModel photoModel;
    QList<Photo> photoList;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = photoModel.queryTimeWithinAllPhoto(startTime, endTime,num,startRow,result, row, col);
    if(res == SQLITE_OK)
    {
        for(int i = 1; i <= row; ++i){
            photoList.append(Photo(atoi(result[i*col]), result[i*col+1], result[i*col+2], result[i*col+3], result[i*col+4]));
        }
//        L_INFO("gain queryTimeWithinAllPhoto is success(PhotoController)");
    }
    return photoList;
}

int PhotoController::appendPhotoInfo(QString photoName, QString photoPath, QString shootTime, QString equipmentNumber)
{
    PhotoModel photoModel;
    int res = photoModel.appendPhotoInfo(photoName, photoPath, shootTime, equipmentNumber);
    if(res != SQLITE_OK){
//        L_INFO("appendPhotoInfo is error(PhotoController)");
    }
    return res;
}
