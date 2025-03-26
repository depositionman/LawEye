#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <QString>
#include "util/simpleQtLogger.h"

class VideoModel
{
public:
    VideoModel();
    int appendVideoInfo(QString videoName, QString videoPath, QString VideoTime, QString shootTime, QString policeNumber, QString firstPhotoPath);
    int queryMaxVideoId(char **&result, int &row, int &col);
    int pageQueryVideoInfo(int num, int startRow,char **&result, int &row, int &col);
    int queryVideoCount(char **&result, int &row, int &col);
    int queryTimeWithinFourVideo(QString startTime, QString endTime, int num, int startRow, char **&result, int &row, int &col);
    int queryVideoTimeByVideoPath(QString videoPath,char **&result, int &row, int &col);
    int queryAllVideoInfo(char **&result, int &row, int &col);
    int queryTimeWithinAllVideo(QString startTime, QString endTime, char **&result, int &row, int &col);
    int queryVideoNameByVideoPath(QString videoPath,char **&result, int &row, int &col);
};

#endif // VIDEOMODEL_H
