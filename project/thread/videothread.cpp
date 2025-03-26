#include "videothread.h"
#include "util/mydecord.h"
//#include "util/simpleQtLogger.h"
#include <qdebug.h>

VideoThread::VideoThread(VideoQueue* videoQueue,QString cameraName)
{
    cameraName_ = cameraName;
    flag_ = false;
    videoQueue_ = videoQueue;
}

VideoThread::~VideoThread()
{
    delete videoQueue_;
    videoQueue_ = nullptr;
}

void VideoThread::run()
{
//    LS_INFO("into VideoThread success");
    MyDecord *myDecord = new MyDecord(cameraName_);
    while(av_read_frame(myDecord->getPformatCtx(), myDecord->getPkt()) == 0)
    {
        if(myDecord->getPkt()->stream_index == myDecord->getVideoIndex())//判断本帧是否为视频数据流
        {
            //让每帧画面转换原始像素图片，在Qt窗口中展示
            int got_picture_ptr = -1;//操作的状态信息 不为0表示解码成功
            //从一帧视频码流信息中解析出图像信息
            avcodec_decode_video2(myDecord->getPcodecCtx(), myDecord->getPicture(), &got_picture_ptr, myDecord->getPkt());
            avcodec_decode_video2(myDecord->getPcodecCtx(), myDecord->getPicture2(), &got_picture_ptr, myDecord->getPkt());
            if(got_picture_ptr != 0)//解码成功
            {
                //剔除图像中的无效信息，生成最终的原始图像
                sws_scale(myDecord->getSwsCtx(), myDecord->getPicture()->data, myDecord->getPicture()->linesize,0, myDecord->getPicture()->height,
                          myDecord->getRgbPicture()->data, myDecord->getRgbPicture()->linesize);
                //将图片转存到QImage中
                QImage img = QImage((uchar*)myDecord->getBuffer(), myDecord->getPcodecCtx()->width, myDecord->getPcodecCtx()->height,
                                    QImage::Format_RGB32);
                emit sendImg(img);
                if(flag_ == true){
//                    qDebug() << "Source data pointers:" << myDecord->getPicture2()->data[0];
//                    qDebug() << "Source linesizes:" << myDecord->getPicture2()->linesize[0];
//                    qDebug() << "Destination data pointers:" << myDecord->getYuvPicture()->data[0];
//                    qDebug() << "Destination linesizes:" << myDecord->getYuvPicture()->linesize[0];
                    //剔除图像中的无效信息，生成最终的原始图像
                    sws_scale(myDecord->getSwsCtxYuv(), myDecord->getPicture2()->data, myDecord->getPicture2()->linesize,0, myDecord->getPicture2()->height,
                              myDecord->getYuvPicture()->data, myDecord->getYuvPicture()->linesize);
                    //将从摄像头解码出来的数据存入队列中供录像回放线程使用
                    QMutexLocker locker(&videoQueue_->mutex);  // 加锁
                    videoQueue_->queue.enqueue(myDecord->getYuvPicture());     // 将数据放入队列
                    videoQueue_->condition.wakeOne();          // 唤醒等待的消费者
                }
            }
        }
        av_packet_unref(myDecord->getPkt());
    }
    delete myDecord;
    myDecord = nullptr;
}

bool VideoThread::flag() const
{
    return flag_;
}

void VideoThread::setFlag(bool flag)
{
    flag_ = flag;
}
