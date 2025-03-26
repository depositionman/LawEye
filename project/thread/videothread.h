#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <QObject>
#include <QThread>
#include <QImage>
#include "data/videoqueue.h"

class VideoThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoThread(VideoQueue* videoQueue,QString cameraName);
    ~VideoThread();
    VideoQueue *videoQueue_;
    bool flag() const;
    void setFlag(bool flag);

protected:
    void run();
signals:
    void sendImg(QImage);
private:
    bool flag_;
    QString cameraName_;
public slots:
};

#endif // VIDEOTHREAD_H
