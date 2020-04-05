#include "Beeper.h"

Beeper::Beeper(QObject* parent) : ToneGeneratorBase(parent)
{   
    setName("Beeper");
    description = "Beeper";
}

void Beeper::onCreate()
{

    m_playTimer = new QTimer();

    connect(m_playTimer,&QTimer::timeout,[=]{
        m_playTimer->stop();
        stop();
    });
}

void Beeper::objectReceiveEvent(QString name)
{
    if(name == "trigger")
    {
        if(m_trigger)
        {
            playTone();
            m_playTimer->start(m_duration);
        }
        else
        {
            m_playTimer->stop();
            stop();
        }
    }
}

void Beeper::onDestroy()
{
    m_playTimer->stop();
    stop();
}
