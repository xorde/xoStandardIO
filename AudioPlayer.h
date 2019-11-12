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

    QString m_path = "";
    QString m_pathFromSettings = "";
    bool m_playOnPathChange = true;
    bool m_play = false;

};

#endif // AUDIOPLAYER_H
