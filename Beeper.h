#ifndef BEEPER_H
#define BEEPER_H

#include "ToneGeneratorBase.h"

class Beeper : public ToneGeneratorBase
{
    Q_OBJECT
public:
    Beeper(QObject *parent = nullptr);
protected:
    void onCreate() override;
    void onDestroy()override;
    void objectReceiveEvent(QString name) override;
    QTimer *m_playTimer = nullptr;
};

#endif // BEEPER_H
