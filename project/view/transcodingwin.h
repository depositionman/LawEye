#ifndef TRANSCODINGWIN_H
#define TRANSCODINGWIN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include <QPushButton>
#include <QString>
#include <QListWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QProgressBar>

class TranscodingWin : public QWidget
{
    Q_OBJECT
public:
    explicit TranscodingWin();
    void init_allWin();
    void init_qss();
    void changeProgressBar();
protected:
    void closeEvent(QCloseEvent *event);
private:
    QListWidget *listWidget_;
    QString photoPath_;
    QComboBox *transCom_;
    QLineEdit *videoPathEdit_;
    QProgressBar *progressBar_;
    QString videoPath_;
    int value_;
    int videoFlag_;//选中视频的标志位
signals:
    void backMainWin();
public slots:
    void changeVideoByTime(QDateTime datetime);
    void getVideoFilePath();
    void transCoding();
    void getVideoPath(const QModelIndex &index);
    void updateProgressBar();
    void fillProgressBar();
};

#endif // TRANSCODINGWIN_H
