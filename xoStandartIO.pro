QT    *= core widgets multimedia serialport
TARGET = xoStandartIO

include("../../xoTools/Plugin.pri")
include("../../../NeuroboticsToolkit/NTSubFolder.pri")

SOURCES += \
    AudioPlayer.cpp \
    ComPortIO.cpp \
    HttpGetRequest.cpp \
    Mouse.cpp   \
    xoStandartIO.cpp

HEADERS += \
    AudioPlayer.h \
    ComPortIO.h \
    HttpGetRequest.h \
    Mouse.h \
    xoStandartIO.h


win32: {
include("../../../NeuroboticsToolkit/User32.pri")
SOURCES += \
      Keyboard.cpp \
      KeyboardArrows.cpp \

HEADERS += \
    Keyboard.h \
    KeyboardArrows.h \
}



DISTFILES += xoStandartIO.json \
    xoStandartIO.json

unix { target.path = /usr/lib
    INSTALLS += target }

QMAKE_POST_LINK += mkdir $$shell_path($${DESTDIR}) &
DESTDIR = $$join(DESTDIR,,,/xoStandartIO)

RESOURCES += \
    xostandartio.qrc
