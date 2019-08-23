#-------------------------------------------------
#
# Project created by QtCreator 2019-07-17T10:09:52
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoinF
TEMPLATE = app


SOURCES += main.cpp\
        mainscence.cpp \
    mypushbutton.cpp \
    chooselevelscene.cpp \
    playscene.cpp \
    mycoin.cpp \
    dataconfig.cpp

HEADERS  += mainscence.h \
    mypushbutton.h \
    chooselevelscene.h \
    playscene.h \
    mycoin.h \
    dataconfig.h

FORMS    += mainscence.ui

RESOURCES += \
    res.qrc
