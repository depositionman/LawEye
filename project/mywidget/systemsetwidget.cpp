#include "systemsetwidget.h"

SystemSetWidget::SystemSetWidget(QWidget *parent)
    : BubbleButton(parent) // 继承 BubbleButton 而不是 QPushButton
{
    setText("系统设置");
    setGeometry(0, 0, 100, 60); // 设置按钮大小
    startBubbleAnimation(); // 启动气泡动画
}

void SystemSetWidget::mouseReleaseEvent(QMouseEvent *e)
{
    emit openSetWin();

    // 调用父类的 mouseReleaseEvent 以确保正常的按钮行为
    BubbleButton::mouseReleaseEvent(e);
}
