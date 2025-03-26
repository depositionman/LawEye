#ifndef CHECKLOGWIDGET_H
#define CHECKLOGWIDGET_H

#include <QPushButton>
#include "mywidget/bubblebutton.h"

class CheckLogWidget : public BubbleButton
{
    Q_OBJECT
public:
    explicit CheckLogWidget(QWidget *parent = nullptr);  // 注意这里父类应该是 QWidget 而不是 QPushButton
protected:
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:
    void checkLog();

private:
    BubbleButton *bubbleButton;  // 使用组合而不是继承
};

#endif // LOGINWIDGET_H
