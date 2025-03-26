#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QImage>
#include "mywidget/loginwidget.h"
#include "view/loginwin.h"
#include "data/videoqueue.h"
#include "thread/videothread.h"
#include "view/lookphotowin.h"
#include "view/lookvideowin.h"
#include "view/viewlogwin.h"
#include "view/transcodingwin.h"
#include "thread/playbackthread.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void init_allWin();
    void init_navWin();
    void init_videoWin();
    void init_functionWin();
protected:
    void paintEvent(QPaintEvent *event);
private:
    QVBoxLayout *mainLayout_;
    QWidget *navWidget_;
    QWidget *videoWidget_;
    QWidget *functionWidget_;
    QImage videoImg_;
    QLabel video_;
    QString equipmentNumber_;
    LoginWidget *loginWidget_;
    LoginWin *loginwin_;
    VideoQueue *videoQueue_;//存放视频的队列
    QString videoPath_;
    VideoThread *videoThread_;
    QString photoPath_;
    LookPhotoWin *lookPhotoWin_;
    QString policeNumber_;
    LookVideoWin *lookVideoWin_;
    ViewLogWin *viewLogWin_;
    TranscodingWin *transcodingWin_;
    PlayBackThread *playBackThread_;
signals:
    void sendEquipmentNumber(QString);
    void sendFirstPhotoPath(QString);   //将封面照片的路径发送给线程端
    void saveDate();    //提醒解码线程保存该次视频的数据去数据库
    void occurOperation(QString); //告诉日志发生了操作
    void backSetWin();//返回设置界面的信号
    void openLoginWin();
public slots:
    void receiveImg(QImage);                //获取摄像头图片的槽
    void createLoginWin();                  //创建登录窗口的槽
    void createSetWin();                    //创建设置窗口的槽
    void createTranscodeWin();              //创建转码窗口的槽
    void takePicture();                     //拍照功能的槽
    void createVideoReplayWin();            //创建视频回放窗口的槽
    void createFindPhotoWin();              //创建查看现场照片的槽
    void createCheckLogWin();               //创建查看日志的槽
    void receiveEquipmentNumber(QString);   //获取设备编号的槽
    void backMainWin();                     //关闭登录界面回放主界面的槽
    void backMainWinAfterlogin(QString);    //完成登录后登录界面返回主界面的槽
    void receiveVideoPath(QString);         //获取存放视频的文件夹路径
    void receivePhotoPath(QString);         //获取存放图片的文件夹路径
    void LookPhotoWinbackMainWin();         //从查看照片窗口回到主窗口
    void saveFirstPhoto();                  //保存视频第一帧的图片
    void closeWin();                        //关闭窗口的操作
    void LookVideoWinbackMainWin();         //从查看视频窗口回到主窗口
    void ViewLogwinbackMainWin();           //从查看日志窗口回到主窗口
    void TrancewinbackMainWin();           //从转码窗口回到主窗口
};

#endif // MAINWIDGET_H
