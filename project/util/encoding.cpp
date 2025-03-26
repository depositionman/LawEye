#include "encoding.h"
#include <QDebug>
#include <QTimer>
//#include <util/simpleQtLogger.h>

Encoding::Encoding()
{
}

void Encoding::preEncoding(QString path)
{
    //1.注册组件
    av_register_all();
    //为AVFormatctX分配空间
    pFormatCtx = avformat_alloc_context();
    //2.猜测视频内容的格式
    AVOutputFormat *pOutCtx = av_guess_format(nullptr, path.toUtf8(),nullptr);
    if(pOutCtx == nullptr)
    {
//        L_INFO("av_guess_format is error");
        return;
    }
    //3.设置输出格式(指定输出文件)
    this->pFormatCtx->oformat = pOutCtx;
    //4.打开视频文件流
    int res = avio_open(&pFormatCtx->pb,path.toUtf8(),AVIO_FLAG_WRITE);
    if(res < 0)
    {
//        L_INFO("avio_open is error");
        return;
    }
    //5.新建视频流
    AVStream *newStream = avformat_new_stream(pFormatCtx,nullptr);
    if(newStream == nullptr)
    {
//        L_INFO("avformat_new_stream is error");
        return;
    }
    //6.查找编码器
    pCodeCtx = newStream->codec;//视频流的类型
    //设置编码器的初始参数
    //基本参数
    pCodeCtx->width = this->width;
    pCodeCtx->height = this->height;
    pCodeCtx->time_base = {1,25};//时间机
    pCodeCtx->bit_rate = 400000;//码率
    pCodeCtx->framerate = {25,1};//帧率
    pCodeCtx->gop_size = 10;//设定10帧为一个单元进行传输
    //与视频清晰度有关的参数
    pCodeCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    pCodeCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    pCodeCtx->qmax = 51;
    pCodeCtx->qmin = 10;//量化参数(q值越小压缩程度越少，画面清晰，生成图片更大)
    pCodeCtx->max_b_frames = 0;//不使用b帧
    pCodeCtx->codec_id = pOutCtx->video_codec;
    AVCodec *pEncode = avcodec_find_encoder(pCodeCtx->codec_id);
    if(pEncode == nullptr)
    {
//        L_INFO("avcodec_find_encoder is error");
        return;
    }
    //7.打开编码器
    res = avcodec_open2(pCodeCtx,pEncode,nullptr);
    if(res != 0)
    {
//        L_INFO("avcodec_open2 is error");
        return;
    }
    //8.写入头部信息
    res = avformat_write_header(pFormatCtx,nullptr);
    if(res < 0)
    {
//        L_INFO("avformat_write_header is error");
        return;
    }
}

void Encoding::encode(AVFrame *frame)
{
    //为编码后的数据包开空间
    pkt = av_packet_alloc();
    // 设置帧的顺序号
    frame->pts = this->ptsIndex++;

    // 发送一帧图像数据给编码器进行编码
    int res = avcodec_send_frame(pCodeCtx, frame);
    if (res != 0)
    {
//        L_INFO("avcodec_send_frame is error");
        return;
    }

    // 处理编码后的数据
    while (res >= 0)
    {
        res = avcodec_receive_packet(pCodeCtx, pkt);
        if (res == AVERROR(EAGAIN) || res == AVERROR_EOF)
        {
            qDebug() << "no more frame";
            break;
        }
        else if (res < 0)
        {
//            L_INFO("Error during encoding");
            return;
        }

        // 写入文件
        res = av_interleaved_write_frame(pFormatCtx, pkt);
        if (res != 0)
        {
//            L_INFO("av_interleaved_write_frame is error");
        }

        // 重置 pkt，为下一帧准备
        av_packet_unref(pkt);
    }
}


void Encoding::writeTailFrame()
{
    //写入尾帧
    av_write_trailer(pFormatCtx);
    //关闭输入流
    avio_close(pFormatCtx->pb);
    //释放视频信息
    avformat_free_context(pFormatCtx);
}


