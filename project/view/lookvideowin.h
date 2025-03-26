#ifndef LOOKVIDEOWIN_H
#define LOOKVIDEOWIN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include <QPushButton>
#include <QString>
#include <QListWidget>
#include "view/playbackwin.h"

class LookVideoWin : public QWidget
{
    Q_OBJECT
public:
    explicit LookVideoWin(QString photoPath,QString equipmentNumber);
    void init_allWin();
    void checkVideo();
    int startRow_;
    QListWidget *listWidget_;
    bool findFlag_;
    QString startTimeString_;
    QString endTimeString_;
    PlayBackWin *playBackWin_;
    QString photoPath_;
    QString equipmentNumber_;
    int index_;//播放的视频下标
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void backMainWin();
    void changeVideo(QString);
public slots:
    void upPage();
    void downPage();
    void playVideo(const QModelIndex &index);
    void changeVideoByTime(QDateTime datetime);
    void backLookVideoWin();
    void sendLastVideoPath();
    void sendNextVideoPath();
};

#endif // LOOKVIDEOWIN_H
