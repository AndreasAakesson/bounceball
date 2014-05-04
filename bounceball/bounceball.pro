#-------------------------------------------------
#
# Project created by QtCreator 2014-04-12T16:17:02
#
#-------------------------------------------------
include(gui/gui.pri)
include(engine/engine.pri)
include(entites/entites.pri)
include(helpers/helpers.pri)

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = bounceball
TEMPLATE = app

SOURCES += main.cpp \
    bounceball.cpp

HEADERS  += \
    bounceball.h

FORMS    +=

RESOURCES +=

ICON = placeholder.icns

## levels
levels.files = data/levels/
macx {
    levels.path = Contents/Resources/levels
}
win32 {
    levels.path = levels/
}

## sound
audio.files = data/audio/
macx {
    audio.path = Contents/Resources/audio
}
win32 {
    audio.path = audio/
}

## imgs

QMAKE_BUNDLE_DATA += levels audio

#audio.sources = data/audio/*.wav
#DEPLOYMENT += audio
