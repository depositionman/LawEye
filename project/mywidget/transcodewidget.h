#ifndef TRANSCODEWIDGET_H
#define TRANSCODEWIDGET_H

#include <QPushButton>
#include "mywidget/bubblebutton.h"

class TranscodeWidget : public BubbleButton
{
    Q_OBJECT
public:
    explicit TranscodeWidget(QWidget *parent = nullptr);
protected:
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:
    void openTranscodeWin();

private:
    BubbleButton *bubbleButton;  // 使用组合而不是继承
};

#endif
