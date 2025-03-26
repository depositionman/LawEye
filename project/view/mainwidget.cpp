#include "mainwidget.h"
#include "mywidget/closewidget.h"
#include "thread/videothread.h"
#include <QPixmap>
#include "mywidget/loginwidget.h"
#include <QFile>
#include "util/simpleQtLogger.h"
#include "mywidget/systemsetwidget.h"
#include "mywidget/transcodewidget.h"
#include "mywidget/photowidget.h"
#include "mywidget/videoreplaywidget.h"
#include "mywidget/localphotowidget.h"
#include "mywidget/checklogwidget.h"
#include <QDebug>
#include <QLabel>
#include <QFont>
#include "view/loginwin.h"
#include "view/systemsettingswin.h"
#include "thread/playbackthread.h"
#include "controller/photocontroller.h"
#include <QDateTime>
#include <QMessageBox>
#include "view/lookvideowin.h"
#include "view/viewlogwin.h"
#include "view/transcodingwin.h"
#include <QCamera>
#include <QCameraInfo>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    transcodingWin_ = nullptr;
    viewLogWin_ = ViewLogWin::getViewLogWin();
    viewLogWin_->setEquipmentNumber(equipmentNumber_);
    viewLogWin_->setPoliceNumber(policeNumber_);
    connect(this,&MainWidget::occurOperation,viewLogWin_,&ViewLogWin::printStatus);
    connect(viewLogWin_,&ViewLogWin::backMainWin,this,&MainWidget::ViewLogwinbackMainWin);
    init_allWin();
}

MainWidget::~MainWidget()
{
    delete loginWidget_;
    loginWidget_ = nullptr;
    delete loginwin_;
    loginwin_ = nullptr;
    delete videoQueue_;
    videoQueue_ = nullptr;
    delete videoThread_;
    videoThread_ = nullptr;
    delete lookPhotoWin_;
    lookPhotoWin_ = nullptr;
    delete lookVideoWin_;
    lookVideoWin_ = nullptr;
    delete viewLogWin_;
    viewLogWin_ = nullptr;
    delete transcodingWin_;
    transcodingWin_ = nullptr;
    delete playBackThread_;
    playBackThread_ = nullptr;
}

void MainWidget::init_allWin()
{
    //设置主窗口的大小
    this->setFixedSize(700,800);
    //为主布局分配空间，并将窗口添加到布局中
    mainLayout_ = new QVBoxLayout;
    //创建三个小窗口
    navWidget_ = new QWidget;
//    navWidget_->setStyleSheet("background:red");
    videoWidget_ = new QWidget;
//    videoWidget_->setStyleSheet("background:black");
    functionWidget_ = new QWidget;
//    functionWidget_->setStyleSheet("background:yellow");
    //初始化三个小窗口
    init_navWin();
    init_videoWin();
    init_functionWin();
    //将窗口添加到布局中
    mainLayout_->addWidget(navWidget_,1);
//    mainLayout_->addStretch(1);
    mainLayout_->addWidget(videoWidget_,6);
//    mainLayout_->addStretch(3);
    mainLayout_->addWidget(functionWidget_,4);
    //设置布局的格式
    mainLayout_->setMargin(0);
    mainLayout_->setSpacing(0);
    //添加主布局
    this->setLayout(mainLayout_);
}

void MainWidget::init_navWin()
{
    //创建布局
    QHBoxLayout *navLayout = new QHBoxLayout;
    //创建关闭控件并设置对应的格式
    CloseWidget *closeWidget = new CloseWidget;
    closeWidget->setText("X"); // 设置按钮上的文本为 "X"
    QFile file(":/qss/closeWidget.qss");
    if(file.open(QIODevice::ReadOnly)){
        closeWidget->setStyleSheet(file.readAll());
//        LS_INFO(":/qss/closeWidget.qss is open success");
        file.close();
    }
    //关闭控件创建连接 实现关闭功能
    connect(closeWidget, SIGNAL(closeMainWin()), this, SLOT(closeWin()));
    //大标题
    QLabel *title = new QLabel;
    title->setText("执法记录仪");
    QFont font;
    font.setPointSize(28); // 确保使用设置的字体大小
    title->setFont(font);
    title->setFixedSize(300,200);
    //创建两个垂直布局管理器
    QVBoxLayout *titleLayout = new QVBoxLayout;
    QVBoxLayout *widgetLayout = new QVBoxLayout;
    //将控件添加到对应的布局管理器中
    titleLayout->addStretch(6);
    titleLayout->addWidget(title);
    titleLayout->addStretch(1);
    widgetLayout->addStretch(1);
    widgetLayout->addWidget(closeWidget);
    widgetLayout->addStretch(3);
    //将两个垂直布局管理器放入总布局管理器中
    navLayout->addStretch(7);
    navLayout->addLayout(titleLayout);
    navLayout->addStretch(3);
    navLayout->addLayout(widgetLayout);
    navLayout->addStretch(1);
    //设置布局的格式
    navLayout->setMargin(0);
    navLayout->setSpacing(0);
    //添加布局
    navWidget_->setLayout(navLayout);
}

