#include "BubbleButton.h"

BubbleButton::BubbleButton(QWidget *parent)
    : QPushButton(parent)
{
    // 创建定时器，用于定期触发气泡动画
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BubbleButton::startBubbleAnimation);
    timer->start(1000); // 每隔1秒启动一次动画
}

void BubbleButton::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event);
    QPainter painter(this);

    // 绘制发光效果
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(80, 200, 120, 150));
    painter.drawEllipse(QPoint(width() / 2, height() / 2), width() / 2, height() / 2);

    // 这里绘制气泡等效果
    for (const Bubble *bubble : bubbles) {
        painter.setBrush(QColor(255, 255, 255, 100)); // 气泡颜色
        painter.drawEllipse(bubble->geometry());
    }
}

void BubbleButton::startBubbleAnimation() {
    QRect bubbleRect(rand() % width(), rand() % height(), 10, 10); // 随机生成气泡位置和大小
    Bubble *bubble = new Bubble(bubbleRect);
    bubbles.append(bubble);

    QPropertyAnimation *animation = new QPropertyAnimation(bubble, "geometry");
    animation->setDuration(2000); // 动画持续时间
    animation->setStartValue(bubbleRect);
    animation->setEndValue(QRect(bubbleRect.x(), bubbleRect.y() - 50, 10, 10)); // 气泡向上移动
    connect(animation, &QPropertyAnimation::finished, [this, bubble]() {
        bubbles.removeOne(bubble); // 动画结束后移除气泡
        delete bubble;
        update();
    });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
