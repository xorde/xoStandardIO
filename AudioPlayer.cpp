#include "AudioPlayer.h"
#include "GlobalConsole.h"

AudioPlayer::AudioPlayer(QObject *parent) : ComponentBase("AudioPlayer", "Plays WAV and MP3 files", parent)
{
    setIcon(":/images/music.svg");

    createInput("play", m_play);
    createInput("path", m_path).sampling(0ms);
    createInput("audiobytes", audiobytes).sampling(0ms);

    createOutput("volume", volume).def(0).sampling(0ms);

    createSetting("pathAudio", m_pathFromSettings).opt("{\"specialType\":\"PickFile:*.wav;*.mp3\"}");
    createSetting("playOnPathChange", m_playOnPathChange).def(true);
}

void AudioPlayer::setPath(QString path)
{
    if (!m_player) return;

    stop();

    m_player->setMedia(QUrl::fromLocalFile(path));

    if (!QFile::exists(path)) GlobalConsole::writeLine("Audiofile \""+path+"\" doesn't exist");

    if (m_playOnPathChange) play();
}

void AudioPlayer::play()
{
    if (m_player)
    {
        m_player->setPosition(0);
        m_player->play();
    }
}

void AudioPlayer::stop()
{
    if (m_player) m_player->stop();
}

void AudioPlayer::pause()
{
    if (m_player) m_player->pause();
}

void AudioPlayer::onCreate()
{
    m_player = new QMediaPlayer();

    probe = new QAudioProbe(this);
    probe->setSource(m_player);

    connect(probe, &QAudioProbe::audioBufferProbed, this, [=](const QAudioBuffer &buffer)
    {
        int length = buffer.byteCount();
        qreal peakLevel = 0.0;

        const char *ptr = buffer.constData<char>();
        const char *const end = ptr + length;
        while (ptr < end)
        {
            const qint16 value = *reinterpret_cast<const qint16*>(ptr);
            const qreal fracValue = qreal(value) / 32768;
            peakLevel = qMax(peakLevel, fracValue);
            ptr += 2;
        }

        volume = peakLevel;
    });
}

void AudioPlayer::onDestroy()
{
    destruct();
}

void AudioPlayer::objectReceiveEvent(QString name)
{
    qDebug() << "Audio receive" << name;
    if (name == "path")
    {
        m_pathFromSettings = m_path.value();
        setPath(m_path);
    }
    else if(name == "audiobytes")
    {
        static int sas = 0;
        GlobalConsole::writeLine(QString::number(++sas));

        playerBuffer.close();
        playerBuffer.setData(audiobytes);

        m_player->setMedia(QMediaContent(), &playerBuffer);
        m_player->play();
    }
    else if (name == "pathAudio")
    {
        setPath(m_pathFromSettings);
    }
    else if (name == "play")
    {
        m_play ? play() : stop();
    }
}

void AudioPlayer::destruct()
{
    if (m_player)
    {
        m_player->stop();
        delete m_player;
        m_player = nullptr;
    }

}