void MainWidget::init_videoWin()
{
    //创建布局
    QHBoxLayout *videoLayout = new QHBoxLayout;
    QVBoxLayout *lastLayout = new QVBoxLayout;
    //设置布局格式
    videoLayout->setMargin(0);
    videoLayout->setSpacing(0);
    //将控件添加到布局中
    videoLayout->addStretch(1);
    videoLayout->addWidget(&video_);
    videoLayout->addStretch(1);
    //将水平布局添加到垂直布局中去调整窗口的竖直位置
    lastLayout->addStretch(1);
    lastLayout->addLayout(videoLayout);
    lastLayout->addStretch(1);
    //窗口添加布局
    videoWidget_->setLayout(lastLayout);
    //播放线程
    videoQueue_ = new VideoQueue;
    QString cameraName = "";
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    cameraName = cameras.at(0).description();
    videoThread_ = new VideoThread(videoQueue_,cameraName);
    videoThread_->start();
    connect(videoThread_, SIGNAL(sendImg(QImage)), this, SLOT(receiveImg(QImage)));
}

void MainWidget::init_functionWin()
{
    //创建主布局
    QVBoxLayout *functionLayout = new QVBoxLayout;
    //将布局分为三分
    QHBoxLayout *topLayout = new QHBoxLayout;
    QHBoxLayout *midLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QWidget *topWin = new QWidget;
    QWidget *midWin = new QWidget;
    QWidget *buttonWin = new QWidget;
    //将三个布局添加到对应的窗口中
    topWin->setLayout(topLayout);
    midWin->setLayout(midLayout);
    buttonWin->setLayout(buttonLayout);
    //将三个窗口放入主布局中
    functionLayout->addWidget(topWin,1);
    functionLayout->addWidget(midWin,1);
    functionLayout->addWidget(buttonWin,1);
    //窗口添加主布局
    functionWidget_->setLayout(functionLayout);
    //上层窗口的控件
    //创建拍照控件
    PhotoWidget *photoWidget = new PhotoWidget;
    photoWidget->setFixedSize(120,60);
    connect(photoWidget, SIGNAL(getPhoto()), this, SLOT(takePicture()));
    //录像回放控件
    VideoReplayWidget *videoReplayWidget = new VideoReplayWidget;
    videoReplayWidget->setFixedSize(120,60);
    connect(videoReplayWidget, SIGNAL(doReplay()), this, SLOT(createVideoReplayWin()));
    //现场照片控件
    LocalPhotoWidget *localPhotoWidget = new LocalPhotoWidget;
    localPhotoWidget->setFixedSize(120,60);
    connect(localPhotoWidget, SIGNAL(lookPhoto()), this, SLOT(createFindPhotoWin()));
    //按照从左向右的顺序添加控件
    topLayout->addWidget(photoWidget);
    topLayout->addWidget(videoReplayWidget);
    topLayout->addWidget(localPhotoWidget);

    //中层窗口的控件
    //查看日志控件
    CheckLogWidget *checkLogWidget = new CheckLogWidget;
    checkLogWidget->setFixedSize(150,60);
    connect(checkLogWidget, SIGNAL(checkLog()), this, SLOT(createCheckLogWin()));
    //按照从左向右的顺序添加控件
    midLayout->addWidget(checkLogWidget);

    //下层窗口的控件
    //创建登录控件
    loginWidget_ = new LoginWidget;
    loginWidget_->setFixedSize(120,60);
    connect(loginWidget_, SIGNAL(openLoginWin()), this, SLOT(createLoginWin()));
    connect(this,&MainWidget::openLoginWin,loginWidget_,&LoginWidget::openLoginWin);
    //创建系统设置控件
    SystemSetWidget *setWidget = new SystemSetWidget;
    setWidget->setFixedSize(120,60);
    connect(setWidget, SIGNAL(openSetWin()), this, SLOT(createSetWin()));
    //录像转码控件
    TranscodeWidget *transcodeWidget = new TranscodeWidget;
    transcodeWidget->setFixedSize(120,60);
    connect(transcodeWidget, SIGNAL(openTranscodeWin()), this, SLOT(createTranscodeWin()));
    //按照从左向右的顺序添加控件
    buttonLayout->addWidget(transcodeWidget);
    buttonLayout->addWidget(setWidget);
    buttonLayout->addWidget(loginWidget_);

    //设置主窗口按钮的样式
    QFile file(":/qss/mainBtn.qss");
    if(file.open(QIODevice::ReadOnly)){
        checkLogWidget->setStyleSheet(file.readAll());
        file.seek(0);
        localPhotoWidget->setStyleSheet(file.readAll());
        file.seek(0);
        photoWidget->setStyleSheet(file.readAll());
        file.seek(0);
        videoReplayWidget->setStyleSheet(file.readAll());
        file.seek(0);
        transcodeWidget->setStyleSheet(file.readAll());
        file.seek(0);
        setWidget->setStyleSheet(file.readAll());
        file.seek(0);
        loginWidget_->setStyleSheet(file.readAll());
//        LS_INFO(":/qss/mainBtn.qss is open success");
        file.close();
    }
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    if(!videoImg_.isNull()){
        video_.setPixmap(QPixmap::fromImage(videoImg_).scaled(500,500));
    }
}

