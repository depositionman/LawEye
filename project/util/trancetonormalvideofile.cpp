#include "trancetonormalvideofile.h"
#include <QDebug>
//#include "util/simpleQtLogger.h"

TranceToNormalVideoFile::TranceToNormalVideoFile()
{
    //1.注册组件
    av_register_all();
    //初始化源/目标容器
    this->srcFormatCtx = avformat_alloc_context();
    this->destFormatCtx = avformat_alloc_context();
    this->videoIndex = -1;
    this->pkt = (AVPacket*)malloc(sizeof(AVPacket));
}

void TranceToNormalVideoFile::loadSrcFile(QString filePath)
{
    //1.打开源文件
    int res = avformat_open_input(&this->srcFormatCtx, filePath.toUtf8(), nullptr, nullptr);
    if(res != 0)
    {
//        L_INFO("avformat_open_input is error");
        return;
    }
    //2.获取码流
    res = avformat_find_stream_info(this->srcFormatCtx, nullptr);
    if(res < 0)
    {
//        L_INFO("avformat_find_stream_info is error");
        return;
    }
    //3.查找视频流
    for(int i = 0; i < this->srcFormatCtx->nb_streams; ++i)
    {
        if(this->srcFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            this->videoIndex = i;
            break;
        }
    }
    if(this->videoIndex == -1)
    {
//        L_INFO("video stream is not find");
        return;
    }
//    L_INFO("videoIndex:"+this->videoIndex);
}

void TranceToNormalVideoFile::tranceToMp4(QString filePath)
{
    //1.创建并打开新转码的目标文件
    this->outputFormat = av_guess_format(nullptr, filePath.toUtf8(), nullptr);
    if(this->outputFormat == nullptr)
    {
//        L_INFO("av_guess_format is error");
        return;
    }
    //2.设置视频格式
    this->destFormatCtx->oformat = this->outputFormat;
    //3.打开新的图像视频流
    int res = avio_open(&this->destFormatCtx->pb, filePath.toUtf8(), AVIO_FLAG_WRITE);
    if(res < 0)
    {
//        L_INFO("avio_open is error");
        return;
    }
    //4.新建视频流
    newStream = avformat_new_stream(this->destFormatCtx,nullptr);
    if(newStream == nullptr)
    {
//        L_INFO("avformat_new_stream is error");
        return;
    }
    //5.设置视频流参数
    avcodec_parameters_copy(newStream->codecpar
                            ,this->srcFormatCtx->streams[this->videoIndex]->codecpar);
    newStream->codecpar->codec_tag = 0;
    //6.写入头帧
    res = avformat_write_header(this->destFormatCtx, nullptr);
    if(res < 0)
    {
//        L_INFO("avformat_write_header is error"+res);
        return;
    }
    //调用转码
    tranceFile();
}

void TranceToNormalVideoFile::tranceFile()
{
    //1.创建新的码流数据包 AVPacket
    int size = this->newStream->codecpar->width * this->newStream->codecpar->height;
    int res = av_new_packet(this->pkt, size);
    if(res != 0)
    {
//        L_INFO("av_new_packet is error");
        return;
    }
    //2.计算总帧数
    int frameCount = 0;
    while(av_read_frame(this->srcFormatCtx,this->pkt) == 0)
    {
//        L_INFO("this pkt stream index" + this->pkt->stream_index);
        if(this->pkt->stream_index == this->videoIndex)
        {
            ++frameCount;
            qDebug() << "frameCount" << frameCount;
            emit changeProgressBar();
        }
        //3.设置时间基
        //3-1无时间基
        if(this->pkt->pts == AV_NOPTS_VALUE)
        {
            //获取原视频文件时间基
            AVRational timeBase1 = this->srcFormatCtx->streams[this->videoIndex]->time_base;
            //计算两帧之间的时长
            int64_t duration = (double)AV_TIME_BASE /
                    (double)av_q2d(this->srcFormatCtx->streams[this->videoIndex]->r_frame_rate);
            //计算显示时间基：(帧数 * 两帧之间的时长) / (输入的时间基 * AV_TIME_BASE)
            this->pkt->pts = (double)(frameCount * duration) /
                    (double)(av_q2d(timeBase1) * AV_TIME_BASE);
            //设置解码时间基
            this->pkt->dts = this->pkt->pts;
            //设置时长
            this->pkt->duration = (double) duration / (double)(av_q2d(timeBase1) * AV_TIME_BASE);
        }
        else if(this->pkt->pts < this->pkt->dts)
            continue;
        //时间基转换
        this->pkt->dts = av_rescale_q_rnd(this->pkt->dts,
                                        this->srcFormatCtx->streams[this->videoIndex]->time_base,
                newStream->time_base,(AVRounding)(AV_ROUND_INF | AV_ROUND_PASS_MINMAX));
        this->pkt->pts = av_rescale_q_rnd(this->pkt->pts,
                                        this->srcFormatCtx->streams[this->videoIndex]->time_base,
                newStream->time_base,(AVRounding)(AV_ROUND_INF | AV_ROUND_PASS_MINMAX));
        //两帧之间的时长
        this->pkt->duration = av_rescale_q(this->pkt->duration,
                                           this->srcFormatCtx->streams[this->videoIndex]->time_base,
                newStream->time_base);
        //数据流位置
        this->pkt->pos = -1;
        //关键帧标志
        this->pkt->flags |= AV_PKT_FLAG_KEY;
        //AVPacket在码流数据中的下标
        this->pkt->stream_index = 0;
        //写入这帧数据
        av_interleaved_write_frame(this->destFormatCtx,this->pkt);
        //重置码流数据
        av_packet_unref(this->pkt);
    }//while(av_read_frame(this->srcFormatCtx,this->pkt) == 0)
    //写入尾帧
    av_write_trailer(this->destFormatCtx);
    //关闭流
    avio_close(this->destFormatCtx->pb);
    //释放目标文件上下文对象
    av_free(this->destFormatCtx);
    //关闭源文件
    avformat_close_input(&this->srcFormatCtx);
    //释放源文件上下文对象
    av_free(this->srcFormatCtx);
//    L_INFO("trance is success..");
    emit tranceSuccess();
}
