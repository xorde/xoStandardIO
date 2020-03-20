#include "KeyboardArrows.h"
#include "helpers/GlobalKeyboard.h"

KeyboardArrows::KeyboardArrows(QObject *parent) : ComponentBase ("KeyboardArrows", "Generated triggers on arrow or WASD keys", parent)
{
    setIcon(":/images/gamepad.svg");

    createOutput("Up", m_arrowUp).sampling(0ms);
    createOutput("Down", m_arrowDown).sampling(0ms);
    createOutput("Left", m_arrowLeft).sampling(0ms);
    createOutput("Right", m_arrowRight).sampling(0ms);
    createOutput("Stop", m_arrowRight).sampling(0ms);

    createSetting("AcceptWASD", m_acceptWASD);//.hint("Use WASD keys as well");
    //createSetting("StopKey", m_stopKey)
}

void KeyboardArrows::onCreate()
{
    GlobalKeyboard::Install();
    m_connections << connect(GlobalKeyboard::Instance(), &GlobalKeyboard::keyPressed, [=](unsigned long key)
    {
        auto qkey = GlobalKeyboard::getQKeyIndex(key);
        if (qkey == Qt::Key_Up || (m_acceptWASD && qkey == Qt::Key_W))
        {
            m_arrowUp = true;
            touchOutput("Up", true);
        }
        else if (qkey == Qt::Key_Down || (m_acceptWASD && qkey == Qt::Key_S))
        {
            m_arrowDown = true;
            touchOutput("Down", true);
        }
        else if (qkey == Qt::Key_Left || (m_acceptWASD && qkey == Qt::Key_A))
        {
            m_arrowLeft = true;
            touchOutput("Left", true);
        }
        else if (qkey == Qt::Key_Right || (m_acceptWASD && qkey == Qt::Key_D))
        {
            m_arrowRight = true;
            touchOutput("Right", true);
        }
        else if (qkey == m_stopKey || (m_acceptWASD && qkey == Qt::Key_X))
        {
            m_arrowStop = true;
            touchOutput("Stop", true);
        }
    });

    m_connections << connect(GlobalKeyboard::Instance(), &GlobalKeyboard::keyReleased, [=](unsigned long key)
    {
        auto qkey = GlobalKeyboard::getQKeyIndex(key);
        if (qkey == Qt::Key_Up || (m_acceptWASD && qkey == Qt::Key_W))
        {
            m_arrowUp = false;
            touchOutput("Up", true);
        }
        else if (qkey == Qt::Key_Down || (m_acceptWASD && qkey == Qt::Key_S))
        {
            m_arrowDown = false;
            touchOutput("Down", true);
        }
        else if (qkey == Qt::Key_Left || (m_acceptWASD && qkey == Qt::Key_A))
        {
            m_arrowLeft = false;
            touchOutput("Left", true);
        }
        else if (qkey == Qt::Key_Right || (m_acceptWASD && qkey == Qt::Key_D))
        {
            m_arrowRight = false;
            touchOutput("Right", true);
        }
        else if (qkey == m_stopKey || (m_acceptWASD && qkey == Qt::Key_X))
        {
            m_arrowStop = false;
            touchOutput("Stop", true);
        }
    });
}

void KeyboardArrows::onDestroy()
{
    m_connections.clear();
    GlobalKeyboard::Uninstall();
}