void MainWidget::receiveImg(QImage img)
{
    videoImg_ = img;
    update();
}

void MainWidget::createLoginWin()
{
    this->hide();
    loginwin_ = new LoginWin;
    connect(this , &MainWidget::sendEquipmentNumber, loginwin_, &LoginWin::receiveEquipmentNumber);
    connect(loginwin_, &LoginWin::backMainWin, this, &MainWidget::backMainWin);
    connect(loginwin_, &LoginWin::backMainWinAfterlogin, this, &MainWidget::backMainWinAfterlogin);
    emit sendEquipmentNumber(equipmentNumber_);
    loginwin_->show();
}

void MainWidget::createSetWin()
{
    emit backSetWin();
    emit occurOperation("设置路径");
}

void MainWidget::createTranscodeWin()
{
    if(loginWidget_->text() == "已登录"){
        this->hide();
        if(transcodingWin_ != nullptr){
            delete transcodingWin_;
            transcodingWin_ = nullptr;
        }
        transcodingWin_ = new TranscodingWin;
        connect(transcodingWin_,&TranscodingWin::backMainWin,this,&MainWidget::TrancewinbackMainWin);
        transcodingWin_->show();
        viewLogWin_->setPoliceNumber(policeNumber_);
        emit occurOperation("视频转码");
    }
    else{
        QMessageBox::warning(this,"警告","请先登录");
        emit openLoginWin();
    }
//    qDebug() << "视频转码窗口";
//    this->hide();
//    transcodingWin_ = new TranscodingWin;
//    connect(transcodingWin_,&TranscodingWin::backMainWin,this,&MainWidget::TrancewinbackMainWin);
//    transcodingWin_->show();
}

void MainWidget::takePicture()
{
    if(loginWidget_->text() == "已登录"){
        //拍照
        PhotoController photoController;
        // 获取当前日期和时间
        QDateTime currentDateTime = QDateTime::currentDateTime();
        // 将日期和时间格式化为字符串
        QString formattedDateTimeName = currentDateTime.toString("yyyy-MM-dd_HH-mm-ss");
        QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");
        //将图片存入文件中
        QString imgPath = photoPath_ + "/" + formattedDateTimeName + ".png";
        videoImg_.save(imgPath);
        //将图片信息同步到数据库中
        photoController.appendPhotoInfo(formattedDateTimeName, imgPath, formattedDateTime, equipmentNumber_);
        QMessageBox::information(this, "拍照", "拍照成功");
        viewLogWin_->setPoliceNumber(policeNumber_);
        emit occurOperation("拍照");    
    }
    else{
        QMessageBox::warning(this,"警告","请先登录");
        emit openLoginWin();
    }
}

void MainWidget::createVideoReplayWin()
{
    if(loginWidget_->text() == "已登录"){
    //    qDebug() << "视频回放";
        this->hide();
        //查看视频回放
        lookVideoWin_ = new LookVideoWin(photoPath_,equipmentNumber_);
        connect(lookVideoWin_, &LookVideoWin::backMainWin, this, &MainWidget::LookVideoWinbackMainWin);
        lookVideoWin_->show();
        viewLogWin_->setPoliceNumber(policeNumber_);
        emit occurOperation("查看视频");
    }
    else{
        QMessageBox::warning(this,"警告","请先登录");
        emit openLoginWin();
    }
//    this->hide();
//    //查看视频回放
//    lookVideoWin_ = new LookVideoWin(photoPath_,equipmentNumber_);
//    connect(lookVideoWin_, &LookVideoWin::backMainWin, this, &MainWidget::LookVideoWinbackMainWin);
//    lookVideoWin_->show();
//    viewLogWin_->setPoliceNumber(policeNumber_);
//    emit occurOperation("查看视频");
}

