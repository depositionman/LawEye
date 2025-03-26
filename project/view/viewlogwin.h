#ifndef VIEWLOGWIN_H
#define VIEWLOGWIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "data/log.h"
#include <QString>
#include <QList>
#include <QTableWidget>

class ViewLogWin : public QWidget
{
    Q_OBJECT
public:
    static ViewLogWin* getViewLogWin();
    void init_allWindow();
    void init_qss();

    QString getPoliceNumber() const;
    void setPoliceNumber(const QString &policeNumber);

    QString getEquipmentNumber() const;
    void setEquipmentNumber(const QString &equipmentNumber);
    void fillTableWithCurrentPageData();
protected:
    void closeEvent(QCloseEvent *event);
private:
    //提供一个接口
    static ViewLogWin* viewLogWin;
    //私有化构造函数
    ViewLogWin();
    QString equipmentNumber_;
    QString policeNumber_;
    QVBoxLayout *contentLayout_;
    QTableWidget *tableWidget_;
    int yeshu_;
signals:
    void backMainWin();
public slots:
    void printStatus(QString);
    void onPrevButtonClicked();
    void onNextButtonClicked();
};

#endif // VIEWLOGWIN_H
