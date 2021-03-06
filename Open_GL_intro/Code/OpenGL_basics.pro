#-------------------------------------------------
#
# Project created by QtCreator 2017-01-24T12:26:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = OpenGL_basics
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    mainview.cpp \
    user_input.cpp

HEADERS  += mainwindow.h \
    mainview.h \
    vertex.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
