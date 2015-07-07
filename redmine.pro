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
    network.h \
    authenticator.h \
    redmine.h \
    redmine_global.h \
    parameter.h \
    types.h \
    converter.h \
    pathing.h \
    including.h \
    typing.h

include(user.pri)
#include(project.pri)
#include(issue.pri)
