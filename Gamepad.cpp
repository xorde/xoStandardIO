#include "Gamepad.h"

Gamepad::Gamepad(QObject *parent) : ComponentBase("Gamepad", "Gamepad for control", parent)
{
    setIcon(":/images/gamepad-square.svg");

    createOutput("axis_left_X", m_outputAxisLeftXValue);
    createOutput("axis_left_Y", m_outputAxisLeftYValue);
    createOutput("axis_right_X", m_outputAxisRightXValue);
    createOutput("axis_right_Y", m_outputAxisRightYValue);

    createOutput("button_A", m_outputButtonAFlag);
    createOutput("button_B", m_outputButtonBFlag);
    createOutput("button_X", m_outputButtonXFlag);
    createOutput("button_Y", m_outputButtonYFlag);
    createOutput("button_L1", m_outputButtonL1Flag);
    createOutput("button_R1", m_outputButtonR1Flag);

    createOutput("button_L2", m_outputButtonL2Value);
    createOutput("button_R2", m_outputButtonR2Value);

    createOutput("button_Select", m_outputButtonSelectFlag);
    createOutput("button_Start", m_outputButtonStartFlag);
    createOutput("button_Guide", m_outputButtonGuideFlag);
    createOutput("button_Center", m_outputButtonCenterFlag);

    createOutput("button_Up", m_outputButtonUpFlag);
    createOutput("button_Down", m_outputButtonDownFlag);
    createOutput("button_Left", m_outputButtonLeftFlag);
    createOutput("button_Right", m_outputButtonRightFlag);
}

void Gamepad::onCreate()
{
    QList<int> gamepads;
    do
    {
        gamepads = m_gamepadManager->connectedGamepads();
    }
    while(QGamepadManager::instance()->connectedGamepads().isEmpty());

    GlobalConsole::writeItem("I AM HERE");

//    if (gamepads.isEmpty()) {
//        qDebug() << "Did not find any connected gamepads";
//        return;
//    }
//    else{
//        qDebug() << "!!!Connected: " << gamepads;
//    }

    m_gamepad = new QGamepad;

    connect(m_gamepad, &QGamepad::axisLeftXChanged, [=](xoDouble value){
          GlobalConsole::writeItem("Left X");
          m_outputAxisLeftXValue = value;
    });
    connect(m_gamepad, &QGamepad::axisLeftYChanged, this, [=](xoDouble value){
        GlobalConsole::writeItem("Left Y");
        m_outputAxisLeftYValue = value;
    });
    connect(m_gamepad, &QGamepad::axisRightXChanged, this, [=](xoDouble value){
        GlobalConsole::writeItem("Right X");
        m_outputAxisRightXValue = value;
    });
    connect(m_gamepad, &QGamepad::axisRightYChanged, this, [=](xoDouble value){
        GlobalConsole::writeItem("Right Y");
        m_outputAxisRightYValue = value;
    });
    connect(m_gamepad, &QGamepad::buttonAChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button A");
        m_outputButtonAFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonBChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button B");
        m_outputButtonBFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonXChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button X");
        m_outputButtonXFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonYChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button Y");
        m_outputButtonYFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonL1Changed, this, [=](xoBool pressed){
       GlobalConsole::writeItem("Button L1");
       m_outputButtonL1Flag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonR1Changed, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button R1");
        m_outputButtonR1Flag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonL2Changed, this, [=](xoDouble value){
        GlobalConsole::writeItem("Button L2");
        m_outputButtonL2Value = value;
    });
    connect(m_gamepad, &QGamepad::buttonR2Changed, this, [=](xoDouble value){
        GlobalConsole::writeItem("Button R2");
        m_outputButtonR2Value = value;
    });
    connect(m_gamepad, &QGamepad::buttonSelectChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button Select");
        m_outputButtonSelectFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonStartChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button Start");
        m_outputButtonStartFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonGuideChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button Guide");
        m_outputButtonGuideFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonDownChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button Down");
        m_outputButtonDownFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonUpChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button Up");
        m_outputButtonUpFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonLeftChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button Left");
        m_outputButtonLeftFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonRightChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button Right");
        m_outputButtonRightFlag = pressed;
    });
    connect(m_gamepad, &QGamepad::buttonCenterChanged, this, [=](xoBool pressed){
        GlobalConsole::writeItem("Button Center");
        m_outputButtonCenterFlag = pressed;
    });
}

void Gamepad::onDestroy()
{
    delete m_gamepad;
}
