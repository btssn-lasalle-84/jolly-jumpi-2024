#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include <QBluetoothSocket>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceInfo>
#include <QBluetoothUuid>
#include <QBluetoothDeviceInfo>
#include <QString>

class Bluetooth : public QObject
{
    Q_OBJECT

public:
    explicit Bluetooth(QObject* parent = nullptr);
    ~Bluetooth();

    void initialiserCommunication();
    void envoyerTrame(const QString &trame);
    bool getAbandon() const;
    void setAbandon(bool abandon);

signals:
    void deconnecte();

private slots:
    void reconnaitrePeripherique(QBluetoothDeviceInfo peripherique);
    void estConnecte();
    void estDeconnecte();
    void trameRecue();

private:
    void lireTrame();
    bool traiterTrame(QString trame);

    QBluetoothSocket* socket;
    QBluetoothDeviceDiscoveryAgent* agentDecouverteBluetooth;
    QBluetoothDeviceInfo peripheriqueDistant;
    bool abandon;
};

#endif // BLUETOOTH_H
