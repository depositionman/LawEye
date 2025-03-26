#ifndef PLAYBACKTHREAD_H
#define PLAYBACKTHREAD_H

#include <QObject>
#include <QThread>
#include "data/videoqueue.h"
#include <QString>
#include "util/encoding.h"

class PlayBackThread : public QThread
{
    Q_OBJECT
public:
    explicit PlayBackThread(VideoQueue* &videoQueue,QString savePath,QString policeNumber);
    ~PlayBackThread();
    bool saveFlag() const;
    void setSaveFlag(bool saveFlag);

private:
    QString savePath_;
    VideoQueue* videoQueue_;
    QString policeNumber_;
    //第一帧图片的路径
    QString firstPhotoPath_;
    //现在时间的字符串
    QString formattedDateTime_;
    QString formattedDateTimeName_;
    int frame_;
    Encoding *encoding_;
    bool saveFlag_;//保存最后一个文件内容成功的标志位
protected:
    void run();
signals:
    void saveFirstPhoto();
public slots:
    void receiveFirstPhotoPath(QString);
    void saveDate();
};

#endif // PLAYBACKTHREAD_H
