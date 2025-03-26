#include "view/loginwin.h"
#include <QIcon>        //图标
#include <QPalette>     //调色板
#include <QBrush>       //画刷
#include <QPixmap>      //背景图
#include <QRegExpValidator> //reg登录 exp预期 validator验证器
#include <QList>
#include <QString>
#include <QMessageBox>  //消息弹窗
#include <QFile>
#include <QDebug>   //qt的输入输出文件
#include <QTime>
#include "util/sqliteutil.h"
#include "myWidget/verify.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCryptographicHash> //md5加密库
#include "controller/policecontroller.h"

LoginWin::LoginWin(QWidget *parent)
    : QWidget(parent)
{
    this->init_window();
    this->init_control();
    this->init_connect();
    this->init_qss();
}

LoginWin::~LoginWin()
{
    delete this->usrLabel;
    delete this->pwdLabel;
    delete this->verLabel;
    delete this->usrEdit;
    delete this->pwdEdit;
    delete this->verEdit;
    delete this->exitBtn;
    delete this->loginBtn;
}

void LoginWin::init_window()
{
    //3.设置窗口大小fixed size
    this->setFixedSize(700,800);
    //4.添加背景图片
    QPixmap pixmap(":/img/background.jpg");
    QPalette palet(palette());
    palet.setBrush(QPalette::Background, QBrush(pixmap.scaled(this->size())));
    this->setPalette(palet);
}

void LoginWin::init_control()
{
//    this->reWin = new ReWidget;
    //初始化控件
    this->equipLabel = new QLabel("设备编号：",this);
    this->equipLabel->move(100,200);
    this->equipNumberLabel = new QLabel("",this);
    this->equipNumberLabel->move(250,200);
    //1.创建控件
    this->usrLabel = new QLabel("警员编号：", this);    //用户名标签
    //2.设置控件的位置--绝对位置
    this->usrLabel->move(100, 300);
    //3.设置控件的样式
    this->pwdLabel = new QLabel("密  码：", this);   //密码标签
    this->pwdLabel->move(100, 400);

    this->verLabel = new QLabel("验证码：", this);   //验证码标签
    this->verLabel->move(100, 500);

    this->usrEdit = new QLineEdit("", this);        //用户编辑框
    this->usrEdit->move(250, 300);
    this->usrEdit->setPlaceholderText("usr");       //设置占位符文本

    this->pwdEdit = new QLineEdit("", this);        //密码编辑框
    this->pwdEdit->move(250, 400);
    this->pwdEdit->setPlaceholderText("password");    //设置占位符文本
    this->pwdEdit->setEchoMode(QLineEdit::Password);         //设置回显的模式（明密文）

    this->eyesBtn = new QPushButton(this);
    this->eyesBtn->setFixedSize(50,50);
    this->eyesBtn->move(500,400);
    connect(eyesBtn,&QPushButton::clicked, this, &LoginWin::changeMode);
    eyesBtn->setText("*");

    this->verEdit = new QLineEdit("", this);        //验证码编辑框
    this->verEdit->move(250, 500);
    this->verEdit->setPlaceholderText("ver code");    //设置占位符文本

    this->loginBtn = new QPushButton("登录", this);
    this->loginBtn->move(150, 650);

    this->exitBtn = new QPushButton("退出", this);
    this->exitBtn->move(450, 650);

    this->verify = new Verify;
    this->verify->setParent(this);
    this->verify->move(500,490);
    this->verify->show();

    //进行输入框的条件限制
    //账号的限制：数字 长度6-12
    QRegExp regexp1("^[a-zA-Z0-9]{6,12}$");
    this->usrEdit->setValidator(new QRegExpValidator(regexp1));
    //密码的限制：字母+数字 长度6-8
    QRegExp regexp2("^[a-zA-Z0-9]{6,8}$");
    this->pwdEdit->setValidator(new QRegExpValidator(regexp2));
    //验证码的限制：字母+数字 长度6
    QRegExp regexp3("^[a-zA-Z0-9]{6}$");
    this->verEdit->setValidator(new QRegExpValidator(regexp3));
}

void LoginWin::init_connect()
{
    //发送信号者 发出的信号 接收信号者 接收到信号要做的事情
    //登录
    connect(this->loginBtn, SIGNAL(clicked(bool)), this, SLOT(doLogin()));
    //退出程序
    connect(this->exitBtn, SIGNAL(clicked(bool)), this, SLOT(closeLogin()));
}

void LoginWin::init_qss()
{
    QFile file(":/qss/login.qss");
    if(file.open(QFile::ReadOnly))
    {
        this->setStyleSheet(file.readAll());
//        qDebug()<<"文件打开成功";
        file.close();
    }
}

void LoginWin::allText_clear()
{
    this->usrEdit->setText("");
    this->pwdEdit->setText("");
    this->verEdit->setText("");
}

void LoginWin::closeLogin()
{
    this->close();
    emit backMainWin();
}

void LoginWin::receiveEquipmentNumber(QString equipmentNumber)
{
    equipNumberLabel->setText(equipmentNumber);
}

void LoginWin::changeMode()
{
    if (this->pwdEdit->echoMode() == QLineEdit::Password) {
        this->pwdEdit->setEchoMode(QLineEdit::Normal);
    } else {
        this->pwdEdit->setEchoMode(QLineEdit::Password);
    }
}

void LoginWin::doLogin()
{
    this->code = verify->getCode();
    //进行表单验证
    QString name = this->usrEdit->text();
    QString pwd = this->pwdEdit->text();
    QString ver = this->verEdit->text().trimmed();//trimmed()删除编辑框前后的空格
    //1.验证编辑框是否为空
    if(name.isEmpty() || pwd.isEmpty() || ver.isEmpty())
    {
        QMessageBox::warning(this, "登录窗口", "表单不能为空");
        return;
    }
    //2.验证验证码是否正确
    if(this->code.toLower() != ver.toLower())
    {
        verify->updateVer();
        QMessageBox::warning(this, "登录窗口", "验证码错误");
        verEdit->setText("");
        verify->updateVer();
        return;
    }
    //4.验证用户名长度是否符合
    if(name.length() < 6)
    {
        QMessageBox::warning(this, "登录窗口", "用户名不足6位");
        return;
    }
    //5.验证密码长度是否符合
    if(pwd.length() < 6)
    {
        QMessageBox::warning(this, "登录窗口", "密码不足6位");
        return;
    }
    //3.验证用户名，密码是否符合
    PoliceController policeController;
    QString MD5;
    QByteArray str;
    str = QCryptographicHash::hash(pwd.toLatin1(),QCryptographicHash::Md5);
    MD5.append(str.toHex());
    int res = policeController.loginService(name, MD5);
    if(res == NOTEXIST){
        QMessageBox::warning(this, "登录窗口", "警察信息错误登录失败");
        this->allText_clear();
        return;
    }
    else if(res == EXIST){
        this->allText_clear();
        QMessageBox::information(this, "登录窗口", "登录成功");
        emit backMainWinAfterlogin(name);
    }
}
