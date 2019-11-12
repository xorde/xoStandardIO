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

    bool m_acceptWASD = false;
    int m_stopKey = Qt::Key_X;

    bool m_arrowUp = false;
    bool m_arrowDown = false;
    bool m_arrowLeft = false;
    bool m_arrowRight = false;
    bool m_arrowStop = false;
};

#endif // KEYBOARDARROWS_H
