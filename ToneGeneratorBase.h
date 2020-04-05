#ifndef TONEGENERATORBASE_H
#define TONEGENERATORBASE_H

#include "ComponentBase.h"
#include <QAudioDeviceInfo>
#include <QAudioOutput>

class ToneGeneratorBase : public ComponentBase
{
     Q_OBJECT
public:
   explicit ToneGeneratorBase(QObject *parent = nullptr);
protected:
    QAudioOutput *m_audio = nullptr;
    QIODevice *outDevice;
    void playTone();
    float m_volume =50;
    float m_freq = 440;
    int m_duration =500;
    bool m_trigger = false;
    void stop();

     int mTime;

private slots:
    void playbackNotify();



};

#endif // TONEGENERATORBASE_H
