#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include "model/videomodel.h"
#include "data/video.h"

class VideoController
{
public:
    VideoController();
    int appendVideoInfo(QString videoName, QString videoPath, QString VideoTime, QString shootTime, QString policeNumber, QString firstPhotoPath);
    int queryMaxVideoId();
    QList<Video> pageQueryVideoInfo(int num, int startRow);
    int queryVideoCount();
    QList<Video> queryTimeWithinFourVideo(QString startTime, QString endTime, int num, int startRow);
    QString queryVideoTimeByVideoPath(QString videoPath);
    QList<Video> queryAllVideoInfo();
    QList<Video> queryTimeWithinAllVideo(QString startTime, QString endTime);
    QString queryVideoNameByVideoPath(QString videoPath);
};

#endif // VIDEOCONTROLLER_H
