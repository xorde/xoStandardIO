#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <QObject>
#include "ComponentBase.h"
#include <QGamepad>
#include <QGamepadManager>
#include "GlobalConsole.h"

class Gamepad : public ComponentBase
{
    Q_OBJECT

public:
   explicit Gamepad(QObject *parent = nullptr);

private:
    QGamepad *m_gamepad = nullptr;

protected:
    void onCreate();
    void onDestroy();

    QGamepadManager *m_gamepadManager = QGamepadManager::instance();

    xoDouble m_outputAxisLeftXValue = 0;
    xoDouble m_outputAxisLeftYValue = 0;
    xoDouble m_outputAxisRightXValue = 0;
    xoDouble m_outputAxisRightYValue = 0;

    xoBool m_outputButtonAFlag = false;
    xoBool m_outputButtonBFlag = false;
    xoBool m_outputButtonXFlag = false;
    xoBool m_outputButtonYFlag = false;
    xoBool m_outputButtonL1Flag = false;
    xoBool m_outputButtonR1Flag = false;

    xoDouble m_outputButtonL2Value = 0;
    xoDouble m_outputButtonR2Value = 0;

    xoBool m_outputButtonSelectFlag = false;
    xoBool m_outputButtonStartFlag = false;
    xoBool m_outputButtonGuideFlag = false;
    xoBool m_outputButtonCenterFlag = false;

    xoBool m_outputButtonDownFlag = false;
    xoBool m_outputButtonUpFlag = false;
    xoBool m_outputButtonLeftFlag = false;
    xoBool m_outputButtonRightFlag = false;
};

#endif // GAMEPAD_H
