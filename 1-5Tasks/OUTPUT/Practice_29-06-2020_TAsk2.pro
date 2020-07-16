#-------------------------------------------------
#
# Project created by QtCreator 2020-07-04T19:51:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Practice_29-06-2020_TAsk2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += /home/andrew/ch/clickhouse-cpp
LIBS += -L/home/andrew/ch/build/clickhouse -lclickhouse-cpp-lib-static \
        -L/home/andrew/ch/build/contrib/lz4 -llz4-lib \
        -L/home/andrew/ch/build/contrib/cityhash -lcityhash-lib


SOURCES += \
        main.cpp \
        widget.cpp \
    qcustomplot.cpp \
    getvisualfromch.cpp

HEADERS += \
        widget.h \
    qcustomplot.h \
    getvisualfromch.h

FORMS += \
        widget.ui
