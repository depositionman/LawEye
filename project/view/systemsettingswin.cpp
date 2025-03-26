#include "systemsettingswin.h"
#include "mywidget/shadowlabel.h"
#include <QLabel>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include "controller/equipmentcontroller.h"
#include <QList>
#include <QString>
#include <QFileDialog>
#include <QPushButton>
#include <QDebug>
#include <QSpacerItem>
#include "view/mainwidget.h"
#include <QMessageBox>
#include "util/simpleQtLogger.h"
#include "controller/settingcontroller.h"
#include "util/sqliteutil.h"
#include "mywidget/noticelabel.h"

// 递归计算文件夹大小的函数
quint64 calculateFolderSize(const QString &folderPath) {
    quint64 totalSize = 0;
    QDir dir(folderPath);
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    // 计算文件夹内所有文件的大小
    foreach (QFileInfo fileInfo, fileList) {
        totalSize += fileInfo.size();
    }

    // 递归计算子文件夹的大小
    QFileInfoList folderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo folderInfo, folderList) {
        totalSize += calculateFolderSize(folderInfo.absoluteFilePath());
    }

    return totalSize;
}

SystemSettingsWin::SystemSettingsWin(QWidget *parent) : QWidget(parent)
{
    mainWidget_ = nullptr;
    init_win();
}

SystemSettingsWin::~SystemSettingsWin()
{
    delete mainWidget_;
    mainWidget_ = nullptr;
}

