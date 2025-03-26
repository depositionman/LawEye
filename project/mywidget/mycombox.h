#ifndef MYCOMBOX_H
#define MYCOMBOX_H

#include <QObject>
#include <QWidget>
#include <QComboBox>

class MyComBox : public QComboBox
{
    Q_OBJECT
public:
    explicit MyComBox(QWidget *parent = nullptr);
protected:
    void showPopup() override;
};

#endif // MYCOMBOX_H
