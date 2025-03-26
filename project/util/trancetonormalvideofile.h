#ifndef TRANCETONORMALVIDEOFILE_H
#define TRANCETONORMALVIDEOFILE_H

#include <QString>
#include <QObject>
extern "C"
{
    #include "libavcodec/avcodec.h"     //编解码库
    #include "libavdevice/avdevice.h"   //输入输出设备库；读取摄像头的
    #include "libavfilter/avfilter.h"   //音视频滤镜库；进行音视频处理与编辑
    #include "libavformat/avformat.h"   //文件格式和协议库
    #include "libavutil/avutil.h"       //音视频处理
    #include "libswresample/swresample.h"   //音频重采样
    #include "libswscale/swscale.h"     //图像进行格式转换
}
class TranceToNormalVideoFile : public QObject
{
   Q_OBJECT
public:
    TranceToNormalVideoFile();
    void loadSrcFile(QString filePath);
    void tranceToMp4(QString filePath);
    void tranceFile();
private:
    //srcFormatCtx待转化的上下文容器  destFormatCtx转化后的上下文容器
    AVFormatContext *srcFormatCtx;
    AVFormatContext *destFormatCtx;
    AVOutputFormat *outputFormat;
    AVPacket *pkt;//用于一帧码流数据
    int videoIndex;//视频流的对应下标
    AVStream *newStream;
signals:
    void changeProgressBar();
    void tranceSuccess();
};

#endif // TRANCETONORMALVIDEOFILE_H
