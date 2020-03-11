#include "AudioPlayer.h"
#include "GlobalConsole.h"

AudioPlayer::AudioPlayer(QObject *parent) : ComponentBase("AudioPlayer", 0x00411010, "Plays WAV and MP3 files", parent)
{
    setIcon(":/images/music.svg");

    createInput("play", m_play);
    createInput("path", m_path).sampling(0ms);
    createSetting("pathAudio", m_pathFromSettings).opt("{\"specialType\":\"PickFile:*.wav;*.mp3\"}");
    createSetting("playOnPathChange", m_playOnPathChange).def(true);
}

void AudioPlayer::setPath(QString path)
{
    if (!m_player) return;

    stop();

    auto url = QUrl::fromLocalFile(path);
    //qDebug() << "AudioPlayer:" << "New file" << path;
    m_player->setMedia(url);

    if (!QFile::exists(path))
    {
        GlobalConsole::writeLine("Audiofile \""+path+"\" doesn't exist");
    }

    if (m_playOnPathChange)
    {
        play();
    }
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
    if (m_player)
    {
        m_player->stop();
    }
}

void AudioPlayer::pause()
{
    if (m_player)
    {
        m_player->pause();
    }
}

void AudioPlayer::onCreate()
{
     m_player = new QMediaPlayer();
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
        m_pathFromSettings = m_path;
        setPath(m_path);
    }
    else if (name == "pathAudio")
    {
        setPath(m_pathFromSettings);
    }
    else if (name == "play")
    {
        //qDebug() << "Playing" << m_play;
        if (m_play)
        {
            play();
        }
        else
        {
            stop();
        }
    }
}

void AudioPlayer::destruct()
{
    m_connections.clear();

    if (m_player)
    {
        m_player->stop();
        delete m_player;
        m_player = nullptr;
    }

}