void MainWidget::createFindPhotoWin()
{
    if(loginWidget_->text() == "已登录"){
        this->hide();
        //查看现场照片
        lookPhotoWin_ = new LookPhotoWin;
        connect(lookPhotoWin_, &LookPhotoWin::backMainWin, this, &MainWidget::LookPhotoWinbackMainWin);
        lookPhotoWin_->show();
        viewLogWin_->setPoliceNumber(policeNumber_);
        emit occurOperation("查看照片");
    }
    else{
        QMessageBox::warning(this,"警告","请先登录");
        emit openLoginWin();
    }
}

void MainWidget::createCheckLogWin()
{
    if(loginWidget_->text() == "已登录"){
//        qDebug() << "查看日志";
        this->hide();
        viewLogWin_->show();
    }
    else{
        QMessageBox::warning(this,"警告","请先登录");
        emit openLoginWin();
    }
//    this->hide();
//    viewLogWin_->show();
}

void MainWidget::receiveEquipmentNumber(QString equipmentNumber)
{
    equipmentNumber_ = equipmentNumber;
    viewLogWin_->setEquipmentNumber(equipmentNumber);
}

void MainWidget::backMainWin()
{
    loginwin_->close();
    delete loginwin_;
    loginwin_ = nullptr;
    this->show();
}

void MainWidget::backMainWinAfterlogin(QString policeNumber)
{
    policeNumber_ = policeNumber;
    loginwin_->close();
    delete loginwin_;
    loginwin_ = nullptr;
    this->show();
    loginWidget_->setText("已登录");
    videoThread_->setFlag(true);
    viewLogWin_->setPoliceNumber(policeNumber_);
    emit occurOperation("登录");
    //开启存储视频的线程
    QString savePath = videoPath_;
    playBackThread_ = new PlayBackThread(videoQueue_, savePath, policeNumber);
    playBackThread_->start();
    connect(playBackThread_, &PlayBackThread::saveFirstPhoto, this ,&MainWidget::saveFirstPhoto);
    connect(this, &MainWidget::sendFirstPhotoPath, playBackThread_, &PlayBackThread::receiveFirstPhotoPath);
    connect(this ,&MainWidget::saveDate, playBackThread_, &PlayBackThread::saveDate);
}

void MainWidget::receiveVideoPath(QString videoPath)
{
    videoPath_ = videoPath;
}

void MainWidget::receivePhotoPath(QString photoPath)
{
    photoPath_ = photoPath;
}

void MainWidget::LookPhotoWinbackMainWin()
{  
    lookPhotoWin_->close();
    delete lookPhotoWin_;
    lookPhotoWin_ = nullptr;
    this->show();
}

void MainWidget::saveFirstPhoto()
{
    // 获取当前日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    // 将日期和时间格式化为字符串
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd_HH-mm-ss");
    QString firstPhotoPath = videoPath_ + "/videoImg/" + formattedDateTime + ".png";
    if(!videoImg_.isNull()){
        videoImg_.save(firstPhotoPath);
    }
    emit sendFirstPhotoPath(firstPhotoPath);
}

void MainWidget::closeWin()
{
    emit saveDate();
    if(playBackThread_->saveFlag() == false){
        NoticeLabel *m_noticeLable_ = new NoticeLabel(this);
        m_noticeLable_->setNoticeType(NoticeType::TEXT_BACKGROUND);
        m_noticeLable_->setTextColor(QColor(0,0,255));
        m_noticeLable_->setBackgroundColor(QColor(255,255,255));
        m_noticeLable_->Notice(this,QString("还在存储视频文件请稍后！"));
    }
    while(playBackThread_->saveFlag() == false);
    this->close();
}

void MainWidget::LookVideoWinbackMainWin()
{
    lookVideoWin_->close();
    delete lookVideoWin_;
    lookVideoWin_ = nullptr;
    this->show();
}

void MainWidget::ViewLogwinbackMainWin()
{
    viewLogWin_->close();
    delete viewLogWin_;
    viewLogWin_ = nullptr;
    this->show();
}

void MainWidget::TrancewinbackMainWin()
{
    transcodingWin_->close();
    delete transcodingWin_;
    transcodingWin_ = nullptr;
    this->show();
}
