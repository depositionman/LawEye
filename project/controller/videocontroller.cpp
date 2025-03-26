#include "videocontroller.h"
#include "util/sqliteutil.h"

VideoController::VideoController()
{

}

int VideoController::appendVideoInfo(QString videoName, QString videoPath, QString VideoTime, QString shootTime, QString policeNumber, QString firstPhotoPath)
{
    VideoModel videoModel;
    int res = videoModel.appendVideoInfo(videoName, videoPath, VideoTime, shootTime, policeNumber,firstPhotoPath);
    if(res != SQLITE_OK){
//        L_INFO("appendVideoInfo is error(VideoController)");
    }
    return res;
}

int VideoController::queryMaxVideoId()
{
    VideoModel videoModel;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = videoModel.queryMaxVideoId(result, row, col);
    return atoi(result[col]);
}

QList<Video> VideoController::pageQueryVideoInfo(int num, int startRow)
{
    VideoModel videoModel;
    QList<Video> videoList;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = videoModel.pageQueryVideoInfo(num, startRow,result, row, col);
    if(res == SQLITE_OK)
    {
        for(int i = 1; i <= row; ++i){
            videoList.append(Video(atoi(result[i*col]), result[i*col+1], result[i*col+2],
                    result[i*col+3], result[i*col+4], result[i*col+5], result[i*col+6]));
        }
//        L_INFO("gain pageQueryVideoInfo is success(VideoController)");
    }
    return videoList;
}

int VideoController::queryVideoCount()
{
    VideoModel videoModel;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = videoModel.queryVideoCount(result, row, col);
    return atoi(result[col]);
}

QList<Video> VideoController::queryTimeWithinFourVideo(QString startTime, QString endTime, int num, int startRow)
{
    VideoModel videoModel;
    QList<Video> videoList;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = videoModel.queryTimeWithinFourVideo(startTime, endTime, num, startRow,result, row, col);
    if(res == SQLITE_OK)
    {
        for(int i = 1; i <= row; ++i){
            videoList.append(Video(atoi(result[i*col]), result[i*col+1], result[i*col+2],
                    result[i*col+3], result[i*col+4], result[i*col+5], result[i*col+6]));
        }
//        L_INFO("gain queryTimeWithinFourVideo is success(VideoController)");
    }
    return videoList;
}

QString VideoController::queryVideoTimeByVideoPath(QString videoPath)
{
    VideoModel videoModel;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = videoModel.queryVideoTimeByVideoPath(videoPath,result, row, col);
    return result[col];
}

QList<Video> VideoController::queryAllVideoInfo()
{
    VideoModel videoModel;
    QList<Video> videoList;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = videoModel.queryAllVideoInfo(result,row,col);
    if(res == SQLITE_OK)
    {
        for(int i = 1; i <= row; ++i){
            videoList.append(Video(atoi(result[i*col]), result[i*col+1], result[i*col+2],
                    result[i*col+3], result[i*col+4], result[i*col+5], result[i*col+6]));
        }
//        L_INFO("gain queryAllVideoInfo is success(VideoController)");
    }
    return videoList;
}

QList<Video> VideoController::queryTimeWithinAllVideo(QString startTime, QString endTime)
{
    VideoModel videoModel;
    QList<Video> videoList;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = videoModel.queryTimeWithinAllVideo(startTime, endTime, result, row, col);
    if(res == SQLITE_OK)
    {
        for(int i = 1; i <= row; ++i){
            videoList.append(Video(atoi(result[i*col]), result[i*col+1], result[i*col+2],
                    result[i*col+3], result[i*col+4], result[i*col+5], result[i*col+6]));
        }
//        L_INFO("gain queryTimeWithinAllPhoto is success(VideoController)");
    }
    return videoList;
}

QString VideoController::queryVideoNameByVideoPath(QString videoPath)
{
    VideoModel videoModel;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = videoModel.queryVideoNameByVideoPath(videoPath,result, row, col);
    return result[col];
}
