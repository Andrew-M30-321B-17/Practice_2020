#-------------------------------------------------
#
# Project created by QtCreator 2020-07-01T01:17:13
#
#-------------------------------------------------

QT       += core gui \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Practice_29-06-2020
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

INCLUDEPATH += /home/andrew/ch/clickhouse-cpp \
               /home/andrew/paho.mqtt.c/src
LIBS += -L/home/andrew/ch/build/clickhouse -lclickhouse-cpp-lib-static \
        -L/home/andrew/ch/build/contrib/lz4 -llz4-lib \
        -L/home/andrew/ch/build/contrib/cityhash -lcityhash-lib

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    condition.cpp \
    thcl.cpp
HEADERS += \
        mainwindow.h \
    condition.h \
    thcl.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    createBD.py \
    myscript.py \
    mqttGetData.py \
    setDataToBDFromMqtt.py
