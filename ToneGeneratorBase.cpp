#include "ToneGeneratorBase.h"
#define SAMPLE_FREQ     40000
#define AUDIO_BUF_MS    30

ToneGeneratorBase::ToneGeneratorBase(QObject *parent) : ComponentBase(parent)
{
    QAudioFormat format;
    format.setSampleRate(SAMPLE_FREQ);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultOutputDevice();
    if (!info.isFormatSupported(format))
    {
        qWarning() << "bad format, but pofig";
        format = info.nearestFormat(format);
    }

    m_audio = new QAudioOutput(format, this);
    m_audio->setNotifyInterval(AUDIO_BUF_MS);
    connect(m_audio, SIGNAL(notify()), this, SLOT(playbackNotify()));
    connect(m_audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(stateChanged(QAudio::State)));

    m_audio->setBufferSize(SAMPLE_FREQ);
    createSetting("volume",m_volume);
    createSetting("freq",m_freq);
    createSetting("duration",m_duration);
    createInput("trigger",m_trigger);
}



void ToneGeneratorBase::playbackNotify()
{
    QByteArray ba;
    int Ncnt = SAMPLE_FREQ*AUDIO_BUF_MS / 1000;
    for (int i=0; i<Ncnt; i++, mTime++)
    {
        float y = 0;
        if (m_freq > 0)
            y = (32768 * m_volume/100) * sinf(2*(3.1415)*mTime*m_freq/SAMPLE_FREQ);
        signed short sample = lrintf(y);
        ba.append(reinterpret_cast<const char*>(&sample), 2);
    }
    if (outDevice)
        outDevice->write(ba);
}

void ToneGeneratorBase::playTone()
{
    outDevice = m_audio->start();
    // fucking hack (fill double buffer):
    for (int i=0; i<2; i++)
        playbackNotify();

}
void ToneGeneratorBase::stop()
{
    m_audio->stop();
    outDevice = nullptr;
}
