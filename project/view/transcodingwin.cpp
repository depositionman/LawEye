#include "transcodingwin.h"
#include "mywidget/shadowlabel.h"
#include "controller/videocontroller.h"
#include "data/showvideo.h"
#include "view/playbackwin.h"
#include <QFileDialog>
#include "util/trancetonormalvideofile.h"
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>

TranscodingWin::TranscodingWin()
{
    videoFlag_ = 0;
    value_ = 0;
    listWidget_ = new QListWidget;
    init_allWin();
    init_qss();
}

void TranscodingWin::init_allWin()
{
    this->setFixedSize(700,800);
    //为整体界面设置布局管理器
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    //划分为三个区域
    QWidget *topWin = new QWidget;
    QWidget *middleWin = new QWidget;
    QWidget *buttonWin = new QWidget;
    QVBoxLayout *topLayout = new QVBoxLayout;
    QGridLayout *middleLayout = new QGridLayout;
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    topWin->setLayout(topLayout);
    middleWin->setLayout(middleLayout);
    buttonWin->setLayout(buttonLayout);
    //将三个窗口加入主布局中
    mainLayout->addWidget(topWin,3);
    mainLayout->addWidget(middleWin,3);
    mainLayout->addWidget(buttonWin,7);
    //分别为这三个窗口设置布局管理器
    //1.top的布局设置
    //1.1初始化所有控件
    ShadowLabel *title = new ShadowLabel;
    title->setText("录像选择界面");
    title->setFixedSize(288,48);

    QPushButton *backBtn = new QPushButton;
    backBtn->setIcon(QIcon(":/img/exit.png"));
    connect(backBtn, &QPushButton::clicked, this, &TranscodingWin::backMainWin);

    QLabel *dateLabel = new QLabel;
    dateLabel->setText("请选择日期");
    dateLabel->setFixedSize(170,40);
    dateLabel->setStyleSheet("font-size: 30px");
    QDateEdit *dateEdit = new QDateEdit;
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
    connect(dateEdit, &QDateEdit::dateTimeChanged, this ,&TranscodingWin::changeVideoByTime);
    //1.2开始布局控件
    QHBoxLayout *backBtnLayout = new QHBoxLayout;
    backBtnLayout->addStretch(50);
    backBtnLayout->addWidget(backBtn);
    backBtnLayout->addStretch(1);
    backBtnLayout->setSpacing(0);
    backBtnLayout->setMargin(0);
    topLayout->addLayout(backBtnLayout,1);

    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->addStretch(1);
    titleLayout->addWidget(title);
    titleLayout->addStretch(1);
    titleLayout->setSpacing(0);
    titleLayout->setMargin(0);
    topLayout->addLayout(titleLayout,3);

    topLayout->addStretch(1);

    QHBoxLayout *dateLayout = new QHBoxLayout;
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
    QList<Video> videoList = videoController.queryAllVideoInfo();
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
    listWidget_->setIconSize(QSize(200,200));
    //根据窗口大小自适应布局
    listWidget_->setResizeMode(QListView::Adjust);
    //水平排列
    listWidget_->setFlow(QListView::TopToBottom);
    //图标间距
    listWidget_->setSpacing(10);
    //防止图标被拖动
    listWidget_->setMovement(QListView::Static);
    for(it_show = showVideoList.begin(); it_show != showVideoList.end(); ++it_show)
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).firstPhotoPath()), (*it_show).Name());
        item->setData(Qt::UserRole, (*it_show).Path());
        listWidget_->addItem(item);
    }
    middleLayout->addWidget(listWidget_);

    //btn的布局
    //转码格式
    QHBoxLayout *transLayout = new QHBoxLayout;
    QWidget *transWin = new QWidget;
    QLabel *transLabel = new QLabel;
    transLabel->setText("转码格式");
    transLabel->setFixedSize(100,50);
    transCom_ = new QComboBox;
    transCom_->addItem(QString("mp4"));
    transCom_->addItem(QString("avi"));
    //设置默认转码格式
    transCom_->setCurrentIndex(0);
    transCom_->setFixedSize(250,50);
    transLayout->addStretch(1);
    transLayout->addWidget(transLabel);
    transLayout->addWidget(transCom_);
    transLayout->addStretch(1);
    transWin->setLayout(transLayout);
    //路径存储
    QHBoxLayout *pathLayout = new QHBoxLayout;
    QWidget *pathWin = new QWidget;
    QLabel *pathLabel = new QLabel;
    pathLabel->setText("路径存储");
    pathLabel->setFixedSize(100,50);
    QPushButton *videoButton = new QPushButton;
    videoButton->setFixedSize(50,50);
    videoButton->setIcon(QIcon(":/img/folder.png"));
    videoPathEdit_ = new QLineEdit;
    videoPathEdit_->setFixedSize(200,50);
    connect(videoButton, &QPushButton::clicked, this, &TranscodingWin::getVideoFilePath);
    pathLayout->addStretch(1);
    pathLayout->addWidget(pathLabel);
    pathLayout->addWidget(videoPathEdit_);
    pathLayout->addWidget(videoButton);
    pathLayout->addStretch(1);
    pathWin->setLayout(pathLayout);
    //进度条
    QWidget *proWin = new QWidget;
    QHBoxLayout *proLayout = new QHBoxLayout;
    progressBar_ = new QProgressBar;
    progressBar_->setOrientation(Qt::Horizontal);  // 水平方向
    progressBar_->setMinimum(0);  // 最小值
    progressBar_->setValue(0);  // 当前进度
    progressBar_->setFixedSize(400,25);
    proLayout->addStretch(1);
    proLayout->addWidget(progressBar_);
    proLayout->addStretch(1);
    proWin->setLayout(proLayout);
    //按钮
    QWidget *btnWin = new QWidget;
    QHBoxLayout *btnLayou = new QHBoxLayout;
    QPushButton *confirmBtn = new QPushButton;
    confirmBtn->setText("确定");
    confirmBtn->setFixedSize(100,50);
    connect(confirmBtn,&QPushButton::clicked,this,&TranscodingWin::transCoding);
    QPushButton *exitmBtn = new QPushButton;
    exitmBtn->setText("返回");
    exitmBtn->setFixedSize(100,50);
    connect(exitmBtn,&QPushButton::clicked,this,&TranscodingWin::backMainWin);
    btnLayou->addStretch(2);
    btnLayou->addWidget(confirmBtn);
    btnLayou->addStretch(1);
    btnLayou->addWidget(exitmBtn);
    btnLayou->addStretch(2);
    btnWin->setLayout(btnLayou);
    //添加到底层布局管理器中
    buttonLayout->addWidget(transWin,1);
    buttonLayout->addWidget(pathWin,1);
    buttonLayout->addWidget(proWin,1);
    buttonLayout->addWidget(btnWin,1);
    buttonLayout->addStretch(1);

    //点击选中转码视频
    connect(listWidget_, &QListWidget::clicked, this, &TranscodingWin::getVideoPath);
}

