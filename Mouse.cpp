#include "Mouse.h"
#include "globalhelper.h"
#include <QCursor>

Mouse::Mouse(QObject *parent) : ComponentBase ("Mouse", "Provides and sets cursor position",parent)
{
    setIcon(":/images/mouse.svg");

    createOutput("x", m_x).sampling(10ms);
    createOutput("y", m_y).sampling(10ms);

    //createOutput("mouseDown", m_mouseDown);

    createInput("input_x", m_inputX);
    createInput("input_y", m_inputY);
}

void Mouse::onCreate()
{

}

void Mouse::onDestroy()
{
    m_connections.clear();
}

void Mouse::objectRequestEvent(QString name)
{
    if (name == "x") m_x = QCursor::pos().x();
    else if (name == "y") m_y = QCursor::pos().y();
}

void Mouse::objectReceiveEvent(QString name)
{
    if(name == "input_x")
    {
        QCursor::setPos(m_inputX,  QCursor::pos().y());
    }
    else if(name == "input_y")
    {
        QCursor::setPos(QCursor::pos().x(), m_inputY);
    }
}

