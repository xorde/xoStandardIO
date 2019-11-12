#ifndef XOSTANDARTIO_H
#define XOSTANDARTIO_H

#include <QGenericPlugin>
#include "ComponentBase.h"
#include "ModuleBaseAppONB.h"

Q_DECLARE_INTERFACE(ModuleBaseAppONB, "xo.ModuleBaseLibONB/1.0")

class xoStandartIO : public ModuleBaseAppONB
{
    Q_OBJECT
    Q_INTERFACES(ModuleBaseAppONB)
    Q_PLUGIN_METADATA(IID "xorde.Qt.xoPlugin" FILE "xoStandartIO.json")
public:
    xoStandartIO();
};

#endif // XOSTANDARTIO_H
