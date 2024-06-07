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

    trame += "\n";
    if(!trame.startsWith(ENTETE_TRAME) || !trame.endsWith(FIN_TRAME))
    {
        qWarning() << "Trame incorrecte !";
        return false;
    }

    // Suppression entête et fin
    trame =
      trame.mid(ENTETE_TRAME.length(), trame.length() - ENTETE_TRAME.length() - FIN_TRAME.length());

    // Séparation éléments trame
    QStringList elements = trame.split(DELIMITEUR_TRAME);
    qDebug() << Q_FUNC_INFO << "elements" << elements;

    // Traitement éléments trame
    if(elements[TYPE_TRAME].isEmpty())
    {
        qWarning() << "Type de trame manquant";
        return false;
    }
    if(elements[TYPE_TRAME] == QString(ACQUITTEMENT))
    {
        qDebug() << Q_FUNC_INFO << "trame ACK";
        emit acquittement();
    }
    else if(elements[TYPE_TRAME] == QString(ABANDON))
    {
        qDebug() << Q_FUNC_INFO << "trame A";
        emit abandonPartie();
    }
    else if(elements[TYPE_TRAME] == QString(VALIDER))
    {
        qDebug() << Q_FUNC_INFO << "trame V";
        emit boutonValider();
    }
    else if(elements[TYPE_TRAME] == QString(DROITE))
    {
        qDebug() << Q_FUNC_INFO << "trame D";
        emit encodeurDroite();
    }
    else if(elements[TYPE_TRAME] == QString(GAUCHE))
    {
        qDebug() << Q_FUNC_INFO << "trame G";
        emit encodeurGauche();
    }
    else if(elements[TYPE_TRAME] == QString(TIR))
    {
        if(elements.count() == 4)
        {
            qDebug() << Q_FUNC_INFO << "trame T"
                     << "numeroTable" << elements[2].toInt() << "numeroTrou" << elements[3].toInt();
            emit tirReussi(elements[2].toInt(), elements[3].toInt());
        }
    }
    else
    {
        qWarning() << "Type de trame inconnu" << elements[TYPE_TRAME];
        return false;
    }

    return true;
}
