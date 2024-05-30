#include "bluetooth.h"
#include "partie.h"
#include "ihm.h"

#define ADRESSE_ESP32_SIMULATEUR "08:3a:f2:a8:e3:c2"
#define NOM_ESP32_SIMULATEUR     QString("jolly-jumpi-1")

Bluetooth::Bluetooth(QObject* parent) :
    QObject(parent),
    socket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol)),
    agentDecouverteBluetooth(new QBluetoothDeviceDiscoveryAgent),
    abandon(false)
{
    connect(socket, &QBluetoothSocket::connected, this, &Bluetooth::estConnecte);
    connect(socket, &QBluetoothSocket::disconnected, this, &Bluetooth::estDeconnecte);
    connect(socket, &QBluetoothSocket::readyRead, this, &Bluetooth::trameRecue);
    connect(agentDecouverteBluetooth, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &Bluetooth::reconnaitrePeripherique);
}

Bluetooth::~Bluetooth()
{
    delete socket;
    delete agentDecouverteBluetooth;
}

void Bluetooth::initialiserCommunication()
{
}

void Bluetooth::envoyerTrame(const QString &trame)
{
    if (socket->state() == QBluetoothSocket::ConnectedState)
    {
        socket->write(trame.toUtf8());
    }
}

void Bluetooth::lireTrame()
{
    if (socket->canReadLine())
    {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();
        traiterTrame(line);
    }
}

bool Bluetooth::traiterTrame(QString trame)
{
    return true;
}

void Bluetooth::reconnaitrePeripherique(QBluetoothDeviceInfo peripherique)
{
    if (peripherique.address().toString() == ADRESSE_ESP32_SIMULATEUR)
    {
        peripheriqueDistant = peripherique;
        agentDecouverteBluetooth->stop();
        estConnecte();
    }
}

void Bluetooth::estConnecte()
{
    if (socket->state() == QBluetoothSocket::UnconnectedState)
    {
        socket->connectToService(peripheriqueDistant.address(), QBluetoothUuid(QBluetoothUuid::SerialPort));
    }
}

void Bluetooth::estDeconnecte()
{
    emit deconnecte();
}

void Bluetooth::trameRecue()
{
    lireTrame();
}

bool Bluetooth::getAbandon() const
{
    return abandon;
}

void Bluetooth::setAbandon(bool abandon)
{
    this->abandon = abandon;
}
