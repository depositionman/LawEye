#include "playvideothread.h"
#include <QImage>
#include <QDebug>
enum VideoStatus PlayVideoThread::videoStatus = START;

PlayVideoThread::PlayVideoThread(QString videoPath)
{
    stopFlag_ = false;
    videoPath_ = videoPath;
    factor = 1.0;
    flag = false;
}

PlayVideoThread::~PlayVideoThread()
{
    delete videoDecord;
    videoDecord = nullptr;
}

void PlayVideoThread::stop()
{
    stopFlag_ = true;
}

void PlayVideoThread::run()
{
//    qDebug() << "开启播放线程";
    flag = true;//线程已经开启
    //对视频进行解码
    videoDecord = new VideoDecord(videoPath_);
    while(av_read_frame(videoDecord->getPformatCtx(), videoDecord->getPkt()) == 0)
    {
        if(videoDecord->getPkt()->stream_index == videoDecord->getVideoIndex())//判断本帧是否为视频数据流
        {
            //让每帧画面转换原始像素图片，在Qt窗口中展示
            int got_picture_ptr = -1;//操作的状态信息 不为0表示解码成功
            //从一帧视频码流信息中解析出图像信息
            avcodec_decode_video2(videoDecord->getPcodecCtx(), videoDecord->getPicture(), &got_picture_ptr, videoDecord->getPkt());
            if(got_picture_ptr != 0)//解码成功
            {
                if(videoStatus != PAUSE)
                {
                    //剔除图像中的无效信息，生成最终的原始图像
                    sws_scale(videoDecord->getSwsCtx(), videoDecord->getPicture()->data, videoDecord->getPicture()->linesize,0, videoDecord->getPicture()->height,
                              videoDecord->getRgbPicture()->data, videoDecord->getRgbPicture()->linesize);
                    //将图片转存到QImage中
                    QImage img = QImage((uchar*)videoDecord->getBuffer(), videoDecord->getPcodecCtx()->width, videoDecord->getPcodecCtx()->height,
                                        QImage::Format_RGB32);
                    emit sendImg(img);
                }//if(videoStatus != PAUSE)
                const int sleepTime = 40.0/factor;
//                qDebug() << factor;
                QThread::msleep(sleepTime);
            }//if(got_picture_ptr != 0)
        }//if(videoDecord->getPkt()->stream_index == videoDecord->getVideoIndex())
        if(stopFlag_ == true){
            return;
        }
        av_packet_unref(videoDecord->getPkt());
    }//while(av_read_frame(videoDecord->getPformatCtx(), videoDecord->getPkt()) == 0)
    //播放结束触发信号
    emit videoEnd();
}

bool PlayVideoThread::getFlag() const
{
    return flag;
}

void PlayVideoThread::setFlag(bool value)
{
    flag = value;
}

bool PlayVideoThread::getStopFlag() const
{
    return stopFlag_;
}

void PlayVideoThread::setStopFlag(bool stopFlag)
{
    stopFlag_ = stopFlag;
}

double PlayVideoThread::getFactor() const
{
    return factor;
}

void PlayVideoThread::setFactor(double value)
{
    factor = value;
}


void PlayVideoThread::clearBuf()
{
    avcodec_flush_buffers(videoDecord->getPcodecCtx());
}

VideoStatus PlayVideoThread::getVideoStatus() const
{
    return videoStatus;
}

void PlayVideoThread::setVideoStatus(const VideoStatus &value)
{
    videoStatus = value;
}
