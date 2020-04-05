#include "ToneGenerator.h"


ToneGenerator::ToneGenerator(QObject* parent) : ToneGeneratorBase(parent)
{
    createSetting("delay",m_delay);
    setName("ToneGenerator");
    description = "Tone generator";
}

void ToneGenerator::onCreate()
{
    m_delayTimer = new QTimer();
    connect(m_delayTimer,&QTimer::timeout,[=]{

        m_delayTimer->stop();
        playTone();
        m_playTimer->start(m_duration);
    });

    m_playTimer = new QTimer();

    connect(m_playTimer,&QTimer::timeout,[=]{
        m_playTimer->stop();
        stop();
        m_delayTimer->start(m_delay);

    });

}

void ToneGenerator::onDestroy()
{
    m_delayTimer->stop();
    m_playTimer->stop();
    stop();
}
void ToneGenerator::objectReceiveEvent(QString name)
{
    if(name == "trigger")
    {
        if(m_trigger)
        {
            playTone();
            if(m_delay)
                m_playTimer->start(m_duration);
        }
        else
        {
            m_delayTimer->stop();
            m_playTimer->stop();
            stop();
        }
    }
}
