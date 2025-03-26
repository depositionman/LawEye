#ifndef PLAYBACKWIN_H
#define PLAYBACKWIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include "thread/playvideothread.h"
#include <QLabel>
#include "mywidget/mycombox.h"
#include "mywidget/playicon.h"
#include <QProgressBar>

class PlayBackWin : public QWidget
{
    Q_OBJECT
public:
    explicit PlayBackWin(QString videoPath, QString photoPath,QString equipmentNumber);
    ~PlayBackWin();
    void init_allWin();
    void changeProgressBar();
    QString getVideoPath() const;
    void setVideoPath(const QString &videoPath);

protected:
    void paintEvent(QPaintEvent *event);
private:
    QString videoPath_;
    PlayVideoThread *playVideoThread_;
    QLabel *video_;//在窗口中播放的图片
    MyComBox *factorBox_;
    PlayIcon *playIcon_;//播放图标
    QImage videoImg_;//用于接收视频解析出来的图片播放使用
    int flag_;//构造的标志位
    QString photoPath_;
    QString equipmentNumber_;
    QString videoTime_;
    QProgressBar *progressBar_;
    int value_;//进度条的值
signals:
    void backLookVideoWin();
    void lastVideoSignal();
    void nextVideoSignal();
    void stopThread();
public slots:
    void receiveImg(QImage img);
    void replay();
    void playVideo();
    void getImage();
    void lastVideo();
    void nextVideo();
};

#endif // PLAYBACKWIN_H
