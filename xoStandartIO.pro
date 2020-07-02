QT    *= core widgets multimedia serialport
TARGET = xoStandartIO
TEMPLATE = app

include("../../xoTools/Application.pri")
include("../../../NeuroboticsToolkit/NTSubFolder.pri")
win32: {
#QMAKE_POST_LINK += xcopy /Y $$shell_path($${DESTDIR}/../../NeuroboticsToolkit.CV$${SUFFIX}$${XO_TOOLS_EXTENSION}) $$shell_path($${DESTDIR}/) &
QMAKE_POST_LINK += xcopy /Y $$shell_path($${DESTDIR}/../../NeuroboticsToolkit$${SUFFIX}$${XO_TOOLS_EXTENSION}) $$shell_path($${DESTDIR}/) &
#QMAKE_POST_LINK += windeployqt $${DESTDIR}/NeuroboticsToolkit.CV$${SUFFIX}$${XO_TOOLS_EXTENSION} &
QMAKE_POST_LINK += windeployqt $${DESTDIR}/NeuroboticsToolkit$${SUFFIX}$${XO_TOOLS_EXTENSION} &
}

SOURCES += \
    AudioPlayer.cpp \
    Beeper.cpp \
    ComPortIO.cpp \
    HttpGetRequest.cpp \
    Mouse.cpp   \
    ToneGenerator.cpp \
    ToneGeneratorBase.cpp \
#    Engine.cpp \
    main.cpp \
    xoStandartIO.cpp

HEADERS += \
    AudioPlayer.h \
    Beeper.h \
    ComPortIO.h \
    HttpGetRequest.h \
    Mouse.h \
    ToneGenerator.h \
    ToneGeneratorBase.h \
#    Engine.h \
    xoStandartIO.h


win32: {
include("../../../NeuroboticsToolkit/User32.pri")
SOURCES += \
      Keyboard.cpp \
      KeyboardArrows.cpp \

HEADERS += \
    Keyboard.h \
    KeyboardArrows.h \

RC_ICONS += images/xoStandartIO.ico
}



DISTFILES += xoStandartIO.json

unix { target.path = /usr/lib
    INSTALLS += target }

#QMAKE_POST_LINK += mkdir $$shell_path($${DESTDIR}) &
#DESTDIR = $$join(DESTDIR,,,/xoStandartIO)

RESOURCES += \
    xostandartio.qrc
