#include "mycombox.h"

MyComBox::MyComBox(QWidget *parent)
    : QComboBox(parent)
{

}

void MyComBox::showPopup()
{
    QComboBox::showPopup();  // 调用基类的 showPopup 方法

    QWidget *popup = this->findChild<QFrame*>();  // 查找弹出窗口
    if (popup)  // 确保popup找到后再移动
    {
        popup->move(popup->x(), popup->y() - this->height() - popup->height());  // 向上移动
    }
}
