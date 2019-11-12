#ifndef COMPORTIO_H
#define COMPORTIO_H

#include <QObject>
#include "ComponentBase.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QString>

class ComPortIO : public ComponentBase
{
    Q_OBJECT
public:
    explicit ComPortIO(QObject *parent = nullptr);

protected:
    int m_portIndex = 1;
    int m_baudRateIndex = 3;
    int m_dataBitsIndex = 3;
    int m_stopBitsIndex = 0;
    int m_parityBitsIndex = 0;
    int m_flowControlIndex = 0;

    //QStringList m_port;
    QString m_port = "COM1";
    QString m_message = "";
    QSerialPort *m_serialPort = nullptr;

    void onCreate();
    void onDestroy();

    void objectChangeEvent(QString name);
    void objectReceiveEvent(QString name);


    QSerialPort::BaudRate m_baudRate = QSerialPort::Baud9600;
    QSerialPort::DataBits m_dataBits = QSerialPort::Data8;
    QSerialPort::StopBits m_stopBits = QSerialPort::OneStop;
    QSerialPort::Parity m_parityBits  = QSerialPort::NoParity;
    QSerialPort::FlowControl m_flowControl  = QSerialPort::NoFlowControl;

    QString getComPortNames();

    void selectComPortNameByIndex();
    void selectBaudRateByIndex(int baudRateIndex);
    void selectDataBitsByIndex(int dataBitsIndex);
    void selectStopBitsByIndex(int stopBitsIndex);
    void selectParityBitsByIndex(int parityBitsIndex);
    void selectFlowControlByIndex(int flowControlIndex);

    void setComPortOptions();

#endif // COMPORTIO_H
};
