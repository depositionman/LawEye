#include "lookvideowin.h"
#include "mywidget/shadowlabel.h"
#include "controller/videocontroller.h"
#include "data/showvideo.h"
#include "view/playbackwin.h"
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>

LookVideoWin::LookVideoWin(QString photoPath,QString equipmentNumber)
{
    equipmentNumber_ = equipmentNumber;
    photoPath_ = photoPath;
    startRow_ = 0;
    listWidget_ = new QListWidget(this);
    playBackWin_ = nullptr;
    init_allWin();
}

void LookVideoWin::init_allWin()
{
    this->setFixedSize(700,800);
    //为整体界面设置布局管理器
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    //划分为三个区域
    QWidget *topWin = new QWidget(this);
    QWidget *middleWin = new QWidget(this);
    QWidget *buttonWin = new QWidget(this);
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    QGridLayout *middleLayout = new QGridLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(this);
    topWin->setLayout(topLayout);
    middleWin->setLayout(middleLayout);
    buttonWin->setLayout(buttonLayout);
    //将三个窗口加入主布局中
    mainLayout->addWidget(topWin,3);
    mainLayout->addWidget(middleWin,7);
    mainLayout->addWidget(buttonWin,2);
    //分别为这三个窗口设置布局管理器
    //1.top的布局设置
    //1.1初始化所有控件
    ShadowLabel *title = new ShadowLabel(this);
    title->setText("录像选择界面");
    title->setFixedSize(288,48);

    QPushButton *backBtn = new QPushButton(this);
    backBtn->setIcon(QIcon(":/img/exit.png"));
    connect(backBtn, &QPushButton::clicked, this, &LookVideoWin::backMainWin);

    QLabel *dateLabel = new QLabel(this);
    dateLabel->setText("请选择日期");
    dateLabel->setFixedSize(170,40);
    dateLabel->setStyleSheet("font-size: 30px");
    QDateEdit *dateEdit = new QDateEdit(this);
    dateEdit->setFixedSize(160,40);
    // 设置弹出日历
    dateEdit->setCalendarPopup(true);
    // 设置当前日期为默认日期
    dateEdit->setDate(QDate::currentDate());
    // 设置日期范围
    dateEdit->setMinimumDate(QDate(2024, 8, 21));
    dateEdit->setMaximumDate(QDate(2099, 12, 31));
    // 设置日期格式
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    connect(dateEdit, &QDateEdit::dateTimeChanged, this ,&LookVideoWin::changeVideoByTime);
    //1.2开始布局控件
    QHBoxLayout *backBtnLayout = new QHBoxLayout(this);
    backBtnLayout->addStretch(50);
    backBtnLayout->addWidget(backBtn);
    backBtnLayout->addStretch(1);
    backBtnLayout->setSpacing(0);
    backBtnLayout->setMargin(0);
    topLayout->addLayout(backBtnLayout,1);

    QHBoxLayout *titleLayout = new QHBoxLayout(this);
    titleLayout->addStretch(1);
    titleLayout->addWidget(title);
    titleLayout->addStretch(1);
    titleLayout->setSpacing(0);
    titleLayout->setMargin(0);
    topLayout->addLayout(titleLayout,3);

    topLayout->addStretch(1);

    QHBoxLayout *dateLayout = new QHBoxLayout(this);
    dateLayout->addStretch(1);
    dateLayout->addWidget(dateLabel);
    dateLayout->addWidget(dateEdit);
    dateLayout->addStretch(1);
    dateLayout->setSpacing(0);
    dateLayout->setMargin(0);
    topLayout->addLayout(dateLayout,1);

    topLayout->addStretch(1);

    //2.middle的布局设置
    //分页查询，从数据库中获取录像的信息添加到链表中
    VideoController videoController;
    QList<Video> videoList = videoController.pageQueryVideoInfo(4,startRow_);
    QList<Video>::iterator it_video;
    //将对应的照片加载到ShowPicture的链表中
    QList<ShowVideo> showVideoList;
    QList<ShowVideo>::iterator it_show;
    for(it_video = videoList.begin(); it_video != videoList.end(); ++it_video)
    {
        showVideoList.append(ShowVideo((*it_video).firstPhotoPath(), (*it_video).path(), (*it_video).name()));
    }
    //然后将imageList中的图片一个一个取出放入QListWidget中
    //设置为图标模式
    listWidget_->setViewMode(QListView::IconMode);
    listWidget_->setIconSize(QSize(250,250));
    //根据窗口大小自适应布局
    listWidget_->setResizeMode(QListView::Adjust);
    //图标间距
    listWidget_->setSpacing(30);
    //防止图标被拖动
    listWidget_->setMovement(QListView::Static);
    for(it_show = showVideoList.begin(); it_show != showVideoList.end(); ++it_show)
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).firstPhotoPath()), (*it_show).Name());
        item->setData(Qt::UserRole, (*it_show).Path());
        listWidget_->addItem(item);
    }
    middleLayout->addWidget(listWidget_);

    //3.button的布局设计
    QPushButton *upBtn = new QPushButton(this);
    upBtn->setText("上一页");
    upBtn->setFixedSize(100,50);
    connect(upBtn, &QPushButton::clicked, this, &LookVideoWin::upPage);
    QPushButton *downBtn = new QPushButton;
    downBtn->setText("下一页");
    downBtn->setFixedSize(100,50);
    connect(downBtn, &QPushButton::clicked, this, &LookVideoWin::downPage);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(upBtn);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(downBtn);
    buttonLayout->addStretch(1);

    //双击播放视频
    connect(listWidget_, &QListWidget::doubleClicked, this, &LookVideoWin::playVideo);
}

