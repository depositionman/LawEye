#include "videodecord.h"
#include <QImage>
#include <QDebug>
#include "util/simpleQtLogger.h"

VideoDecord::VideoDecord(QString videoPath)
{
    videoPath_ = videoPath;
    this->openFile();
    this->getVideoStream();
    this->findDecord();
    this->preDecord();
}

VideoDecord::~VideoDecord() {
    av_free(buffer);
    av_free(bufferYuv);
    av_frame_free(&picture);
    av_frame_free(&rgbPicture);
    av_frame_free(&picture2);
    av_frame_free(&yuvPicture);
    avcodec_close(pcodecCtx);
    avformat_close_input(&pformatCtx);
    sws_freeContext(swsCtx);
    sws_freeContext(swsCtxYuv);
}

void VideoDecord::openFile()
{
    //注册组件
    av_register_all();
    //注册设备
    avdevice_register_all();
    //初始化AVFormatContext* pFormatCtx
    pformatCtx = avformat_alloc_context();
    //打开对象
    //摄像头Integrated Camera
//    AVInputFormat *fmt = av_find_input_format("dshow");//查找摄像头输入流（通过Directx show）
//    int res = avformat_open_input(&pformatCtx,"video=Integrated Camera", fmt, nullptr);
    int res = avformat_open_input(&pformatCtx, videoPath_.toUtf8(), nullptr, nullptr);
    if(res != 0)
    {
//        LS_INFO("avformat_open_input error");
        return;
    }
}

void VideoDecord::getVideoStream()
{
    //3.从AVFormatContext解析出流媒体信息
    int res = avformat_find_stream_info(pformatCtx, nullptr);
    if(res != 0)
    {
//        LS_INFO("avformat_find_stream_info error");
        return;
    }
    //4.从流信息中取出视频流
    videoIndex = -1;//用于保存视频流对应的下标
    //pformatCtx->nb_streams流的数量
    for(int i = 0; i < pformatCtx->nb_streams; ++i)
    {
        if(pformatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoIndex = i;
            break;
        }
    }
    if(videoIndex == -1)
    {
//        LS_INFO("gain video stream error");
        return;
    }
//    LS_INFO("gain video stream success" << "index:" << videoIndex);
}

void VideoDecord::findDecord()
{
    //5.获取合适的编解码器
    pcodecCtx = pformatCtx->streams[videoIndex]->codec;
    decoder = avcodec_find_decoder(pcodecCtx->codec_id);
    if(decoder == nullptr)
    {
//        LS_INFO("not find suitable decoder");
        return;
    }
    //6.打开解码器
    int res = avcodec_open2(pcodecCtx, decoder, nullptr);
    if(res != 0)
    {
//        LS_INFO("open decoder error");
        return;
    }
}

void VideoDecord::preDecord()
{
    pkt = (AVPacket *)malloc(sizeof(AVPacket));
    //从上下文容器中读取一帧帧的视频流数据保存到pkt中
    //初始化AVFrame 需要两个 一个是压缩的图像码流 第二个是解压后的图像码流(去除无用像素信息)
    picture = av_frame_alloc();//用于保存压缩的图像码流信息
    rgbPicture = av_frame_alloc();//用于保存解压后的图像码流信息

    picture2 = av_frame_alloc();
    yuvPicture = av_frame_alloc();
    //初始化格式
    picture->width = pcodecCtx->width;
    picture->height = pcodecCtx->height;
    picture->format = pcodecCtx->pix_fmt;
    rgbPicture->width = pcodecCtx->width;
    rgbPicture->height = pcodecCtx->height;
    rgbPicture->format = pcodecCtx->pix_fmt;

    picture2->width = pcodecCtx->width;
    picture2->height = pcodecCtx->height;
    picture2->format = pcodecCtx->pix_fmt;
    yuvPicture->width = pcodecCtx->width;
    yuvPicture->height = pcodecCtx->height;
    yuvPicture->format = pcodecCtx->pix_fmt;
    //获取最终要生成的每一张图片的尺寸
    int numbyte = avpicture_get_size(AV_PIX_FMT_RGB32, picture->width, picture->height);

    int numbyteYuv = avpicture_get_size(AV_PIX_FMT_YUV420P, picture2->width, picture2->height);
    //创建图片缓冲区
    buffer = (uint8_t *)av_malloc(numbyte * sizeof (uint8_t));

    bufferYuv = (uint8_t *)av_malloc(numbyteYuv * sizeof (uint8_t));
    //初始化图片，用于保存最终生成的图片
    avpicture_fill((AVPicture*)rgbPicture, buffer, AV_PIX_FMT_RGB32,
                   pcodecCtx->width, pcodecCtx->height);

    avpicture_fill((AVPicture*)yuvPicture, bufferYuv, AV_PIX_FMT_YUV420P,
                   pcodecCtx->width, pcodecCtx->height);
    //设置过滤规则（转置）
    swsCtx = sws_getContext(pcodecCtx->width, pcodecCtx->height, pcodecCtx->pix_fmt,
                                       pcodecCtx->width, pcodecCtx->height, AV_PIX_FMT_RGB32,
                                       SWS_BICUBIC, nullptr, nullptr,nullptr);

    swsCtxYuv = sws_getContext(pcodecCtx->width, pcodecCtx->height, pcodecCtx->pix_fmt,
                                       pcodecCtx->width, pcodecCtx->height, AV_PIX_FMT_YUV420P,
                                       SWS_BICUBIC, nullptr, nullptr,nullptr);
}

