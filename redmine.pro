QT       += network xml
QT       -= gui

TARGET = qtredmine
TEMPLATE = lib

DEFINES += REDMINEQT_LIBRARY

SOURCES += \
    sender.cpp \
    network.cpp \
    authenticator.cpp \
    redmine.cpp

HEADERS += \
    sender.h \
    user.h \
    network.h \
    authenticator.h \
    redmine.h \
    redmine_global.h

