#include "graphicsview.h"
#include <QBrush>
#include <Qpixmap>
#include <QColor>
#include <QTimer>
#include <QDebug>
#include "view/systemsettingswin.h"

/**将图片白色背景部分变透明
 * @brief removeWhiteBackground
 * @param path 1.const QString &path填图片的路径 2.int tolerance对白色的容忍度
 * @return 处理后的图片
 */
QImage removeWhiteBackground(const QString &path, int tolerance) {
    QImage image(path);
    image = image.convertToFormat(QImage::Format_ARGB32);

    QColor white(Qt::white);
//    int tolerance = 20;  // 容忍度可以调整

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);
            // 检查颜色是否接近白色
            if (color.red() > white.red() - tolerance && color.green() > white.green() - tolerance && color.blue() > white.blue() - tolerance) {
                color.setAlpha(0);  // 设置为透明
                image.setPixelColor(x, y, color);
            }
        }
    }
    return image;
}

GraphicsView::GraphicsView()
{
    this->setWindowTitle("执法记录仪开机ing...");
    this->setFixedSize(700,800);
    //添加图元的背景图
    this->setBackgroundBrush(QBrush(QPixmap(":/img/openBackground.png")));
    //要设置场景才能显示背景图
    this->scene_ = new QGraphicsScene(this);
    this->setScene(this->scene_);
    //设置坐标 将(0,0)点改到图片左上角  默认是图片中心
    this->setSceneRect(0, 0, this->width()-2, this->height()-2);
    //进行图片背景的处理，得到背景透明的图片
    QPixmap thiefImg = QPixmap::fromImage(removeWhiteBackground(":/img/thief.png",18));
    QPixmap policeImg = QPixmap::fromImage(removeWhiteBackground(":/img/police.png",20));
    //创建GraphicsItem对象
    this->thief_item = new GraphicsItem(thiefImg,0);
    this->police_item = new GraphicsItem(policeImg,1);
    //设置GraphicsItem对象的位置
    this->thief_item->setPos(150,500);
    this->police_item->setPos(450,500);
    //将GraphicsItem对象添加到场景中
    this->scene_->addItem(thief_item);
    this->scene_->addItem(police_item);
    //建立连接让人物动起来
    QTimer *timer1 = new QTimer(this);
    timer1->start(25);
    connect(timer1,SIGNAL(timeout()),this->scene_,SLOT(advance()));
    //连接人物与
    connect(this->thief_item, SIGNAL(enterSettingWin()), this, SLOT(createSettingWin()));
}

void GraphicsView::createSettingWin()
{
    this->close();
    disconnect(this->thief_item, SIGNAL(enterSettingWin()), this, SLOT(createSettingWin()));
    SystemSettingsWin * systemSettingsWin = new SystemSettingsWin;
    systemSettingsWin->show();
}
