QT       += core

QT       -= gui

TARGET = philosopheQT
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    threadphilo.cpp

HEADERS += \
    threadphilo.h
