#ifndef XOMOUSE_H
#define XOMOUSE_H

#include "ComponentBase.h"
#include "helpers/ConnectionHelper.h"

class Mouse : public ComponentBase
{
    Q_OBJECT
public:
    explicit Mouse(QObject *parent = nullptr);

protected:
    void onCreate();
    void onDestroy();

    void objectRequestEvent(QString name);
    void objectReceiveEvent(QString name);

    ConnectionHelper m_connections;

    xoFloat m_inputX = 0;
    xoFloat m_inputY = 0;

    xoFloat m_x = 0;
    xoFloat m_y = 0;
};

#endif // MOUSE_H
