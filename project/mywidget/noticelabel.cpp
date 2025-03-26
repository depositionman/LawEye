#include "noticelabel.h"

NoticeLabel::NoticeLabel(QWidget *parent)
    :m_pParent(parent)
{
    //文字居中
    setAlignment(Qt::AlignCenter);

    m_pTimer = new QTimer();
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()), Qt::UniqueConnection);

    m_opacity_cut_val = 255/(1000/40)+1;  //透明度最大值255  最后1000ms开始降低透明度

    QFont font;
    font.setFamily("微软雅黑");
    font.setBold(true);
    font.setPointSizeF(20);
    setFont(font);

    m_noticeType = NoticeType::ONLY_TEXT;
}

NoticeLabel::~NoticeLabel()
{
    if (m_pTimer->isActive())
    {
        m_pTimer->stop();
    }

    delete m_pTimer;
    deleteLater();
}

void NoticeLabel::Notice(QWidget *parent, const QString &strMessage, const int delay_ms)
{
    if (m_pTimer->isActive())
    {
        m_pTimer->stop();
        setVisible(false);
    }

    if (strMessage.isEmpty() || delay_ms <= 0)
    {
        return;
    }

    setParent(parent);
    m_pParent = parent;
    setMesseage(strMessage, delay_ms);
    m_pTimer->start(40);
}

void NoticeLabel::onTimerTimeout()
{
    m_delay_ms -= 40;
    if (m_delay_ms > 0)
    {
        //重新定位(窗口大小和位置可能变化)
        if (nullptr != m_pParent)
        {
            QPoint pt((m_pParent->width() - width()) >> 1, (m_pParent->height() - height()) >> 1);
            if (pos() != pt)
            {
                changeSize();
                move(pt);
            }
        }

        //最后1s开始渐变消失
        if (m_delay_ms <= 1000)
        {
            m_opacity_val -= m_opacity_cut_val;
            if (m_opacity_val < 0)
            {
                m_opacity_val = 0;
            }

            setColor();
        }
    }
    else
    {
        //显示结束
        m_pTimer->stop();
        setVisible(false);
    }
}

void NoticeLabel::setMesseage(const QString &strMessage, int delay_ms)
{
    QStringList strList = strMessage.split("\n");
    QFontMetrics fontMetrics(font());
    m_vecLinesLen.clear();

    int tmpW = 0;
    int maxLineLen = 1; //最长那一行的长度
    foreach (auto s, strList)
    {
        tmpW = fontMetrics.width(s);
        m_vecLinesLen.push_back(tmpW);
        if (maxLineLen < tmpW)
        {
            maxLineLen = tmpW;
        }
    }

    m_Width = fontMetrics.width(strMessage);
    m_Height = fontMetrics.lineSpacing() + 10;
    m_MinHeight = (m_Width * m_Height)/maxLineLen + 1;//面积除以最长的宽就是最小的高

    //设置宽高
    changeSize();

    //换行
    setWordWrap(true);

    //设置显示内容
    setText(strMessage);

    //居中
    if (m_pParent != nullptr)
    {
        move((m_pParent->width() - width()) >> 1, (m_pParent->height() - height()) >> 1);
    }

    setVisible(true);//显示
    m_delay_ms = delay_ms;
    m_opacity_val = 255;

    setColor();
 }

void NoticeLabel::changeSize()
{
    if (m_pParent != nullptr)
    {
        double wd = m_pParent->width() * 0.6;

        int newH = (m_Height * m_Width)/wd + 10;
        if (newH < (m_Height + m_Height))
        {
            newH = m_MinHeight + m_Height;
        }
        else
        {
            foreach (auto lineLen, m_vecLinesLen)
            {
                if (lineLen > wd)
                {
                    newH += m_Height;
                }
            }
        }

        setFixedSize((int)wd, newH);
    }
}

void NoticeLabel::setNoticeType(NoticeType type)
{
    m_noticeType = type;
}

void NoticeLabel::setTextColor(QColor textColor)
{
    m_textColor = textColor;
}

void NoticeLabel::setBackgroundColor(QColor bgColor)
{
    m_bgColor = bgColor;
}

void NoticeLabel::setColor()
{
    switch (m_noticeType) {
    case ONLY_TEXT:
        setStyleSheet(QString("color:rgba(%1, %2, %3, %4)").arg(m_textColor.red()).arg(m_textColor.green()).arg(m_textColor.blue()).arg(m_opacity_val));
        break;
    case TEXT_BACKGROUND:
        setStyleSheet(QString("color:rgb(%1, %2, %3);border-radius:8px;background-color:rgba(%4, %5, %6, %7);") \
                      .arg(m_textColor.red()).arg(m_textColor.green()).arg(m_textColor.blue()) \
                      .arg(m_bgColor.red()).arg(m_bgColor.green()).arg(m_bgColor.blue()).arg(m_opacity_val));
        break;
    default:
        break;
    }
}
