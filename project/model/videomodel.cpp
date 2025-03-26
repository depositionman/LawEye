#include "videomodel.h"
#include "util/sqliteutil.h"
#include <QDebug>

VideoModel::VideoModel()
{

}

int VideoModel::appendVideoInfo(QString videoName, QString videoPath, QString VideoTime, QString shootTime, QString policeNumber, QString firstPhotoPath)
{
    QString sql = QString("INSERT INTO tbl_video (video_name,video_path,videoTime,video_shootTime,police_number,firstPhoto_path) "
                          "VALUES('%1','%2','%3','%4','%5','%6');")
            .arg(videoName).arg(videoPath).arg(VideoTime).arg(shootTime).arg(policeNumber).arg(firstPhotoPath);
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("appendVideoInfo is error(VideoModel)");
    }
    return res;
}

int VideoModel::queryMaxVideoId(char **&result, int &row, int &col)
{
    QString sql = QString("SELECT MAX(video_id) FROM tbl_video;");
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryMaxVideoId is error(VideoModel)");
    }
    return res;
}

int VideoModel::pageQueryVideoInfo(int num, int startRow, char **&result, int &row, int &col)
{
    QString sql = QString("SELECT * FROM tbl_video ORDER BY video_id DESC LIMIT %1 OFFSET %2;").arg(num).arg(startRow);
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("pageQueryVideoInfo is error(VideoModel)");
    }
    return res;
}

int VideoModel::queryVideoCount(char **&result, int &row, int &col)
{
    QString sql = QString("SELECT COUNT(video_id) FROM tbl_video;");
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryVideoCount is error(VideoModel)");
    }
    return res;
}

int VideoModel::queryTimeWithinFourVideo(QString startTime, QString endTime, int num, int startRow, char **&result, int &row, int &col)
{
    QString sql = QString("select * from tbl_video where video_shootTime Between '%1' AND '%2' "
                          "ORDER BY video_id DESC LIMIT %3 OFFSET %4;")
            .arg(startTime).arg(endTime).arg(num).arg(startRow);
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryTimeWithinFourVideo is error(VideoModel)");
    }
    return res;
}

int VideoModel::queryVideoTimeByVideoPath(QString videoPath, char **&result, int &row, int &col)
{
    QString sql = QString("select videoTime from tbl_video where video_path = '%1';")
            .arg(videoPath);
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryVideoTimeByVideoPath is error(VideoModel)");
    }
    return res;
}

int VideoModel::queryAllVideoInfo(char **&result, int &row, int &col)
{
    QString sql = QString("select * from tbl_video;");
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryAllVideoInfo is error(VideoModel)");
    }
    return res;
}

int VideoModel::queryTimeWithinAllVideo(QString startTime, QString endTime, char **&result, int &row, int &col)
{
    QString sql = QString("select * from tbl_video where video_shootTime Between '%1' AND '%2' "
                          "ORDER BY video_id DESC;")
            .arg(startTime).arg(endTime);
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryTimeWithinAllPhoto is error(VideoModel)");
    }
    return res;
}

int VideoModel::queryVideoNameByVideoPath(QString videoPath, char **&result, int &row, int &col)
{
    QString sql = QString("select video_name from tbl_video where video_path = '%1';")
            .arg(videoPath);
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("queryVideoTimeByVideoPath is error(VideoModel)");
    }
    return res;
}
