#include "ComPortIO.h"
#include "texthelper.h"

static QStringList rates = TextHelper::EnumTextValues<QSerialPort::BaudRate>();
static QStringList databits = TextHelper::EnumTextValues<QSerialPort::DataBits>();
static QStringList stopbits = TextHelper::EnumTextValues<QSerialPort::StopBits>();
static QStringList paritybits = TextHelper::EnumTextValues<QSerialPort::Parity>();
static QStringList flowcontrol = TextHelper::EnumTextValues<QSerialPort::FlowControl>();

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

ComPortIO::ComPortIO(QObject *parent) : ComponentBase ("ComPortIO", "ComPort input/output", parent)
{
    setIcon(":/images/serial-port.svg");

    createSetting("comport", m_port).opt(getComPortNames());
    createSetting("baudrate", m_baudRateIndex).enumeration(rates).def(3);
    createSetting("databits", m_dataBitsIndex).enumeration(databits).def(3);
    createSetting("stopbits", m_stopBitsIndex).enumeration(stopbits).def(0);
    createSetting("paritybits", m_parityBitsIndex).enumeration(paritybits).def(0);
    createSetting("flowcontrol", m_flowControlIndex).enumeration(flowcontrol).def(0);
    createInput("ba_message", m_messageByteArray);
    createInput("str_message", m_messageString);
}

void ComPortIO::onCreate()
{
    m_serialPort = new QSerialPort;
    m_serialPort->setPortName("COM1");
    m_serialPort->open(QIODevice::ReadWrite);
    //setComPortOptions();
    qDebug() << m_serialPort->portName()  << " " << m_baudRate <<" "<< m_dataBits <<" "<< m_stopBits <<" "
             << m_parityBits <<" "<< m_flowControl;
    qDebug() << m_serialPort->isOpen();

}

void ComPortIO::onDestroy()
{
    if(m_serialPort->isOpen()){
        m_serialPort->close();
    }
    delete m_serialPort;
}

void ComPortIO::objectChangeEvent(QString name)
{
    qDebug() << "*****CH*****" << name;
    qDebug() << m_serialPort->portName() << " " << m_baudRate << " " << m_dataBits << " " << m_stopBits << " "
             << m_parityBits << " " << m_flowControl << " " << m_serialPort->isOpen();
    //m_serialPort->open(QIODevice::ReadWrite);
}

void ComPortIO::objectReceiveEvent(QString name)
{
    //qDebug() << name;
    if (name == "ba_message")
    {
        m_serialPort->write(m_messageByteArray);
    }

    else if (name == "str_message")
    {
        m_serialPort->write(m_messageString.toUtf8());
    }

    else if (name == "comport")
    {
        setComPortOptions();
        getComPortInfo();
    }
    else if (name == "baudrate")
    {
        selectBaudRateByIndex(m_baudRateIndex);
        setComPortOptions();
    }
    else if (name == "databits")
    {
        selectDataBitsByIndex(m_dataBitsIndex);
        setComPortOptions();
    }
    else if (name == "stopbits")
    {
        selectStopBitsByIndex(m_stopBitsIndex);
        setComPortOptions();
    }
    else if (name == "paritybits")
    {
        selectParityBitsByIndex(m_parityBitsIndex);
        setComPortOptions();
    }
    else if (name == "flowcontrol")
    {
        selectFlowControlByIndex(m_flowControlIndex);
        setComPortOptions();
    }
}

void ComPortIO::selectBaudRateByIndex(int baudRateIndex)
{
    m_baudRate = TextHelper::EnumFromString<QSerialPort::BaudRate>(rates[baudRateIndex]);
    //qDebug() << "Selected Baudrate:" << m_baudRate;
}

void ComPortIO::selectDataBitsByIndex(int dataBitsIndex){
    m_dataBits = TextHelper::EnumFromString<QSerialPort::DataBits>(databits[dataBitsIndex]);
    //qDebug() << "Selected DataBits" << m_dataBits;
}

void ComPortIO::selectStopBitsByIndex(int stopBitsIndex){
    m_stopBits = TextHelper::EnumFromString<QSerialPort::StopBits>(stopbits[stopBitsIndex]);
    qDebug() << "Selected StopBits" << m_stopBits;
}

void ComPortIO::selectParityBitsByIndex(int parityBitsIndex){
    m_parityBits = TextHelper::EnumFromString<QSerialPort::Parity>(paritybits[parityBitsIndex]);
    qDebug() << "Selected ParityBits" << m_parityBits;
}

void ComPortIO::selectFlowControlByIndex(int flowControlIndex){
    m_flowControl = TextHelper::EnumFromString<QSerialPort::FlowControl>(flowcontrol[flowControlIndex]);
    qDebug() << "Selected FlowControl" << m_flowControl;
}

void ComPortIO::setComPortOptions(){
    if(m_serialPort->isOpen())
    {
        m_serialPort->close();
    }
//  m_serialPort->setPortName("COM" + QString::number(m_portIndex));
    m_serialPort->setPortName(m_port);
    m_serialPort->setBaudRate(m_baudRate);
    m_serialPort->setDataBits(m_dataBits);
    m_serialPort->setParity(m_parityBits);
    m_serialPort->setStopBits(m_stopBits);
    m_serialPort->setFlowControl(m_flowControl);
    m_serialPort->open(QIODevice::ReadWrite);
    if(m_serialPort->isOpen()){
        qDebug() << "It works!!";
    }
}

QString ComPortIO::getComPortNames(){
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    QJsonObject jsonObj;
    QJsonArray jsonArr;

    foreach(QSerialPortInfo str, portList){
        jsonArr.append(str.portName());
    }
    jsonObj["specialType"] = "StringList";
    jsonObj["stringList"] = jsonArr;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);

    return QString(byteArray);
}

void ComPortIO::getComPortInfo()
{
    serialPortInfos.clear();

    QString description;
    QString manufacturer;
    QString serialNumber;

    const auto infos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info: infos)
    {

        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();

        serialPortInfos << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);
    }
}
