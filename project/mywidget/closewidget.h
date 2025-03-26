#ifndef CLOSEWIDGET_H
#define CLOSEWIDGET_H

#include <QObject>
#include <QPushButton>

class CloseWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit CloseWidget(QPushButton *parent = 0);
protected:
    void mouseReleaseEvent(QMouseEvent *e);
signals:
    void closeMainWin();
public slots:
};

#endif // CLOSEWIDGET_H
