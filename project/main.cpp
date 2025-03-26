#include <QApplication>
#include "util/simpleQtLogger.h"
#include <QDir>
#include "view/graphicsview.h"
#include "view/mainwidget.h"
#include "view/systemsettingswin.h"
#include <QFileDialog>
#include "view/loginwin.h"
#include "view/lookphotowin.h"
#include "controller/videocontroller.h"
#include <QDebug>
#include "view/playbackwin.h"
#include "view/viewlogwin.h"
#include "view/transcodingwin.h"
#include "controller/logcontroller.h"
#include <QCamera>
#include <QCameraInfo>
#include <QMessageBox>

//void InitLog(QObject* a)
//{
//    //init log begin
//    simpleqtlogger::SimpleQtLogger::createInstance(a);
//    simpleqtlogger::SimpleQtLogger::getInstance()->setLogFormat_file(
//        "<TS> [<LL>][<FUNC>()] [<TEXT>] [<FILE>:<LINE>]", "<TS> [<LL>] <TEXT>");
//    simpleqtlogger::ENABLE_LOG_SINK_CONSOLE = true;

//    simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_file(simpleqtlogger::ENABLE_LOG_LEVELS);
//    bool setLogSuccess = simpleqtlogger::SimpleQtLogger::getInstance()->setLogFileName(QDir::home().filePath(
//        "Documents/log/bodyWornCamera.log"), 10 * 1024 * 1024, 10);//10MB / file ; 10 file
//    LS_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>> MyApplication log started <<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
//    //init log end
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //初始化日志
//    InitLog(&a);
//    LookPhotoWin lw;
//    lw.show();

    GraphicsView gv;
    gv.show();

//    QString cameraName = "";
//    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
//    qDebug() << cameras.at(0).description();
    //    for(int i = 0; i < cameras.size(); ++i)
    //    {
    //        cameraName = cameras.at(i).description();
    //    }
    //    qDebug() << cameraName;

//    LoginWin lw;
//    lw.show();

//    MainWidget mw;
//    mw.setWindowFlags(Qt::FramelessWindowHint);
//    mw.show();

//    VideoController vc;
//    int res = vc.queryMaxVideoId();
//    qDebug() << res;

//    ViewLogWin *vw = ViewLogWin::getViewLogWin();
//    vw->show();

//    TranscodingWin tw("D:\study\study2\qtworkspace\monitor\project\test\video\videoImg");
//    tw.show();

    return a.exec();
}
