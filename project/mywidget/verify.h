#ifndef VERIFY_H
#define VERIFY_H

#include <QWidget>
#include <QString>
#include <QFrame>
#include <QLabel>

class Verify : public QLabel
{
public:
    Verify();
    void generateRandNum();
    QString getCode() const;
    void setCode(const QString &value);

    void updateVer();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
private:
   QString code;
};

#endif // VERIFY_H
