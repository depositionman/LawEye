#include "closewidget.h"

CloseWidget::CloseWidget(QPushButton *parent)
{

}

void CloseWidget::mouseReleaseEvent(QMouseEvent *e)
{
    emit closeMainWin();
}
