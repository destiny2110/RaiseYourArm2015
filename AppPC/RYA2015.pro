#-------------------------------------------------
#
# Project created by QtCreator 2015-07-16T09:05:31
#
#-------------------------------------------------

QT       += core gui serialport multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = RYA2015
TEMPLATE = app

win32{
CONFIG += link_pkgconfig
PKGCONFIG += opencv
}

#win32{
#INCLUDEPATH += "D:/PIF/OpenCV3.0.0/include"
#INCLUDEPATH += "D:/PIF/OpenCV3.0.0/include/opencv"
#LIBS += -LD:/PIF/OpenCV3.0.0/x86/mingw/lib\
#    -lopencv_core300.dll \
#    -lopencv_features2d300.dll \
#    -lopencv_flann300.dll \
#    -lopencv_hal300 \
#    -lopencv_highgui300.dll \
#    -lopencv_imgcodecs300.dll \
#    -lopencv_imgproc300.dll \
#    -lopencv_ml300.dll \
#    -lopencv_calib3d300.dll \
#    -lopencv_video300.dll \
#    -lopencv_videoio300.dll \
#    -lopencv_photo300.dll

#}
win32{
INCLUDEPATH += "D:/OpenCV/build/include"
INCLUDEPATH += "D:/OpenCV/build/include/opencv"
LIBS += -LD:/OpenCV/build/x86/vc12_separate/lib\
     -opencv_coreasdf330 \
#    -lopencv_features2d330.dll \
#    -lopencv_flann330.dll \
#    -lopencv_hal330 \
#    -lopencv_highgui330.dll \
#    -lopencv_imgcodecs330.dll \
#    -lopencv_imgproc330.dll \
#    -lopencv_ml330.dll \
#    -lopencv_calib3d330.dll \
#    -lopencv_video330.dll \
#    -lopencv_videoio330.dll \
#    -lopencv_photo330.dll

}



SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp\
    hostcomm.cpp \
    aboutus.cpp \
    imagedisplay.cpp \
    imageprocessing.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    console.h\
    hostcomm.h \
    aboutus.h \
    imagedisplay.h \
    imageprocessing.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    console.ui \
    aboutus.ui

RESOURCES += \
    image.qrc

DISTFILES +=
