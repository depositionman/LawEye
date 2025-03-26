#include "photomodel.h"
//#include "util/simpleQtLogger.h"

PhotoModel::PhotoModel()
{

}

int PhotoModel::appendPhotoInfo(QString photoName, QString photoPath, QString shootTime, QString policeNumber)
{
    QString sql = QString("INSERT INTO tbl_photo (photo_name,photo_path,photo_shootTime,police_number) "
                          "VALUES('%1','%2','%3','%4');")
            .arg(photoName).arg(photoPath).arg(shootTime).arg(policeNumber);
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("appendPhotoInfo is error(PhotoModel)");
    }
    return res;
}

int PhotoModel::queryMaxPhotoId(char **&result, int &row, int &col)
{
    QString sql = QString("SELECT MAX(photo_id) FROM tbl_photo;");
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryMaxPhotoId is error(PhotoModel)");
    }
    return res;
}

int PhotoModel::queryAllPhotoInfo(char **&result, int &row, int &col)
{
    QString sql = QString("SELECT * FROM tbl_photo;");
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryAllPhotoInfo is error(PhotoModel)");
    }
    return res;
}

int PhotoModel::pageQueryPhotoInfo(int num, int startRow,char **&result, int &row, int &col)
{
    QString sql = QString("SELECT * FROM tbl_photo ORDER BY photo_id DESC LIMIT %1 OFFSET %2;").arg(num).arg(startRow);
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("pageQueryPhotoInfo is error(PhotoModel)");
    }
    return res;
}

int PhotoModel::queryTimeWithinAllPhoto(QString startTime, QString endTime, int num, int startRow, char **&result, int &row, int &col)
{
    QString sql = QString("select * from tbl_photo where photo_shootTime Between '%1' AND '%2' "
                          "ORDER BY photo_id DESC LIMIT %3 OFFSET %4;")
            .arg(startTime).arg(endTime).arg(num).arg(startRow);
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryTimeWithinAllPhoto is error(PhotoModel)");
    }
    return res;
}
