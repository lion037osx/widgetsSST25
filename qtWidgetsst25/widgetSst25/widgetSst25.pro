#-------------------------------------------------
#
# Project created by QtCreator 2017-08-27T01:35:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = widgetSst25
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include ("/home/optimus/Documentos/source_code/qt/qt_libs/qextserialport-1.2rc/src/qextserialport.pri")
