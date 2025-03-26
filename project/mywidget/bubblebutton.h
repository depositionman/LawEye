#ifndef BUBBLEBUTTON_H
#define BUBBLEBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <QRect>
#include <QObject>

class Bubble : public QObject {
    Q_OBJECT
    Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry)
public:
    Bubble(const QRect &rect) : m_geometry(rect) {}

    QRect geometry() const { return m_geometry; }
    void setGeometry(const QRect &geometry) { m_geometry = geometry; }

private:
    QRect m_geometry;
};

class BubbleButton : public QPushButton {
    Q_OBJECT

public:
    BubbleButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void startBubbleAnimation();

private:
    QList<Bubble*> bubbles; // 用于存储气泡的列表
};

#endif // BUBBLEBUTTON_H
