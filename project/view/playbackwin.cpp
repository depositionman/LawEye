#include "playbackwin.h"
#include "mywidget/shadowlabel.h"
#include <QPushButton>
#include <QProgressBar>
#include "controller/photocontroller.h"
#include <QMessageBox>
#include <QDateTime>
#include "controller/videocontroller.h"

PlayBackWin::PlayBackWin(QString videoPath, QString photoPath, QString equipmentNumber)
{
    value_ = 0;
    equipmentNumber_ = equipmentNumber;
    videoPath_ = videoPath;
    flag_ = 0;
    photoPath_ = photoPath;
    playVideoThread_ = nullptr;
    init_allWin();
}

PlayBackWin::~PlayBackWin()
{
    // 首先确保线程完成
    if(playVideoThread_ != nullptr){
        playVideoThread_->setStopFlag(true);
        playVideoThread_->wait();
        delete playVideoThread_;
        playVideoThread_ = nullptr;
    }
    delete factorBox_;
    factorBox_ = nullptr;
    delete playIcon_;
    playIcon_ = nullptr;
}

void PlayBackWin::init_allWin()
{
    this->setFixedSize(700,800);
    //为主窗口设置主布局管理器
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    //将主窗口分为四个部分
    QWidget *topWin = new QWidget;
    QWidget *playWin = new QWidget;
    QWidget *growin = new QWidget;
    QWidget *buttonWin = new QWidget;

    //将四个小窗口加入到布局中
    mainLayout->addWidget(topWin,3);
    mainLayout->addWidget(playWin,13);
    mainLayout->addWidget(growin,2);
    mainLayout->addWidget(buttonWin,4);

    //为四个小窗口设置相关的布局管理器
    QHBoxLayout *topLayout = new QHBoxLayout;
    QHBoxLayout *playLayout = new QHBoxLayout;
    QHBoxLayout *groLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    topWin->setLayout(topLayout);
    playWin->setLayout(playLayout);
    growin->setLayout(groLayout);
    buttonWin->setLayout(buttonLayout);

    //设计上层窗口
    QVBoxLayout *titleLayout = new QVBoxLayout;
    ShadowLabel *title = new ShadowLabel;
    title->setFixedSize(288,48);
    title->setText("录像回放界面");
    titleLayout->addStretch(1);
    titleLayout->addWidget(title);
    titleLayout->addStretch(1);

    QVBoxLayout *btnLayout = new QVBoxLayout;
    QPushButton *backHomeBtn = new QPushButton;
    backHomeBtn->setFixedSize(60,60);
    backHomeBtn->setIcon(QIcon(":/img/exit.png"));
    btnLayout->addStretch(1);
    btnLayout->addWidget(backHomeBtn);
    btnLayout->addStretch(5);
    connect(backHomeBtn, &QPushButton::clicked, this, &PlayBackWin::backLookVideoWin);

    topLayout->addStretch(4);
    topLayout->addLayout(titleLayout);
    topLayout->addStretch(2);
    topLayout->addLayout(btnLayout);

    //设计播放窗口
    video_ = new QLabel;
    video_->setFixedWidth(500);
    playLayout->addStretch(1);
    playLayout->addWidget(video_);
    playLayout->addStretch(1);
    playLayout->setMargin(0);
    playLayout->setSpacing(0);

    //进度条
    progressBar_ = new QProgressBar;
    progressBar_->setOrientation(Qt::Horizontal);  // 水平方向
    progressBar_->setMinimum(0);  // 最小值
    progressBar_->setValue(0);  // 当前进度
    progressBar_->setFixedSize(500,25);
    groLayout->addStretch(1);
    groLayout->addWidget(progressBar_);
    groLayout->addStretch(1);
    //获取视频的时间
    VideoController videoController;
    videoTime_ = videoController.queryVideoTimeByVideoPath(videoPath_);
    videoTime_.chop(1);
    double videoTime = videoTime_.toDouble();
    progressBar_->setMaximum(static_cast<int>(videoTime * 1000));  // 将时间转换为毫秒，int类型，避免精度的缺失


    //设计控件窗口
    //control窗口的布局
    QHBoxLayout *controlLayout = new QHBoxLayout;
    //control窗口
    QWidget *controlWindow = new QWidget;
//    controlWindow->setStyleSheet("background-color:black");
    //上一集Icon
    QPushButton *lastIcon = new QPushButton;
    lastIcon->setIcon(QIcon(":/img/lastIcon.png"));
    lastIcon->setFixedSize(70,70);  
    //下一集Icon
    QPushButton *nextIcon = new QPushButton;
    nextIcon->setIcon(QIcon(":/img/nextIcon.png"));
    nextIcon->setFixedSize(70,70); 
    //全屏Icon
    QLabel *allWinIcon = new QLabel;
    allWinIcon->setPixmap(QPixmap(":/img/allWinIcon.png"));
    allWinIcon->setFixedSize(70,70);
    //播放Icon
    playIcon_ = new PlayIcon();
    playIcon_->setPixmap(QPixmap(":/img/continueIcon.png"));
    playIcon_->setFixedSize(70,70);
    //倍数下拉框
    factorBox_ = new MyComBox;
    factorBox_->addItem(QString("0.5"));
    factorBox_->addItem(QString("1.0"));
    factorBox_->addItem(QString("1.5"));
    factorBox_->addItem(QString("2.0"));
    //设置默认倍数
    factorBox_->setCurrentIndex(1);
    factorBox_->setFixedSize(200,70);
    //截图控件
    QPushButton *screenshot = new QPushButton;
    screenshot->setFixedSize(48,48);
    screenshot->setIcon(QIcon(":/img/jietu.png"));
    //从左往右添加控件
    controlLayout->addWidget(lastIcon);
    controlLayout->addWidget(playIcon_);
    controlLayout->addWidget(nextIcon);
    controlLayout->addWidget(factorBox_);
    controlLayout->addWidget(allWinIcon);
    controlLayout->addWidget(screenshot);
    //布局设置
    controlLayout->setMargin(0);
    controlLayout->setSpacing(0);
    //添加布局和窗口
    controlWindow->setLayout(controlLayout);
    buttonLayout->addWidget(controlWindow);

    connect(lastIcon,&QPushButton::clicked,this,&PlayBackWin::lastVideo);
    connect(nextIcon,&QPushButton::clicked,this,&PlayBackWin::nextVideo);
    connect(screenshot,&QPushButton::clicked,this,&PlayBackWin::getImage);
    connect(this->playIcon_, SIGNAL(changeVideoStatus()), this, SLOT(playVideo()));
}

