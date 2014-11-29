#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T21:43:05
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DTMFtool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    generator.cpp \
    qbuttonextended.cpp \
    dialer.cpp \
    toneplayer.cpp

HEADERS  += mainwindow.h \
    generator.h \
    freqs.h \
    qbuttonextended.h \
    dialer.h \
    toneplayer.h

FORMS    += mainwindow.ui

CONFIG += c++11
