#include "playbackthread.h"
#include "util/encoding.h"
#include "QDebug"
#include "controller/videocontroller.h"
#include <QDateTime>

PlayBackThread::PlayBackThread(VideoQueue* &videoQueue,QString savePath,QString policeNumber)
{
    videoQueue_ = videoQueue;
    savePath_ = savePath; //文件夹的路径
    policeNumber_ = policeNumber;
    firstPhotoPath_ = "";
    saveFlag_ = false;
}

PlayBackThread::~PlayBackThread()
{
    delete videoQueue_;
    videoQueue_ = nullptr;
    delete encoding_;
    encoding_ = nullptr;
}

bool PlayBackThread::saveFlag() const
{
    return saveFlag_;
}

void PlayBackThread::setSaveFlag(bool saveFlag)
{
    saveFlag_ = saveFlag;
}

void PlayBackThread::run()
{
    //帧率
    frame_ = 0;
    //为了获取不同的文件名
    VideoController videoController;
    encoding_ = new Encoding;
    // 获取当前日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    // 将日期和时间格式化为字符串
    formattedDateTime_ = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");
    formattedDateTimeName_ = currentDateTime.toString("yyyy-MM-dd_HH-mm-ss");
    //编码路径
    QString path = savePath_ + "/" + formattedDateTimeName_ + ".h264";
    encoding_->preEncoding(path);
    while (true) {
            QMutexLocker locker(&videoQueue_->mutex);  // 加锁
            if (videoQueue_->queue.isEmpty()) {
                videoQueue_->condition.wait(&videoQueue_->mutex);   // 等待生产者通知
            }
            if(frame_ % 1510 == 0 && frame_ != 0){//1510
                encoding_->writeTailFrame();
                //将视频信息同步到数据库中
                videoController.appendVideoInfo(formattedDateTimeName_, path, QString::number(frame_/25.25)+'s', formattedDateTime_, policeNumber_,firstPhotoPath_);
                // 获取当前日期和时间
                QDateTime currentDateTime = QDateTime::currentDateTime();
                // 将日期和时间格式化为字符串
                formattedDateTime_ = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");
                formattedDateTimeName_ = currentDateTime.toString("yyyy-MM-dd_HH-mm-ss");
                //更新编码路径
                path = savePath_ + "/" + formattedDateTimeName_ + ".h264";
                //防止后续frame溢出 写入数据库后再清除
                frame_ = 0;
                encoding_->preEncoding(path);
            }
            encoding_->encode(videoQueue_->queue.dequeue());//从队列中取出数据
            //存入第一帧图片的路径
            if(frame_ == 0){
               emit saveFirstPhoto();
            }
            //处理完一帧图片进行++操作
            ++frame_;
    }
}

void PlayBackThread::receiveFirstPhotoPath(QString firstPhotoPath)
{
    firstPhotoPath_ = firstPhotoPath;
}

void PlayBackThread::saveDate()
{
    encoding_->writeTailFrame();
    //防止最后一次未满1min 也需同步到数据库中
    VideoController videoController;
    QString path = savePath_ + "/" + formattedDateTimeName_ + ".h264";
    //将视频信息同步到数据库中
    videoController.appendVideoInfo(formattedDateTimeName_, path, QString::number(frame_/25)+'s', formattedDateTime_, policeNumber_,firstPhotoPath_);
    saveFlag_ = true;
}

