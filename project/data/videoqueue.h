#ifndef VIDEOQUEUE_H
#define VIDEOQUEUE_H

#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QImage>
#include "util/mydecord.h"

class VideoQueue
{
public:
    VideoQueue();
    QQueue<AVFrame *> queue;          // 数据队列
    QMutex mutex;               // 互斥锁
    QWaitCondition condition;   // 条件变量
};

#endif // VIDEOQUEUE_H
