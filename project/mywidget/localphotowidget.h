#ifndef LOCALPHOTOWIDGET_H
#define LOCALPHOTOWIDGET_H

#include <QPushButton>
#include "mywidget/bubblebutton.h"

class LocalPhotoWidget : public BubbleButton
{
    Q_OBJECT
public:
    explicit LocalPhotoWidget(QWidget *parent = nullptr);  // 注意这里父类应该是 QWidget 而不是 QPushButton
protected:
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:
    void lookPhoto();

private:
    BubbleButton *bubbleButton;  // 使用组合而不是继承
};

#endif // LOGINWIDGET_H