void LookVideoWin::checkVideo()
{

}

void LookVideoWin::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("关闭提示框");
    msgBox.setInformativeText("是否要回到主界面");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    int ret = msgBox.exec(); // 显示消息框并等待用户响应

    if (ret == QMessageBox::Yes) {
        // 用户选择“是”，允许窗口关闭
        emit backMainWin();
        event->accept();
    } else {
        // 用户选择“否”，阻止窗口关闭
        event->ignore();
    }
}

void LookVideoWin::upPage()
{
    if(startRow_ > 0){
        startRow_ -= 4;
    }
    if(findFlag_ == 0){
        VideoController videoController;
        QList<Video> videoList = videoController.pageQueryVideoInfo(4,startRow_);
        QList<Video>::iterator it_video;
        //将对应的照片加载到ShowPicture的链表中
        QList<ShowVideo> showVideoList;
        QList<ShowVideo>::iterator it_show;
        for(it_video = videoList.begin(); it_video != videoList.end(); ++it_video)
        {
            showVideoList.append(ShowVideo((*it_video).firstPhotoPath(), (*it_video).path(), (*it_video).name()));
        }
        listWidget_->clear();
        for(it_show = showVideoList.begin(); it_show != showVideoList.end(); ++it_show)
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).firstPhotoPath()), (*it_show).Name());
            item->setData(Qt::UserRole, (*it_show).Path());
            listWidget_->addItem(item);
        }
    }
    else{
        VideoController videoController;
        QList<Video> videoList = videoController.queryTimeWithinFourVideo(startTimeString_, endTimeString_, 4,startRow_);
        QList<Video>::iterator it_video;
        //将对应的照片加载到ShowPicture的链表中
        QList<ShowVideo> showVideoList;
        QList<ShowVideo>::iterator it_show;
        for(it_video = videoList.begin(); it_video != videoList.end(); ++it_video)
        {
            showVideoList.append(ShowVideo((*it_video).firstPhotoPath(), (*it_video).path(), (*it_video).name()));
        }
        listWidget_->clear();
        for(it_show = showVideoList.begin(); it_show != showVideoList.end(); ++it_show)
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).firstPhotoPath()), (*it_show).Name());
            item->setData(Qt::UserRole, (*it_show).Path());
            listWidget_->addItem(item);
        }
    }

}

void LookVideoWin::downPage()
{
    VideoController videoController;
    if(startRow_ < videoController.queryVideoCount()){
        startRow_ += 4;
        if(startRow_ > videoController.queryVideoCount()){//判断位置加加后是否超出了范围
            startRow_ -= 4;
        }
    }
    if(findFlag_ == 0){
        VideoController videoController;
        QList<Video> videoList = videoController.pageQueryVideoInfo(4,startRow_);
        QList<Video>::iterator it_video;
        //将对应的照片加载到ShowPicture的链表中
        QList<ShowVideo> showVideoList;
        QList<ShowVideo>::iterator it_show;
        for(it_video = videoList.begin(); it_video != videoList.end(); ++it_video)
        {
            showVideoList.append(ShowVideo((*it_video).firstPhotoPath(), (*it_video).path(), (*it_video).name()));
        }
        listWidget_->clear();
        for(it_show = showVideoList.begin(); it_show != showVideoList.end(); ++it_show)
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).firstPhotoPath()), (*it_show).Name());
            item->setData(Qt::UserRole, (*it_show).Path());
            listWidget_->addItem(item);
        }
    }
    else{
        VideoController videoController;
        QList<Video> videoList = videoController.queryTimeWithinFourVideo(startTimeString_, endTimeString_, 4,startRow_);
        QList<Video>::iterator it_video;
        //将对应的照片加载到ShowPicture的链表中
        QList<ShowVideo> showVideoList;
        QList<ShowVideo>::iterator it_show;
        for(it_video = videoList.begin(); it_video != videoList.end(); ++it_video)
        {
            showVideoList.append(ShowVideo((*it_video).firstPhotoPath(), (*it_video).path(), (*it_video).name()));
        }
        listWidget_->clear();
        for(it_show = showVideoList.begin(); it_show != showVideoList.end(); ++it_show)
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).firstPhotoPath()), (*it_show).Name());
            item->setData(Qt::UserRole, (*it_show).Path());
            listWidget_->addItem(item);
        }
    }
}

