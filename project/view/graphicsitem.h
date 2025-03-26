#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QString>
#include <QPixmap>
#include <QRectF>
#include <QPainter>

class GraphicsItem : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit GraphicsItem(QPixmap img, int status);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget);
    int status() const;
    void setStatus(int status);

private:
    QPixmap img_;
    int status_;
signals:
    void enterSettingWin();
public slots:
    void advance(int phase);
};

#endif // GRAPHICSITEM_H
