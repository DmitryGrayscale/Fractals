#-------------------------------------------------
#
# Project created by QtCreator 2015-03-19T21:08:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fractals
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fraccantor.cpp \
    serpinskitriangle.cpp \
    fracdragon.cpp \
    fracifs.cpp

HEADERS  += mainwindow.h \
    fraccantor.h \
    serpinskitriangle.h \
    fracdragon.h \
    fracifs.h

FORMS    += mainwindow.ui \
    fraccantor.ui \
    serpinskitriangle.ui \
    fracdragon.ui \
    fracifs.ui

RESOURCES += \
    resources.qrc
