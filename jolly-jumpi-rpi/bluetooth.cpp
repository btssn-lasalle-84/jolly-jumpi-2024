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
    if(peripherique.name().startsWith(NOM_ESP32_SIMULATEUR))
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

    if (!trame.startsWith(ENTETE_TRAME) || !trame.endsWith(FIN_TRAME))
    {
        qWarning() << "Trame incorrecte : ";
        return false;
    }
    // Suppression entête et fin
    trame = trame.mid(ENTETE_TRAME.length(), trame.length() - ENTETE_TRAME.length() - FIN_TRAME.length());

    // Séparation éléments trame
    QStringList elements = trame.split(DELIMITEUR_TRAME);

    // Traitement éléments trame
   for (const QString &element : elements)
   {
       if (element.length() != 1)
       {
           qWarning() << "Élément de trame incorrect : " << element;
           continue;
       }
       if (element == QString(ACQUITTEMENT))
       {
           emit acquittement();
       }
       else if (element == QString(ABANDON))
       {
           emit abandonPartie();
       }
       else if (element == QString(VALIDER))
       {
           emit boutonValider();
       }
       else if (element == QString(DROITE))
       {
           emit encodeurDroite();
       }
       else if (element == QString(GAUCHE))
       {
           emit encodeurGauche();
       }
       else if (element.startsWith(TIR))
       {
           emit tirMarque(int numeroTable, int numeroTrou);
       }
       else
           {
               qWarning() << "Trame de tir incorrecte : " << element;
           }
   }
   return true;
}
