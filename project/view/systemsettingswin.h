#ifndef SYSTEMSETTINGSWIN_H
#define SYSTEMSETTINGSWIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QFile>
#include <QComboBox>
#include "controller/settingcontroller.h"
#include "view/mainwidget.h"
#include "mywidget/noticelabel.h"

class SystemSettingsWin : public QWidget
{
    Q_OBJECT
public:
    explicit SystemSettingsWin(QWidget *parent = 0);
    ~SystemSettingsWin();
    void init_win();
    void clearAllText();
private:
    QLineEdit *videoPathEdit_;
    QLineEdit *photoPathEdit_;
    quint64 videoSize_ = 0;
    quint64 photoSize_ = 0;
    double useSizeGB_;
    double surplusSizeGB_;
    QLineEdit *surplusEdit_;
    QComboBox *comboBox_;
    SettingController settingController_;
    MainWidget *mainWidget_;
    NoticeLabel *m_noticeLable_;
signals:
    void sendSettingNumber(QString);
    void sendVideoPath(QString);
    void sendPhotoPath(QString);
public slots:
    void getVideoFilePath();
    void getphotoFilePath();
    void createMainWin();
    void getComboBoxStatus(const QString &text);
    void backSetWin();
};

#endif // SYSTEMSETTINGSWIN_H
