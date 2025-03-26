#ifndef PHOTOWIDGET_H
#define PHOTOWIDGET_H

#include <QPushButton>
#include "mywidget/bubblebutton.h"

class PhotoWidget : public BubbleButton
{
    Q_OBJECT
public:
    explicit PhotoWidget(QWidget *parent = nullptr);
protected:
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:
    void getPhoto();

private:
    BubbleButton *bubbleButton;  // 使用组合而不是继承
};

#endif
