#ifndef TONEGENERATOR_H
#define TONEGENERATOR_H
#include "ToneGeneratorBase.h"
#include <QObject>


class ToneGenerator : public ToneGeneratorBase
{
    Q_OBJECT
public:
  explicit ToneGenerator(QObject *parent = nullptr);
protected:
    void onCreate() override;
    void onDestroy()override;
    void objectReceiveEvent(QString name) override;
    xoInt m_delay=0;
    QTimer *m_delayTimer = nullptr;
    QTimer *m_playTimer = nullptr;
};

#endif // TONEGENERATOR_H