void TranscodingWin::changeVideoByTime(QDateTime datetime)
{
    QString startTimeString = datetime.toString("yyyy-MM-dd HH:mm:ss");
//    qDebug() << startTimeString_;
    QDateTime nextDay = datetime.addDays(1);
    QString endTimeString = nextDay.toString("yyyy-MM-dd HH:mm:ss");
//    qDebug() << endTimeString_;
    VideoController videoController;
    QList<Video> videoList = videoController.queryTimeWithinAllVideo(startTimeString, endTimeString);
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

void TranscodingWin::init_qss()
{
    QFile file(":/qss/log.qss");
    if(file.open(QFile::ReadOnly))
    {
        this->setStyleSheet(file.readAll());
//        qDebug()<<"文件打开成功";
        file.close();
    }
}

void TranscodingWin::getVideoFilePath()
{
    QFileDialog *videoDialog = new QFileDialog;
    videoPathEdit_->setText(videoDialog->getExistingDirectory());
}

void TranscodingWin::transCoding()
{
    if(videoFlag_ == 1){
        if(videoPathEdit_->text() != ""){
            if(transCom_->currentIndex() == 0)
            {
                TranceToNormalVideoFile *tranceToNormalVideoFile = new TranceToNormalVideoFile;
                connect(tranceToNormalVideoFile,&TranceToNormalVideoFile::changeProgressBar,this,&TranscodingWin::updateProgressBar);
                connect(tranceToNormalVideoFile,&TranceToNormalVideoFile::tranceSuccess,this,&TranscodingWin::fillProgressBar);
                tranceToNormalVideoFile->loadSrcFile(videoPath_);
                VideoController videoController;
                QString name = videoController.queryVideoNameByVideoPath(videoPath_);
                QString savePath = videoPathEdit_->text() + + "/" + name + ".mp4";
                tranceToNormalVideoFile->tranceToMp4(savePath);
                QMessageBox::information(this,"提示","转码成功");
            }
            else
            {
                TranceToNormalVideoFile *tranceToNormalVideoFile = new TranceToNormalVideoFile;
                connect(tranceToNormalVideoFile,&TranceToNormalVideoFile::changeProgressBar,this,&TranscodingWin::updateProgressBar);
                connect(tranceToNormalVideoFile,&TranceToNormalVideoFile::tranceSuccess,this,&TranscodingWin::fillProgressBar);
                tranceToNormalVideoFile->loadSrcFile(videoPath_);
                VideoController videoController;
                QString name = videoController.queryVideoNameByVideoPath(videoPath_);
                QString savePath = videoPathEdit_->text() + "/" + name + ".avi";
                tranceToNormalVideoFile->tranceToMp4(savePath);
                QMessageBox::information(this,"提示","转码成功");
            }
        }
        else{
            QMessageBox::warning(this,"警告","请选择存储视频的路径再进行转码");
        }
    }
    else{
        QMessageBox::warning(this,"警告","请选择视频再进行转码");
    }
}

void TranscodingWin::getVideoPath(const QModelIndex &index)
{
    videoFlag_ = 1;
    QListWidgetItem *item = listWidget_->item(index.row());
    videoPath_ = item->data(Qt::UserRole).toString();
    //获取视频的时间
    VideoController videoController;
    QString videoTime_ = videoController.queryVideoTimeByVideoPath(videoPath_);
    videoTime_.chop(1);
    double videoTime = videoTime_.toDouble();
    progressBar_->setMaximum(static_cast<int>(videoTime * 1000));  // 将时间转换为毫秒，int类型，避免精度的缺失
}

void TranscodingWin::updateProgressBar()
{
    qDebug() << "value_" << value_;
    //更新进度条
    value_ += 40;
    progressBar_->setValue(value_);
    changeProgressBar();
}

void TranscodingWin::fillProgressBar()
{
    VideoController videoController;
    QString videoTime_ = videoController.queryVideoTimeByVideoPath(videoPath_);
    videoTime_.chop(1);
    double videoTime = videoTime_.toDouble();
    //更新进度条
    value_ = static_cast<int>(videoTime * 1000);
    progressBar_->setValue(value_);
    changeProgressBar();
}

void TranscodingWin::changeProgressBar()
{
    double dProgress = (progressBar_->value() - progressBar_->minimum()) * 100.0
                    / (progressBar_->maximum() - progressBar_->minimum()); // 百分比计算公式
    progressBar_->setFormat(QString::fromLocal8Bit("当前进度为：%1%").arg(QString::number(dProgress, 'f', 1)));
    progressBar_->setFormat(tr("Current progress : %1%").arg(QString::number(dProgress, 'f', 1)));
    progressBar_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  // 对齐方式
}

void TranscodingWin::closeEvent(QCloseEvent *event)
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
