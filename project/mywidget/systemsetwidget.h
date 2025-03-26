#ifndef SYSTEMSETWIDGET_H
#define SYSTEMSETWIDGET_H

#include <QPushButton>
#include "mywidget/bubblebutton.h"

class SystemSetWidget : public BubbleButton
{
    Q_OBJECT
public:
    explicit SystemSetWidget(QWidget *parent = nullptr);
protected:
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:
    void openSetWin();

private:
    BubbleButton *bubbleButton;  // 使用组合而不是继承
};

#endif
