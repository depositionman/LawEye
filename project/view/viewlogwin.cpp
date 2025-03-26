#include "viewlogwin.h"
#include "mywidget/shadowlabel.h"
#include <QPushButton>
#include <QDateEdit>
#include <QDebug>
#include <QTableWidget>
#include "controller/logcontroller.h"
#include <QMessageBox>
#include <QCloseEvent>

ViewLogWin* ViewLogWin::viewLogWin = nullptr;

ViewLogWin::ViewLogWin()
{
    yeshu_ = 0;
    init_allWindow();
    init_qss();
}

QString ViewLogWin::getEquipmentNumber() const
{
    return equipmentNumber_;
}

void ViewLogWin::setEquipmentNumber(const QString &equipmentNumber)
{
    equipmentNumber_ = equipmentNumber;
}

QString ViewLogWin::getPoliceNumber() const
{
    return policeNumber_;
}

void ViewLogWin::setPoliceNumber(const QString &policeNumber)
{
    policeNumber_ = policeNumber;
}

ViewLogWin *ViewLogWin::getViewLogWin()
{
    if(ViewLogWin::viewLogWin == nullptr){
        ViewLogWin::viewLogWin = new ViewLogWin();
    }
    return ViewLogWin::viewLogWin;
}

void ViewLogWin::init_allWindow()
{
    this->setFixedSize(700,800);
    //创建主布局管理器
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    //将主窗口分为三部分
    QWidget *titleWin = new QWidget;
    QWidget *contentWin = new QWidget;
    QWidget *btnWin = new QWidget;
    mainLayout->addWidget(titleWin,2);
    mainLayout->addWidget(contentWin,8);
    mainLayout->addWidget(btnWin,2);
    //为三个部分窗口分别创建布局管理器
    QHBoxLayout *titleLayout = new QHBoxLayout;
    contentLayout_ = new QVBoxLayout;
    QVBoxLayout *btnLayout = new QVBoxLayout;
    titleWin->setLayout(titleLayout);
    contentWin->setLayout(contentLayout_);
    btnWin->setLayout(btnLayout);

    //标题布局管理器
    ShadowLabel *title = new ShadowLabel;
    title->setFixedSize(288,48);
    title->setText("操作日志界面");
    titleLayout->addStretch(1);
    titleLayout->addWidget(title);
    titleLayout->addStretch(1);

    //按钮布局管理器
    QHBoxLayout *btnLayout1 = new QHBoxLayout;
    QPushButton *exitBtn = new QPushButton;
    exitBtn->setText("返回");
    exitBtn->setFixedSize(400,50);
    btnLayout1->addWidget(exitBtn);
    connect(exitBtn,&QPushButton::clicked,this,&ViewLogWin::backMainWin);
    QPushButton *prevBtn = new QPushButton;
    prevBtn->setText("上一页");
    prevBtn->setFixedSize(150,50);
    QPushButton *nextBtn = new QPushButton;
    nextBtn->setText("下一页");
    nextBtn->setFixedSize(150,50);
    QHBoxLayout *btnLayout2 = new QHBoxLayout;
    btnLayout2->addStretch(2);
    btnLayout2->addWidget(prevBtn);
    btnLayout2->addStretch(1);
    btnLayout2->addWidget(nextBtn);
    btnLayout2->addStretch(2);
    btnLayout->addLayout(btnLayout2);
    btnLayout->addLayout(btnLayout1);

    //操作部分布局管理器(遍历logList_将数据展示出来)
    tableWidget_ = new QTableWidget(0, 4, this); // 0 行，4 列
    QStringList headers = {"时间", "设备编号", "警员编号", "操作类型"};
    tableWidget_->setHorizontalHeaderLabels(headers);
    contentLayout_->addWidget(tableWidget_);

    //展示开头的十条数据
    fillTableWithCurrentPageData();

    connect(prevBtn, &QPushButton::clicked, this, &ViewLogWin::onPrevButtonClicked);
    connect(nextBtn, &QPushButton::clicked, this, &ViewLogWin::onNextButtonClicked);
}

void ViewLogWin::init_qss()
{
    QFile file(":/qss/log.qss");
    if(file.open(QFile::ReadOnly))
    {
        this->setStyleSheet(file.readAll());
//        qDebug()<<"文件打开成功";
        file.close();
    }
}

void ViewLogWin::printStatus(QString operationType)
{
    // 获取当前日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    // 将日期和时间格式化为字符串
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");
    //将操作日志写入数据库
    LogController logController;
    logController.appendLogInfo(operationType,formattedDateTime,equipmentNumber_,policeNumber_);
    fillTableWithCurrentPageData();
}

void ViewLogWin::fillTableWithCurrentPageData()
{
    QList<Log> logList;
    tableWidget_->clearContents();
    LogController logController;
    logList.clear();
    logList = logController.queryTenLog(10,yeshu_*10);
    for(int row = 0; row < 10 && row < logList.size(); ++row){
        tableWidget_->setRowCount(logList.size());  // 插入一行
        QTableWidgetItem *dateItem = new QTableWidgetItem(logList.at(row).time());
        QTableWidgetItem *equipmentItem = new QTableWidgetItem(logList.at(row).equipmentNumber());
        QTableWidgetItem *policeItem = new QTableWidgetItem(logList.at(row).policeNumber());
        QTableWidgetItem *operationItem = new QTableWidgetItem(logList.at(row).operationType());
        // 分别将数据插入到不同的列中
        tableWidget_->setItem(row, 0, dateItem);       // 第一列插入日期时间
        tableWidget_->setItem(row, 1, equipmentItem);  // 第二列插入设备编号
        tableWidget_->setItem(row, 2, policeItem);     // 第三列插入警员编号
        tableWidget_->setItem(row, 3, operationItem);  // 第四列插入操作类型
    }
}

void ViewLogWin::closeEvent(QCloseEvent *event)
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

void ViewLogWin::onPrevButtonClicked()
{
    if(yeshu_ > 0)//第0页开始，不能小于-1
    {
        --yeshu_;
        fillTableWithCurrentPageData();
    }
    else
    {
        QMessageBox::information(this,"提醒","已经是第一页了");
    }
}

void ViewLogWin::onNextButtonClicked()
{
    LogController logController;
    int maxyeshu = 0;
    int count = logController.queryCountLog();
    if(count % 10 != 0){
        maxyeshu = count/10 +1;
    }
    else{
        maxyeshu = count/10;
    }
    if(yeshu_ < maxyeshu - 1)
    {
        ++yeshu_;
        fillTableWithCurrentPageData();
    }
    else
    {
        QMessageBox::information(this,"提醒","已经是最后一页了");
    }
}
