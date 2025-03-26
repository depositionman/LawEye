#ifndef SHADOWLABEL_H
#define SHADOWLABEL_H

#include <QLabel>
#include <QPainter>

class ShadowLabel : public QLabel
{
    Q_OBJECT

public:
    // 使用 QLabel 的构造函数
    using QLabel::QLabel;

protected:
    // 重写 paintEvent 事件
    void paintEvent(QPaintEvent *event) override;
};

#endif // SHADOWLABEL_H
