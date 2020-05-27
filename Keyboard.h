#ifndef XOKEYBOARD_H
#define XOKEYBOARD_H

#include <QObject>
#include "ComponentBase.h"
#include "helpers/ConnectionHelper.h"

class Keyboard : public ComponentBase
{
    Q_OBJECT
public:
    explicit Keyboard(QObject *parent = nullptr);

protected:
    void onCreate();
    void onDestroy();

private:
    ConnectionHelper m_connections;

    xoInt m_key = 0;
    xoString m_keyText = "";
};

#endif // RANDOMNUMBERGENERATOR_H
