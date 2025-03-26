#ifndef VIDEOREPLAYWIDGET_H
#define VIDEOREPLAYWIDGET_H

#include <QPushButton>
#include "mywidget/bubblebutton.h"

class VideoReplayWidget : public BubbleButton
{
    Q_OBJECT
public:
    explicit VideoReplayWidget(QWidget *parent = nullptr);
protected:
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:
    void doReplay();

private:
    BubbleButton *bubbleButton;  // 使用组合而不是继承
};

#endif
