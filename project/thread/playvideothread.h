#ifndef PLAYVIDEOTHREAD_H
#define PLAYVIDEOTHREAD_H

#include <QObject>
#include <QThread>
#include <QImage>
#include "util/videodecord.h"

enum VideoStatus{
    START,//开始播放
    CONTINUEPLAY,//继续播放
    PAUSE//暂停
};

class PlayVideoThread : public QThread
{
     Q_OBJECT
public:
    PlayVideoThread(){}
    PlayVideoThread(QString videoPath);
    ~PlayVideoThread();
    void stop();
    VideoStatus getVideoStatus() const;
    void setVideoStatus(const VideoStatus &value);


    //清除缓存区
    void clearBuf();

    double getFactor() const;
    void setFactor(double value);
    bool getStopFlag() const;
    void setStopFlag(bool stopFlag);

    bool getFlag() const;
    void setFlag(bool value);

protected:
    void run();
private:
    QString videoPath_;
    static enum VideoStatus videoStatus;
    bool flag;//是否为第一次点击
    VideoDecord *videoDecord;
    double factor;//视频倍数
    bool stopFlag_;
signals:
    void sendImg(QImage);
    void videoEnd();

};

#endif
