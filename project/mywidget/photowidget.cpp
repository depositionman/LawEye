#include "photowidget.h"

PhotoWidget::PhotoWidget(QWidget *parent)
    : BubbleButton(parent) // 继承 BubbleButton 而不是 QPushButton
{
    setText("现场拍照");
    setGeometry(0, 0, 120, 60); // 设置按钮大小
    startBubbleAnimation(); // 启动气泡动画
}

void PhotoWidget::mouseReleaseEvent(QMouseEvent *e)
{
    emit getPhoto();

    // 调用父类的 mouseReleaseEvent 以确保正常的按钮行为
    BubbleButton::mouseReleaseEvent(e);
}
