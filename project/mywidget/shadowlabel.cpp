#include "shadowlabel.h"

void ShadowLabel::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font = this->font();
    font.setPointSize(24); // 确保使用设置的字体大小
    painter.setFont(font);

    // 绘制阴影
    painter.setPen(QColor(0, 0, 255, 127));  // 半透明蓝色阴影
    painter.drawText(rect().translated(2, 2), alignment(), text());

    // 绘制文本
    painter.setPen(QColor(30, 144, 255));  // 纯蓝色文字
    painter.drawText(rect(), alignment(), text());
}
