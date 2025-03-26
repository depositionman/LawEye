#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QPushButton>
#include "mywidget/bubblebutton.h"

class LoginWidget : public BubbleButton
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);  // 注意这里父类应该是 QWidget 而不是 QPushButton
protected:
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:
    void openLoginWin();

private:
    BubbleButton *bubbleButton;  // 使用组合而不是继承
};

#endif // LOGINWIDGET_H
