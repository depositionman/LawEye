#include "graphicsitem.h"
#include <QTimer>
#include <QDebug>

GraphicsItem::GraphicsItem(QPixmap img, int status)
{
    //初始化成员变量
    this->img_ = img;
    this->status_ = status;
}

QRectF GraphicsItem::boundingRect() const
{
    return QRectF(0,0,this->img_.width(), this->img_.height());
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, this->img_);
}

void GraphicsItem::advance(int phase)
{
    if(this->status_ == 0){//小偷
        this->setPos(this->mapToScene(-1,0));
    }
    else if(this->status_ == 1){//警察
        this->setPos(this->mapToScene(-3,0));
    }
    else if(this->status_ == 2){//警察抓到了小偷
        this->setPos(this->mapToScene(2,0));
    }
    if(collidingItems().count() > 0){//碰撞检测
        static int count = 0;
        ++count;
        if(count >= 140 && count < 340){
            this->status_ = 2;
        }
        else if(count > 340){
            this->status_ = 3;//带上警车
            emit enterSettingWin();
        }
    }
}
