#include "localphotowidget.h"

LocalPhotoWidget::LocalPhotoWidget(QWidget *parent)
    : BubbleButton(parent) // 继承 BubbleButton 而不是 QPushButton
{
    setText("现场图片");
    setGeometry(0, 0, 120, 60); // 设置按钮大小
    startBubbleAnimation(); // 启动气泡动画
}

void LocalPhotoWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // 在鼠标释放时，发出打开登录窗口的信号
    emit lookPhoto();

    // 调用父类的 mouseReleaseEvent 以确保正常的按钮行为
    BubbleButton::mouseReleaseEvent(e);
}
