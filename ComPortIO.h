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
    xoInt m_baudRateIndex = 3;
    xoInt m_dataBitsIndex = 3;
    xoInt m_stopBitsIndex = 0;
    xoInt m_parityBitsIndex = 0;
    xoInt m_flowControlIndex = 0;

    QStringList serialPortInfos;
    xoString m_port = "COM1";
    xoByteArray m_messageByteArray;
    xoString m_messageString = "";
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
    void getComPortInfo();

#endif // COMPORTIO_H
};
