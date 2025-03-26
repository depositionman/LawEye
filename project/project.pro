#-------------------------------------------------
#
# Project created by QtCreator 2024-08-15T20:37:32
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    util/sqliteutil.cpp \
    view/graphicsview.cpp \
    view/graphicsitem.cpp \
    view/mainwidget.cpp \
    mywidget/closewidget.cpp \
    util/mydecord.cpp \
    thread/videothread.cpp \
    mywidget/loginwidget.cpp \
    mywidget/bubblebutton.cpp \
    mywidget/systemsetwidget.cpp \
    mywidget/transcodewidget.cpp \
    mywidget/photowidget.cpp \
    mywidget/videoreplaywidget.cpp \
    mywidget/localphotowidget.cpp \
    mywidget/checklogwidget.cpp \
    view/systemsettingswin.cpp \
    mywidget/shadowlabel.cpp \
    model/equipmentmodel.cpp \
    controller/equipmentcontroller.cpp \
    data/equipment.cpp \
    view/loginwin.cpp \
    mywidget/verify.cpp \
    model/policemodel.cpp \
    data/police.cpp \
    controller/policecontroller.cpp \
    data/setting.cpp \
    model/settingmodel.cpp \
    controller/settingcontroller.cpp \
    data/videoqueue.cpp \
    thread/playbackthread.cpp \
    util/encoding.cpp \
    view/lookphotowin.cpp \
    model/videomodel.cpp \
    controller/videocontroller.cpp \
    model/photomodel.cpp \
    controller/photocontroller.cpp \
    data/photo.cpp \
    data/showpicture.cpp \
    view/lookvideowin.cpp \
    data/video.cpp \
    data/showvideo.cpp \
    view/playbackwin.cpp \
    thread/playvideothread.cpp \
    mywidget/mycombox.cpp \
    mywidget/playicon.cpp \
    util/videodecord.cpp \
    view/viewlogwin.cpp \
    data/log.cpp \
    model/logmodel.cpp \
    controller/logcontroller.cpp \
    view/transcodingwin.cpp \
    util/trancetonormalvideofile.cpp \
    mywidget/noticelabel.cpp

HEADERS += \
    util/sqliteutil.h \
    view/graphicsview.h \
    view/graphicsitem.h \
    view/mainwidget.h \
    mywidget/closewidget.h \
    util/mydecord.h \
    thread/videothread.h \
    mywidget/loginwidget.h \
    mywidget/bubblebutton.h \
    mywidget/systemsetwidget.h \
    mywidget/transcodewidget.h \
    mywidget/photowidget.h \
    mywidget/videoreplaywidget.h \
    mywidget/localphotowidget.h \
    mywidget/checklogwidget.h \
    view/systemsettingswin.h \
    mywidget/shadowlabel.h \
    model/equipmentmodel.h \
    controller/equipmentcontroller.h \
    data/equipment.h \
    view/loginwin.h \
    mywidget/verify.h \
    model/policemodel.h \
    data/police.h \
    controller/policecontroller.h \
    data/setting.h \
    model/settingmodel.h \
    controller/settingcontroller.h \
    data/videoqueue.h \
    thread/playbackthread.h \
    util/encoding.h \
    view/lookphotowin.h \
    model/videomodel.h \
    controller/videocontroller.h \
    model/photomodel.h \
    controller/photocontroller.h \
    data/photo.h \
    data/showpicture.h \
    view/lookvideowin.h \
    data/video.h \
    data/showvideo.h \
    view/playbackwin.h \
    thread/playvideothread.h \
    mywidget/mycombox.h \
    mywidget/playicon.h \
    util/videodecord.h \
    view/viewlogwin.h \
    data/log.h \
    model/logmodel.h \
    controller/logcontroller.h \
    view/transcodingwin.h \
    util/trancetonormalvideofile.h \
    mywidget/noticelabel.h

#配置目标文件夹,最终编译的程序会放在这个目录
DESTDIR+=bin    # 目标文件生成位置
#配置库文件路径（api路径）
LIBS += $$PWD/lib/sqlite3.lib \             #sqlite3依赖
        $$PWD/ffmpeglib/lib/avcodec.lib \
        $$PWD/ffmpeglib/lib/avdevice.lib \
        $$PWD/ffmpeglib/lib/avfilter.lib \
        $$PWD/ffmpeglib/lib/avformat.lib \
        $$PWD/ffmpeglib/lib/avutil.lib \
        $$PWD/ffmpeglib/lib/swresample.lib \
        $$PWD/ffmpeglib/lib/swscale.lib \

INCLUDEPATH += $$PWD/ffmpeglib/include      #头文件路径

RESOURCES += \
    resource.qrc