void PlayBackWin::changeProgressBar()
{
    double dProgress = (progressBar_->value() - progressBar_->minimum()) * 100.0
                    / (progressBar_->maximum() - progressBar_->minimum()); // 百分比计算公式
    progressBar_->setFormat(QString::fromLocal8Bit("当前进度为：%1%").arg(QString::number(dProgress, 'f', 1)));
    progressBar_->setFormat(tr("Current progress : %1%").arg(QString::number(dProgress, 'f', 1)));
    progressBar_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  // 对齐方式
}

void PlayBackWin::playVideo()
{
    if(flag_ == 0)//只构造一次
    {
        //开启线程播放视频
        playVideoThread_ = new PlayVideoThread(videoPath_);
        connect(this,&PlayBackWin::stopThread,playVideoThread_,&PlayVideoThread::stop);
        flag_ = 1;
    }
    if((playVideoThread_->getVideoStatus() == START && playVideoThread_->getFlag() == true) ||
            playVideoThread_->getVideoStatus() == CONTINUEPLAY)
    {
        playVideoThread_->setVideoStatus(PAUSE);
    }
    else if(playVideoThread_->getVideoStatus() == PAUSE)
    {
        playVideoThread_->setVideoStatus(CONTINUEPLAY);
    }
    switch(playVideoThread_->getVideoStatus())
    {
    case START://开始播放视频
    {
        connect(playVideoThread_, SIGNAL(sendImg(QImage)), this, SLOT(receiveImg(QImage)));
        playVideoThread_->start();
        //播放图标进行更新
        playIcon_->setPixmap(QPixmap(":/img/pauseIcon.png"));
    }
        break;
    case CONTINUEPLAY://继续播放视频
    {
        connect(playVideoThread_, SIGNAL(sendImg(QImage)), this, SLOT(receiveImg(QImage)));
        //播放图标进行更新
        playIcon_->setPixmap(QPixmap(":/img/pauseIcon.png"));
    }
        break;
    case PAUSE://暂停视频
    {
        //播放图标进行更新
        playIcon_->setPixmap(QPixmap(":/img/continueIcon.png"));
    }
        break;
    }
    //重新播放连接
    connect(this->playVideoThread_, SIGNAL(videoEnd()), this, SLOT(replay()));
}

void PlayBackWin::getImage()
{
    //将该帧的图片(videoImg_)存入文件夹中
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
    QMessageBox::information(this, "截图", "截图成功");
}

void PlayBackWin::lastVideo()
{
    emit stopThread();
    emit lastVideoSignal();
}

void PlayBackWin::nextVideo()
{
    emit stopThread();
    emit nextVideoSignal();
}

void PlayBackWin::receiveImg(QImage img)
{
//    qDebug() << factorBox->currentText().toDouble();
    //倍数播放
    playVideoThread_->setFactor(factorBox_->currentText().toDouble());
    videoImg_ = img;
    repaint();
    //更新进度条
    value_ += 40;
    progressBar_->setValue(value_);
    changeProgressBar();
}

void PlayBackWin::replay()
{
    //刷新进度条
    progressBar_->setValue(progressBar_->maximum());
    changeProgressBar();
    //相关标志位复位
    playVideoThread_->setVideoStatus(START);
    playVideoThread_->setFlag(false);
    playVideoThread_->setStopFlag(false);
    //播放图标进行更新
    playIcon_->setPixmap(QPixmap(":/img/continueIcon.png"));
    playVideoThread_->clearBuf();
}

void PlayBackWin::paintEvent(QPaintEvent *event)
{
    if(!videoImg_.isNull())
    {
        video_->setPixmap(QPixmap::fromImage(videoImg_).scaled(video_->size()));
    }
}

QString PlayBackWin::getVideoPath() const
{
    return videoPath_;
}

void PlayBackWin::setVideoPath(const QString &videoPath)
{
    videoPath_ = videoPath;
}


