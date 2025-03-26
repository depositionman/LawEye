#ifndef MYDECORD_H
#define MYDECORD_H

#include <QString>
#include <QObject>
#include <QImage>
extern "C"
{
    #include "libavcodec/avcodec.h"     //编解码库
    #include "libavdevice/avdevice.h"   //输入输出设备库；读取摄像头的
    #include "libavfilter/avfilter.h"   //音视频滤镜库；进行音视频处理与编辑
    #include "libavformat/avformat.h"   //文件格式和协议库
    #include "libavutil/avutil.h"       //音视频处理
    #include "libswresample/swresample.h"   //音频重采样
    #include "libswscale/swscale.h"     //图像进行格式转换
    #include <libavutil/imgutils.h>
}

class MyDecord : public QObject
{
    Q_OBJECT
public:
    MyDecord(QString cameraName,QString videoPath = "");
    ~MyDecord();
    void openFile(QString cameraName);
    void getVideoStream();
    void findDecord();
    void preDecord();//解码前的准备工作
    void decordToH264();
    void decordToImage();
    AVFormatContext *getPformatCtx() const;
    void setPformatCtx(AVFormatContext *value);

    AVCodecContext *getPcodecCtx() const;
    void setPcodecCtx(AVCodecContext *value);

    int getVideoIndex() const;
    void setVideoIndex(int value);

    AVCodec *getDecoder() const;
    void setDecoder(AVCodec *value);

    AVPacket *getPkt() const;
    void setPkt(AVPacket *value);

    AVFrame *getPicture() const;
    void setPicture(AVFrame *value);

    AVFrame *getRgbPicture() const;
    void setRgbPicture(AVFrame *value);

    SwsContext *getSwsCtx() const;
    void setSwsCtx(SwsContext *value);

    uint8_t *getBuffer() const;
    void setBuffer(uint8_t *value);

    QString getVideoPath() const;
    void setVideoPath(const QString &videoPath);


    AVFrame *getYuvPicture() const;
    void setYuvPicture(AVFrame *value);

    uint8_t *getBufferYuv() const;
    void setBufferYuv(uint8_t *value);

    SwsContext *getSwsCtxYuv() const;
    void setSwsCtxYuv(SwsContext *value);

    AVFrame *getPicture2() const;
    void setPicture2(AVFrame *value);

private:
    AVFormatContext *pformatCtx;
    AVCodecContext *pcodecCtx;//存储编解码器信息
    int videoIndex;//视频文件的下标
    AVCodec *decoder;//解码器
    AVPacket *pkt;
    AVFrame *picture;
    AVFrame *rgbPicture;
    SwsContext *swsCtx;
    uint8_t *buffer;
    QString videoPath_;
    //下面是转成yuv格式用到的变量
    AVFrame *picture2;
    AVFrame *yuvPicture;
    uint8_t *bufferYuv;
    SwsContext *swsCtxYuv;
signals:
    void sendImg(QImage);
};

#endif // MYDECORD_H
