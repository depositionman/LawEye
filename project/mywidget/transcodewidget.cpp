#include "transcodewidget.h"

TranscodeWidget::TranscodeWidget(QWidget *parent)
    : BubbleButton(parent) // 继承 BubbleButton 而不是 QPushButton
{
    setText("视频转码");
    setGeometry(0, 0, 120, 60); // 设置按钮大小
    startBubbleAnimation(); // 启动气泡动画
}

void TranscodeWidget::mouseReleaseEvent(QMouseEvent *e)
{
    emit openTranscodeWin();

    // 调用父类的 mouseReleaseEvent 以确保正常的按钮行为
    BubbleButton::mouseReleaseEvent(e);
}
