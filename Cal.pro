#-------------------------------------------------
#
# Project created by QtCreator 2019-11-28T04:34:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cal
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    user_manager.cpp \
    user.cpp \
    user_factory.cpp \
    event.cpp \
    event_factory.cpp \
    authenticator.cpp \
    event_manager.cpp \
    control.cpp \
    timetable.cpp \
    timetable_factory.cpp \
    timetable_manager.cpp

HEADERS  += mainwindow.h \
    user_manager.h \
    user.h \
    user_factory.h \
    event.h \
    event_factory.h \
    authenticator.h \
    event_manager.h \
    control.h \
    timetable.h \
    timetable_factory.h \
    timetable_manager.h

FORMS    += mainwindow.ui