void SystemSettingsWin::init_win()
{
    this->setFixedSize(700,800);
    //主布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    //主窗口设置主布局
    this->setLayout(mainLayout);
    //创建其余布局管理器
    QHBoxLayout *titleLayout = new QHBoxLayout;
    QGridLayout *gridLayout = new QGridLayout;
    QHBoxLayout *btnLayout = new QHBoxLayout;
    QWidget *titleWin = new QWidget;
    QWidget *gridWin = new QWidget;
    QWidget *btnWin = new QWidget;
    //将这些布局管理器添加到主布局中
    mainLayout->addWidget(titleWin,2);
    mainLayout->addWidget(gridWin,5);
    mainLayout->addWidget(btnWin,2);
    //设置各个布局器的格式
    titleLayout->setMargin(0);
    titleLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    //标题
    ShadowLabel *title = new ShadowLabel;
    title->setText("设置界面");
    title->setFixedSize(400,50);
    title->setAlignment(Qt::AlignCenter);
    //添加控件到布局中
    titleLayout->addStretch(1);
    titleLayout->addWidget(title);
    titleLayout->addStretch(1);
    titleWin->setLayout(titleLayout);
    //设备编号
    QLabel *equitNumberLabel = new QLabel;
    equitNumberLabel->setText("设备编号");
    equitNumberLabel->setMinimumSize(100,60);
    comboBox_ = new QComboBox;
    comboBox_->setMinimumSize(200,60);
    EquipmentController equipmentController;
    QList<QString> equipmentNumber = equipmentController.getAllEquipmentNumber();
    for(int i = 0; i < equipmentNumber.size(); ++i){
        comboBox_->addItem(equipmentNumber.at(i));
    }
    connect(comboBox_, &QComboBox::currentTextChanged, this, &SystemSettingsWin::getComboBoxStatus);
    //获取该设备对应的存储路径
    Setting settingInfo = settingController_.getSettingInfoByNumber(comboBox_->currentText());
    //内存空间
    QLabel *memoryLabel = new QLabel;
    memoryLabel->setText("内存空间");
    memoryLabel->setFixedSize(100,60);
    QLineEdit *memoryEdit = new QLineEdit;
    memoryEdit->setMinimumSize(200,60);
    memoryEdit->setText("20G");
    //录像存储
    QLabel *videoSave = new QLabel;
    videoSave->setText("录像存储");
    videoSave->setFixedSize(100,60);
    QPushButton *videoButton = new QPushButton;
    videoButton->setMinimumSize(50,50);
    videoButton->setIcon(QIcon(":/img/folder.png"));
    videoPathEdit_ = new QLineEdit;
    videoPathEdit_->setMinimumSize(200,60);
    videoPathEdit_->setText(settingInfo.videoPath());
    connect(videoButton, &QPushButton::clicked, this, &SystemSettingsWin::getVideoFilePath);
    //图片存储
    QLabel *photoSave = new QLabel;
    photoSave->setText("图片存储");
    photoSave->setFixedSize(100,60);
    QPushButton *photoButton = new QPushButton;
    photoButton->setIcon(QIcon(":/img/folder.png"));
    photoButton->setMinimumSize(50,50);
    photoPathEdit_ = new QLineEdit;
    photoPathEdit_->setMinimumSize(200,60);
    photoPathEdit_->setText(settingInfo.photoPath());
    connect(photoButton, &QPushButton::clicked, this, &SystemSettingsWin::getphotoFilePath);
    //剩余内存
    QLabel *surplusLabel = new QLabel;
    surplusLabel->setText("剩余内存");
    surplusLabel->setFixedSize(100,60);
    surplusSizeGB_ = 20;
    surplusEdit_ = new QLineEdit;
    surplusEdit_->setMinimumSize(200,60);
    if(videoPathEdit_->text() != ""){
        videoSize_ = calculateFolderSize(videoPathEdit_->text());
    }
    if(photoPathEdit_->text() != ""){
        photoSize_ = calculateFolderSize(photoPathEdit_->text());
    }
    useSizeGB_ = (videoSize_ + photoSize_) / (1024.0 * 1024.0) / 1024.0;
    surplusSizeGB_ = 20 - useSizeGB_;
    surplusEdit_->setText(QString("%1G").arg(surplusSizeGB_));
    m_noticeLable_ = new NoticeLabel;
    m_noticeLable_->setNoticeType(NoticeType::TEXT_BACKGROUND);
    m_noticeLable_->setTextColor(QColor(0,0,255));
    m_noticeLable_->setBackgroundColor(QColor(255,255,255));
    m_noticeLable_->Notice(this,QString("检测完成！"));
    //将所有相关控件添加到网格布局中
    gridLayout->addWidget(equitNumberLabel, 0, 0);
    gridLayout->addWidget(comboBox_, 0, 1);
    gridLayout->addWidget(memoryLabel, 1, 0);
    gridLayout->addWidget(memoryEdit, 1, 1);
    gridLayout->addWidget(surplusLabel, 2, 0);
    gridLayout->addWidget(surplusEdit_, 2, 1);
    gridLayout->addWidget(videoSave, 3, 0);
    gridLayout->addWidget(videoPathEdit_, 3, 1);
    gridLayout->addWidget(videoButton, 3, 2);
    gridLayout->addWidget(photoSave, 4, 0);
    gridLayout->addWidget(photoPathEdit_, 4, 1);
    gridLayout->addWidget(photoButton, 4, 2);
    //设置网格布局的格式
    gridLayout->setSpacing(5);
    gridWin->setLayout(gridLayout);

    //下面两个按钮
    //确定和取消按钮
    QPushButton *confirmBtn = new QPushButton;
    confirmBtn->setText("确定");
    confirmBtn->setFixedSize(120,60);
    connect(confirmBtn, &QPushButton::clicked, this, &SystemSettingsWin::createMainWin);
    QPushButton *cancelBtn = new QPushButton;
    cancelBtn->setText("取消");
    cancelBtn->setFixedSize(120,60);
    connect(cancelBtn, &QPushButton::clicked, this, &SystemSettingsWin::clearAllText);
    btnLayout->addWidget(confirmBtn);
    btnLayout->addWidget(cancelBtn);
    btnWin->setLayout(btnLayout);
}

void SystemSettingsWin::getVideoFilePath()
{
    QFileDialog *videoDialog = new QFileDialog;
    videoPathEdit_->setText(videoDialog->getExistingDirectory());
    //计算该文件夹的内存大小
    videoSize_ = calculateFolderSize(videoPathEdit_->text());
    //更新剩余内存
    useSizeGB_ = (videoSize_ + photoSize_) / (1024.0 * 1024.0) / 1024.0;
    surplusSizeGB_ = 20 - useSizeGB_;
    surplusEdit_->setText(QString("%1G").arg(surplusSizeGB_));
    m_noticeLable_->Notice(this,QString("检测完成！"));
}

