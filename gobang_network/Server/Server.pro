#-------------------------------------------------
#
# Project created by QtCreator 2012-09-01T09:47:20
#
#-------------------------------------------------

QT       += core gui

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS     += -lwsock32

RESOURCES += \
    resource.qrc
