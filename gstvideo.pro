#-------------------------------------------------
#
# Project created by QtCreator 2015-07-21T20:46:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gstvideo
TEMPLATE = app


SOURCES += main.cpp\
        gstvideo.cpp \
    gstaudio.cpp

HEADERS  += gstvideo.h \
    gstaudio.h

FORMS    += gstvideo.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += gstreamer-1.0
unix: PKGCONFIG += gstreamer-video-1.0
unix: PKGCONFIG += gstreamer-audio-1.0
