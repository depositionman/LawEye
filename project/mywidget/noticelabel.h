#ifndef NOTICELABEL_H
#define NOTICELABEL_H

#include <QLabel>
#include <QTimer>
#include <QColor>

enum NoticeType
{
    ONLY_TEXT = 0,	//纯文字;
    TEXT_BACKGROUND		//文字和背景
};

class NoticeLabel : public QLabel
{
    Q_OBJECT
public:
    NoticeLabel(QWidget *parent = 0);
    ~NoticeLabel();

    //显示消息，可设置delay_ms=0来控制显示时间
    void Notice(QWidget *parent, const QString &strMessage, const int delay_ms = 2000);

    void setNoticeType(NoticeType type);
    void setTextColor(QColor textColor);
    void setBackgroundColor(QColor bgColor);

public slots:
    void onTimerTimeout();

private:
    void setMesseage(const QString &strMessage, int delay_ms);
    void changeSize();
    void setColor();

private:
    QWidget *m_pParent;
    QTimer  *m_pTimer;
    int m_delay_ms;//显示时间
    int m_opacity_cut_val;//透明度递减值
    int m_opacity_val;//当前透明度
    int m_Width;  //一行宽度
    int m_Height; //一行高度
    int m_MinHeight; //最小高度
    QVector<int> m_vecLinesLen;
    QColor m_textColor;
    QColor m_bgColor;
    NoticeType m_noticeType;
};

#endif // NOTICELABEL_H
