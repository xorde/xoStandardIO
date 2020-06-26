#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "ComponentBase.h"
#include <QMediaPlayer>
#include "helpers/ConnectionHelper.h"

class AudioPlayer : public ComponentBase
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = nullptr);

    void setPath(QString path);
    void play();
    void stop();
    void pause();

protected:
    void onCreate() override;
    void onDestroy() override;

    void objectReceiveEvent(QString name) override;

    void destruct();

    QMediaPlayer *m_player = nullptr;
    ConnectionHelper m_connections;

    xoByteArray audiobytes;
    xoString m_path = QString("");
    xoString m_pathFromSettings = QString("");
    xoBool m_playOnPathChange = true;
    xoBool m_play = false;

};

#endif // AUDIOPLAYER_H
