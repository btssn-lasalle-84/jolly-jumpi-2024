#include "bluetooth.h"
#include <QDebug>

Bluetooth::Bluetooth(QObject* parent) :
    QObject(parent), socket(nullptr),
    agentDecouverteBluetooth(new QBluetoothDeviceDiscoveryAgent(this))
{
}

Bluetooth::~Bluetooth()
{
    if(socket != nullptr && socket->state() == QBluetoothSocket::ConnectedState)
    {
        deconnecter();
    }
}

void Bluetooth::initialiserCommunication()
{
    // Bluetooth activé ?
    if(!peripheriqueLocal.isValid())
        return;

    connect(agentDecouverteBluetooth,
            &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this,
            &Bluetooth::rechercherPeripherique);
    connect(agentDecouverteBluetooth,
            &QBluetoothDeviceDiscoveryAgent::finished,
            this,
            &Bluetooth::terminerRecherchePeripherique);
    agentDecouverteBluetooth->start();
}

void Bluetooth::envoyerTrame(const QString& trame)
{
    if(socket != nullptr && socket->state() == QBluetoothSocket::ConnectedState)
    {
        socket->write(trame.toLatin1());
    }
}

void Bluetooth::rechercherPeripherique(QBluetoothDeviceInfo peripherique)
{
    if(peripherique.name().startsWith(ESP32_JOLLY_JUMPI))
    {
        qDebug() << Q_FUNC_INFO << peripherique.name() << peripherique.address().toString();
        peripheriqueDistant = peripherique;
        terminerRecherchePeripherique();
        connecter();
    }
}

void Bluetooth::terminerRecherchePeripherique()
{
    qDebug() << Q_FUNC_INFO;
    agentDecouverteBluetooth->stop();
    disconnect(agentDecouverteBluetooth,
               &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
               this,
               &Bluetooth::rechercherPeripherique);
}

void Bluetooth::connecter()
{
    if(socket == nullptr)
    {
        socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        if(socket != nullptr)
        {
            connect(socket, SIGNAL(connected()), this, SLOT(connecterSocket()));
            connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecterSocket()));
            connect(socket, SIGNAL(readyRead()), this, SLOT(recevoirTrame()));

            socket->connectToService(peripheriqueDistant.address(),
                                     QBluetoothUuid(QBluetoothUuid::SerialPort));
            socket->open(QIODevice::ReadWrite);
            qDebug() << Q_FUNC_INFO << peripheriqueDistant.name()
                     << peripheriqueDistant.address().toString();
        }
    }
}

void Bluetooth::deconnecter()
{
    if(socket->state() == QBluetoothSocket::ConnectedState)
    {
        socket->close();
        delete socket;
        socket = nullptr;
    }
}

void Bluetooth::connecterSocket()
{
    qDebug() << Q_FUNC_INFO << peripheriqueDistant.name()
             << peripheriqueDistant.address().toString();
    emit connecte();
}

void Bluetooth::deconnecterSocket()
{
    qDebug() << Q_FUNC_INFO << peripheriqueDistant.name()
             << peripheriqueDistant.address().toString();
    emit deconnecte();
}

void Bluetooth::recevoirTrame()
{
    if(socket->canReadLine())
    {
        QString trame = QString::fromUtf8(socket->readLine()).trimmed();
        traiterTrame(trame);
    }
}

bool Bluetooth::traiterTrame(QString trame)
{
    qDebug() << Q_FUNC_INFO << "trame" << trame;
    // @todo traiter la trame et emettre les signaux correspondants
    return true;
}
