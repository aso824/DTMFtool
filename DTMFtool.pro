#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T21:43:05
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DTMFtool
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
		src/generator.cpp \
		src/qbuttonextended.cpp \
		src/dialer.cpp \
		src/toneplayer.cpp

HEADERS  += include/mainwindow.h \
		include/generator.h \
		include/freqs.h \
                qbuttonextended.h \
		include/dialer.h \
		include/toneplayer.h

FORMS    += mainwindow.ui

CONFIG += c++11
