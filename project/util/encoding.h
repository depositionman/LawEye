#ifndef ENCODING_H
#define ENCODING_H
#include <QObject>
#include <QString>

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
class Encoding : public QObject
{
    Q_OBJECT
public:
    Encoding();
    //编码前的准备工作
    void preEncoding(QString path);
    //编码
    void encode(AVFrame *frame);
    //写入尾帧
    void writeTailFrame();
private:
    AVFormatContext *pFormatCtx;
    AVCodecContext *pCodeCtx;
    AVPacket *pkt;//用于保存编码后的帧
    int ptsIndex = 0;
    int width = 1280;
    int height = 720;

    int count = 0;
    QString path;
};

#endif // ENCODING_H