void VideoDecord::decordToH264()
{
    FILE *fp = fopen("../video/temp.h264", "wb");
    while(av_read_frame(pformatCtx, pkt) == 0)
    {
        if(pkt->stream_index == videoIndex)//判断本帧是否为视频数据流
        {
            fwrite(pkt->data, pkt->size, 1, fp);//将一帧的码流数据写入文件
        }
    }
    fclose(fp);
}

void VideoDecord::decordToImage()
{
    int count = 0;
    char imgPath[256] = { 0 };
    while(av_read_frame(pformatCtx, pkt) == 0)
    {
        if(pkt->stream_index == videoIndex)//判断本帧是否为视频数据流
        {
            //让每帧画面转换原始像素图片，在Qt窗口中展示
            int got_picture_ptr = -1;//操作的状态信息 不为0表示解码成功
            //从一帧视频码流信息中解析出图像信息
            avcodec_decode_video2(pcodecCtx, picture, &got_picture_ptr, pkt);
            if(got_picture_ptr != 0)//解码成功
            {
                //剔除图像中的无效信息，生成最终的原始图像
                sws_scale(swsCtx, picture->data, picture->linesize,0, picture->height,
                          rgbPicture->data, rgbPicture->linesize);
                ++count;
                //将图片转存到QImage中
                QImage img = QImage((uchar*)buffer, pcodecCtx->width, pcodecCtx->height,
                                    QImage::Format_RGB32);
                sprintf(imgPath, "../image/img%d.jpg",count);
                //保存成图片文件
                img.save(imgPath);
            }
        }
    }
}

AVFormatContext *VideoDecord::getPformatCtx() const
{
    return pformatCtx;
}

void VideoDecord::setPformatCtx(AVFormatContext *value)
{
    pformatCtx = value;
}

AVCodecContext *VideoDecord::getPcodecCtx() const
{
    return pcodecCtx;
}

void VideoDecord::setPcodecCtx(AVCodecContext *value)
{
    pcodecCtx = value;
}

int VideoDecord::getVideoIndex() const
{
    return videoIndex;
}

void VideoDecord::setVideoIndex(int value)
{
    videoIndex = value;
}

AVCodec *VideoDecord::getDecoder() const
{
    return decoder;
}

void VideoDecord::setDecoder(AVCodec *value)
{
    decoder = value;
}

AVPacket *VideoDecord::getPkt() const
{
    return pkt;
}

void VideoDecord::setPkt(AVPacket *value)
{
    pkt = value;
}

AVFrame *VideoDecord::getPicture() const
{
    return picture;
}

void VideoDecord::setPicture(AVFrame *value)
{
    picture = value;
}

AVFrame *VideoDecord::getRgbPicture() const
{
    return rgbPicture;
}

void VideoDecord::setRgbPicture(AVFrame *value)
{
    rgbPicture = value;
}

SwsContext *VideoDecord::getSwsCtx() const
{
    return swsCtx;
}

void VideoDecord::setSwsCtx(SwsContext *value)
{
    swsCtx = value;
}

uint8_t *VideoDecord::getBuffer() const
{
    return buffer;
}

void VideoDecord::setBuffer(uint8_t *value)
{
    buffer = value;
}

QString VideoDecord::getVideoPath() const
{
    return videoPath_;
}

void VideoDecord::setVideoPath(const QString &videoPath)
{
    videoPath_ = videoPath;
}

AVFrame *VideoDecord::getYuvPicture() const
{
    return yuvPicture;
}

void VideoDecord::setYuvPicture(AVFrame *value)
{
    yuvPicture = value;
}

uint8_t *VideoDecord::getBufferYuv() const
{
    return bufferYuv;
}

void VideoDecord::setBufferYuv(uint8_t *value)
{
    bufferYuv = value;
}

SwsContext *VideoDecord::getSwsCtxYuv() const
{
    return swsCtxYuv;
}

void VideoDecord::setSwsCtxYuv(SwsContext *value)
{
    swsCtxYuv = value;
}

AVFrame *VideoDecord::getPicture2() const
{
    return picture2;
}

void VideoDecord::setPicture2(AVFrame *value)
{
    picture2 = value;
}
