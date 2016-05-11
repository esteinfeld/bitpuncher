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
    exportwizard.cpp

HEADERS  += mainwindow.h \
    bitmapcanvas.h \
    newpaintdialog.h \
    exportwizard.h

FORMS    += mainwindow.ui \
    newpaintdialog.ui

ICON = bitpuncher.icns
RC_FILE = bitpuncher.rc
