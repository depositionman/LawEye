#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "view/graphicsitem.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView();
private:
    QGraphicsScene *scene_;
    GraphicsItem *police_item;
    GraphicsItem *thief_item;
signals:

public slots:
    void createSettingWin();
};

#endif // GRAPHICSVIEW_H
