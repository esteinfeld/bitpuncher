#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T17:48:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bitpuncher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bitmapcanvas.cpp \
    newpaintdialog.cpp \
    exportdialog.cpp

HEADERS  += mainwindow.h \
    bitmapcanvas.h \
    newpaintdialog.h \
    exportdialog.h

FORMS    += mainwindow.ui \
    newpaintdialog.ui \
    exportdialog.ui
