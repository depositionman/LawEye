#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "myWidget/verify.h"

class LoginWin : public QWidget
{
    Q_OBJECT

public:
    LoginWin(QWidget *parent = 0);
    ~LoginWin();
    void init_window();
    void init_control();
    void init_data();
    void init_connect();
    void init_qss();
    void allText_clear();
public slots: //公共的槽函数
    /**登录的槽函数
     * @brief doLogin
     */
    void doLogin();

    void closeLogin();

    void receiveEquipmentNumber(QString);
    void changeMode();//切换密码显示模式
private:
    //存放验证码信息
    QString code;
    //标签
    QLabel *usrLabel, *pwdLabel, *verLabel, *equipLabel, *equipNumberLabel;
    //编辑框
    QLineEdit *usrEdit, *pwdEdit, *verEdit;
    //按钮
    QPushButton *exitBtn, *loginBtn, *eyesBtn;
    //验证码
    Verify *verify;
signals:
    void backMainWin();
    void backMainWinAfterlogin(QString);
};

#endif // LOGINWIDGET_H
