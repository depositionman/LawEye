#ifndef LOOKPHOTOWIN_H
#define LOOKPHOTOWIN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include <QPushButton>
#include <QString>
#include <QListWidget>
#include <mywidget/shadowlabel.h>

class LookPhotoWin : public QWidget
{
    Q_OBJECT
public:
    explicit LookPhotoWin();
    ~LookPhotoWin();
    void init_allWin();
protected:
    void closeEvent(QCloseEvent *event);
private:
    int startRow_;
    QListWidget *listWidget_;
    bool findFlag_;
    QString startTimeString_;
    QString endTimeString_;
    ShadowLabel *title_;
signals:
    void backMainWin();
public slots:
    void loadMorePhoto();
    void playPhoto(const QModelIndex &index);
    void changePhotoByTime(QDateTime datetime);
};

#endif // LOOKPHOTOWIN_H
