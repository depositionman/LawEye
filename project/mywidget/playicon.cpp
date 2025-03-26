#include "playicon.h"

PlayIcon::PlayIcon()
{

}

void PlayIcon::mouseReleaseEvent(QMouseEvent *ev)
{
    emit changeVideoStatus();
}