void LookVideoWin::playVideo(const QModelIndex &index)
{
    index_ = index.row();
    QListWidgetItem *item = listWidget_->item(index_);
    QString videoPath = item->data(Qt::UserRole).toString();
    this->hide();
    if(playBackWin_ != nullptr){
        delete playBackWin_;
        playBackWin_ = nullptr;
    }
    playBackWin_ = new PlayBackWin(videoPath,photoPath_,equipmentNumber_);
    playBackWin_->show();
    connect(playBackWin_, &PlayBackWin::backLookVideoWin, this, &LookVideoWin::backLookVideoWin);
    connect(playBackWin_, &PlayBackWin::lastVideoSignal, this, &LookVideoWin::sendLastVideoPath);
    connect(playBackWin_, &PlayBackWin::nextVideoSignal, this, &LookVideoWin::sendNextVideoPath);
}

void LookVideoWin::changeVideoByTime(QDateTime datetime)
{
    startRow_ = 0;
    findFlag_ = 1;//进入查询模式
    startTimeString_ = datetime.toString("yyyy-MM-dd HH:mm:ss");
//    qDebug() << startTimeString_;
    QDateTime nextDay = datetime.addDays(1);
    endTimeString_ = nextDay.toString("yyyy-MM-dd HH:mm:ss");
//    qDebug() << endTimeString_;
    VideoController videoController;
    QList<Video> videoList = videoController.queryTimeWithinFourVideo(startTimeString_, endTimeString_, 4,startRow_);
    if(videoList.size() != 0){
        QList<Video>::iterator it_video;
        //将对应的照片加载到ShowPicture的链表中
        QList<ShowVideo> showVideoList;
        QList<ShowVideo>::iterator it_show;
        for(it_video = videoList.begin(); it_video != videoList.end(); ++it_video)
        {
            showVideoList.append(ShowVideo((*it_video).firstPhotoPath(), (*it_video).path(), (*it_video).name()));
        }
        listWidget_->clear();
        for(it_show = showVideoList.begin(); it_show != showVideoList.end(); ++it_show)
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).firstPhotoPath()), (*it_show).Name());
            item->setData(Qt::UserRole, (*it_show).Path());
            listWidget_->addItem(item);
        }
    }
    else{
        QMessageBox::information(this,"提示","该日期内没有视频");
    }
}

void LookVideoWin::backLookVideoWin()
{
    playBackWin_->close();
    delete playBackWin_;
    playBackWin_ = nullptr;
    this->show();
}

void LookVideoWin::sendLastVideoPath()
{
    if(index_ > 0){
        --index_;
        QListWidgetItem *item = listWidget_->item(index_);
        QString videoPath = item->data(Qt::UserRole).toString();
        delete playBackWin_;
        playBackWin_ = nullptr;
        playBackWin_ = new PlayBackWin(videoPath,photoPath_,equipmentNumber_);
        playBackWin_->show();
        connect(playBackWin_, &PlayBackWin::backLookVideoWin, this, &LookVideoWin::backLookVideoWin);
        connect(playBackWin_, &PlayBackWin::lastVideoSignal, this, &LookVideoWin::sendLastVideoPath);
        connect(playBackWin_, &PlayBackWin::nextVideoSignal, this, &LookVideoWin::sendNextVideoPath);
    }
    else{
        QMessageBox::warning(playBackWin_,"警告","已经是这一页第一个视频了");
    }
}

void LookVideoWin::sendNextVideoPath()
{
    VideoController videoController;
    if(index_ < 3 && index_ <= videoController.queryVideoCount())
    {
        ++index_;
        QListWidgetItem *item = listWidget_->item(index_);
        QString videoPath = item->data(Qt::UserRole).toString();
        delete playBackWin_;
        playBackWin_ = nullptr;
        playBackWin_ = new PlayBackWin(videoPath,photoPath_,equipmentNumber_);
        playBackWin_->show();
        connect(playBackWin_, &PlayBackWin::backLookVideoWin, this, &LookVideoWin::backLookVideoWin);
        connect(playBackWin_, &PlayBackWin::lastVideoSignal, this, &LookVideoWin::sendLastVideoPath);
        connect(playBackWin_, &PlayBackWin::nextVideoSignal, this, &LookVideoWin::sendNextVideoPath);
    }
    else{
        QMessageBox::warning(playBackWin_,"警告","已经是这一页最后一个视频了");
    }
}
