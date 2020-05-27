#ifndef KEYBOARDARROWS_H
#define KEYBOARDARROWS_H

#include <QObject>
#include "ComponentBase.h"
#include "helpers/ConnectionHelper.h"

class KeyboardArrows : public ComponentBase
{
    Q_OBJECT
public:
    explicit KeyboardArrows(QObject *parent = nullptr);

protected:

    void onCreate() override;
    void onDestroy() override;

    ConnectionHelper m_connections;

    xoBool m_acceptWASD = false;
    int m_stopKey = Qt::Key_X;

    xoBool m_arrowUp = false;
    xoBool m_arrowDown = false;
    xoBool m_arrowLeft = false;
    xoBool m_arrowRight = false;
    xoBool m_arrowStop = false;
};

#endif // KEYBOARDARROWS_H