void SystemSettingsWin::getphotoFilePath()
{
    QFileDialog *photoDialog = new QFileDialog;
    photoPathEdit_->setText(photoDialog->getExistingDirectory());
    //计算该文件夹的内存大小
    photoSize_ = calculateFolderSize(photoPathEdit_->text());
    //更新剩余内存
    useSizeGB_ = (videoSize_ + photoSize_) / (1024.0 * 1024.0) / 1024.0;
    surplusSizeGB_ = 20 - useSizeGB_;
    surplusEdit_->setText(QString("%1G").arg(surplusSizeGB_));
    m_noticeLable_->Notice(this,QString("检测完成！"));
}

void SystemSettingsWin::createMainWin()
{
    if(videoPathEdit_->text() != "" && photoPathEdit_->text() != "")
    {
        if(settingController_.querySettingInfoByNumber(comboBox_->currentText()) == EXIST)
        {
            settingController_.changeSettingInfoByNumber
                    (videoPathEdit_->text(),photoPathEdit_->text(),comboBox_->currentText());
        }
        else
        {
            //首先将数据（设备编号 图片存储路径 视频存储路径）存储到数据库中，方便后续使用
            settingController_.addSettingInfo
                    (videoPathEdit_->text(), photoPathEdit_->text(), comboBox_->currentText());
        }
        //创建主界面
        if(mainWidget_ == nullptr){
            mainWidget_ = new MainWidget;
            mainWidget_->setWindowFlags(Qt::FramelessWindowHint);
            mainWidget_->show();
            connect(this, &SystemSettingsWin::sendSettingNumber, mainWidget_, &MainWidget::receiveEquipmentNumber);
            connect(this, &SystemSettingsWin::sendVideoPath, mainWidget_, &MainWidget::receiveVideoPath);
            connect(this, &SystemSettingsWin::sendPhotoPath, mainWidget_, &MainWidget::receivePhotoPath);
            connect(mainWidget_,&MainWidget::backSetWin,this,&SystemSettingsWin::backSetWin);
            emit sendSettingNumber(comboBox_->currentText());
            emit sendVideoPath(videoPathEdit_->text());
            emit sendPhotoPath(photoPathEdit_->text());
        }
        else{
            mainWidget_->show();
        }
        //隐藏该窗口
        this->hide();
    }
    else{
        QMessageBox::warning(this, QString("警告"), QString("请先选择存储图片/录像的路径！"));
    }
}

void SystemSettingsWin::getComboBoxStatus(const QString &text)
{
    Setting settingInfo = settingController_.getSettingInfoByNumber(comboBox_->currentText());
    videoPathEdit_->setText(settingInfo.videoPath());
    photoPathEdit_->setText(settingInfo.photoPath());
    if(videoPathEdit_->text() != ""){
        videoSize_ = calculateFolderSize(videoPathEdit_->text());
    }
    if(photoPathEdit_->text() != ""){
        photoSize_ = calculateFolderSize(photoPathEdit_->text());
    }
    useSizeGB_ = (videoSize_ + photoSize_) / (1024.0 * 1024.0) / 1024.0;
    surplusSizeGB_ = 20 - useSizeGB_;
    surplusEdit_->setText(QString("%1G").arg(surplusSizeGB_));
    m_noticeLable_->Notice(this,QString("检测完成！"));
}

void SystemSettingsWin::backSetWin()
{
    this->show();
    mainWidget_->hide();
}

void SystemSettingsWin::clearAllText()
{
    videoPathEdit_->setText("");
    photoPathEdit_->setText("");
    surplusEdit_->setText("20G");
    NoticeLabel m_noticeLable;
    m_noticeLable.setNoticeType(NoticeType::TEXT_BACKGROUND);
    m_noticeLable.setTextColor(QColor(0,0,255));
    m_noticeLable.setBackgroundColor(QColor(127,127,127));
    m_noticeLable.Notice(this,QString("检测完成！"));
}
