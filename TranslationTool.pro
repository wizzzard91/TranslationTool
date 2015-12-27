#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T21:15:12
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TranslationTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    originalwidget.cpp \
    translationwidget.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    originalwidget.h \
    translationwidget.h \
    utils.hpp

FORMS    += mainwindow.ui \
    originalwidget.ui \
    translationwidget.ui
