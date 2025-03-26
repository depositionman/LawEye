#include "lookphotowin.h"
#include "mywidget/shadowlabel.h"
#include <QGridLayout>
#include "util/simpleQtLogger.h"
#include <QDir>
#include <QDebug>
#include "data/photo.h"
#include "controller/photocontroller.h"
#include <QListWidget>
#include "data/showpicture.h"
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QCloseEvent>

LookPhotoWin::LookPhotoWin()
{
    startRow_ = 0;
    listWidget_ = new QListWidget(this);
    init_allWin();
}

LookPhotoWin::~LookPhotoWin()
{
    delete title_;
    title_ = nullptr;
}

void LookPhotoWin::init_allWin()
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
    title_ = new ShadowLabel;
    title_->setText("查看现场照片");
    title_->setFixedSize(288,48);

    QPushButton *backBtn = new QPushButton(this);
    backBtn->setIcon(QIcon(":/img/exit.png"));
    connect(backBtn, &QPushButton::clicked, this, &LookPhotoWin::backMainWin);

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
    connect(dateEdit, &QDateEdit::dateTimeChanged, this, &LookPhotoWin::changePhotoByTime);
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
    titleLayout->addWidget(title_);
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
    //分页查询，从数据库中获取图片的信息添加到链表中
    PhotoController photoController;
    QList<Photo> photoList = photoController.pageQueryPhotoInfo(4,startRow_);//有问题
    QList<Photo>::iterator it_photo;
    //将对应的照片加载到ShowPicture的链表中
    QList<ShowPicture> showPictureList;
    QList<ShowPicture>::iterator it_show;
    for(it_photo = photoList.begin(); it_photo != photoList.end(); ++it_photo)
    {
        showPictureList.append(ShowPicture((*it_photo).path(), (*it_photo).name()));
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
    for(it_show = showPictureList.begin(); it_show != showPictureList.end(); ++it_show)
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).imgPath()), (*it_show).name());
        item->setData(Qt::UserRole, (*it_show).imgPath());
        listWidget_->addItem(item);
    }
    middleLayout->addWidget(listWidget_);

    //3.button的布局设计
    QPushButton *loadBtn = new QPushButton(this);
    loadBtn->setText("加载更多..");
    loadBtn->setFixedSize(200,50);
    connect(loadBtn, &QPushButton::clicked, this, &LookPhotoWin::loadMorePhoto);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(loadBtn);
    buttonLayout->addStretch(1);
    buttonLayout->setSpacing(0);
    buttonLayout->setMargin(0);

    //双击查看照片
    connect(listWidget_, &QListWidget::doubleClicked, this, &LookPhotoWin::playPhoto);
}

void LookPhotoWin::closeEvent(QCloseEvent *event)
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

void LookPhotoWin::loadMorePhoto()
{
    startRow_ += 4;
    qDebug() << "startRow_：" << startRow_;
    if(findFlag_ == 0){
        //将新数据写入链表中
        PhotoController photoController;
        QList<Photo> photoList = photoController.pageQueryPhotoInfo(4,startRow_);
        if(photoList.size() != 0){
            QList<Photo>::iterator it_photo;
            //将对应的照片加载到ShowPicture的链表中
            QList<ShowPicture> showPictureList;
            QList<ShowPicture>::iterator it_show;
            for(it_photo = photoList.begin(); it_photo != photoList.end(); ++it_photo)
            {
                showPictureList.append(ShowPicture((*it_photo).path(), (*it_photo).name()));
            }
            for(it_show = showPictureList.begin(); it_show != showPictureList.end(); ++it_show)
            {
                QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).imgPath()), (*it_show).name());
                item->setData(Qt::UserRole, (*it_show).imgPath());
                listWidget_->addItem(item);
            }
        }//if(photoList.size() != 0)
        else
        {
            QMessageBox::information(this,"提示","没有更多图片了");
        }
    }
    else{
        //将新数据写入链表中
        PhotoController photoController;
        QList<Photo> photoList = photoController.queryTimeWithinAllPhoto(startTimeString_, endTimeString_,4,startRow_);
        if(photoList.size() != 0){
            QList<Photo>::iterator it_photo;
            //将对应的照片加载到ShowPicture的链表中
            QList<ShowPicture> showPictureList;
            QList<ShowPicture>::iterator it_show;
            for(it_photo = photoList.begin(); it_photo != photoList.end(); ++it_photo)
            {
                showPictureList.append(ShowPicture((*it_photo).path(), (*it_photo).name()));
            }
            for(it_show = showPictureList.begin(); it_show != showPictureList.end(); ++it_show)
            {
                QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).imgPath()), (*it_show).name());
                item->setData(Qt::UserRole, (*it_show).imgPath());
                listWidget_->addItem(item);
            }
        }//if(photoList.size() != 0)
        else{
            QMessageBox::information(this,"提示","没有更多图片了");
        }
    }//else
}

void LookPhotoWin::playPhoto(const QModelIndex &index)
{
    QListWidgetItem *item = static_cast<QListWidget*>(sender())->item(index.row());
    QString imagePath = item->data(Qt::UserRole).toString();
    // 使用 QDesktopServices::openUrl 打开图片
    if (!QDesktopServices::openUrl(QUrl::fromLocalFile(imagePath))) {
        QMessageBox::warning(this, "Error", "Failed to open image: " + imagePath);
    }
}

void LookPhotoWin::changePhotoByTime(QDateTime datetime)
{
    startRow_ = 0;
    findFlag_ = 1;//进入查询模式
    startTimeString_ = datetime.toString("yyyy-MM-dd HH:mm:ss");
//    qDebug() << startTimeString_;
    QDateTime nextDay = datetime.addDays(1);
    endTimeString_ = nextDay.toString("yyyy-MM-dd HH:mm:ss");
//    qDebug() << endTimeString_;
    //将新数据写入链表中
    PhotoController photoController;
    QList<Photo> photoList = photoController.queryTimeWithinAllPhoto(startTimeString_, endTimeString_,4,startRow_);
    if(photoList.size() != 0){
        QList<Photo>::iterator it_photo;
        //将对应的照片加载到ShowPicture的链表中
        QList<ShowPicture> showPictureList;
        QList<ShowPicture>::iterator it_show;
        for(it_photo = photoList.begin(); it_photo != photoList.end(); ++it_photo)
        {
            showPictureList.append(ShowPicture((*it_photo).path(), (*it_photo).name()));
        }
        listWidget_->clear();
        for(it_show = showPictureList.begin(); it_show != showPictureList.end(); ++it_show)
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon((*it_show).imgPath()), (*it_show).name());
            item->setData(Qt::UserRole, (*it_show).imgPath());
            listWidget_->addItem(item);
        }
    }
    else{
        QMessageBox::information(this,"提示","该日期内没有照片");
    }
}
