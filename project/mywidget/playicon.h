#ifndef PLAYICON_H
#define PLAYICON_H

#include <QObject>
#include <QLabel>

class PlayIcon : public QLabel
{
    Q_OBJECT
public:
    PlayIcon();
protected:
    void mouseReleaseEvent(QMouseEvent *ev);
signals:
    void changeVideoStatus();
};

#endif // PLAYICON_H
