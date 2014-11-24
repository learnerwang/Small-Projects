#-------------------------------------------------
#
# Project created by QtCreator 2012-09-01T12:22:52
#
#-------------------------------------------------

QT       += core gui

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    resource.qrc

LIBS     += -lwsock32
