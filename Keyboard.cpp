#include "Keyboard.h"
#include "globalhelper.h"
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QElapsedTimer>
#include "helpers/GlobalKeyboard.h"
#include "texthelper.h"

Keyboard::Keyboard(QObject *parent) : ComponentBase("Keyboard", "Triggered by keyboard button press events", parent)
{
    setIcon(":/images/keyboard.svg");
    version = 1;

    createOutput("key", m_key).sampling(0ms);
    createOutput("keyText", m_keyText).sampling(0ms);
}

void Keyboard::onCreate()
{
    GlobalKeyboard::Install();
    m_connections << connect(GlobalKeyboard::Instance(), &GlobalKeyboard::keyPressed,[=](unsigned long key)
    {
        m_key = GlobalKeyboard::getQKeyIndex(key);
//        touchOutput("key", true);

        if (m_key > 0)
        {
            m_keyText = TextHelper::EnumToString((Qt::Key)m_key.value()).replace("Key_", "").toLower();
//            touchOutput("keyText", true);
            log(m_keyText);
        }
    });
}

void Keyboard::onDestroy()
{
    GlobalKeyboard::Uninstall();
    m_connections.clear();
}

