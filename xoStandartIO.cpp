#include "xoStandartIO.h"
#include "Keyboard.h"
#include "KeyboardArrows.h"
#include "Mouse.h"
#include "AudioPlayer.h"
#include "ComPortIO.h"
#include "HttpGetRequest.h"
#include "ToneGenerator.h"
#include "Beeper.h"

xoStandartIO::xoStandartIO() : ModuleBaseAppONB("xoStandartIO", "127.0.0.1", "8080")
{
    setIcon(":/images/xoStandartIO.png");
    declareComponent(new Mouse);
    declareComponent(new ToneGenerator);
    declareComponent(new Beeper);

    declareComponent(new AudioPlayer);
    declareComponent(new ComPortIO);
    declareComponent(new HttpGetRequest);


#ifdef Q_OS_WIN
    declareComponent(new Keyboard);
    declareComponent(new KeyboardArrows);
#endif
}
