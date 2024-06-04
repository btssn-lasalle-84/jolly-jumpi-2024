#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include <QtBluetooth>
#include <QString>

#define ENTETE_TRAME     QString("$JJP")
#define FIN_TRAME        QString("\n")
#define DELIMITEUR_TRAME QString(",")

#define ABANDON 'A'
#define VALIDER 'V'
#define DROITE  'D'
#define GAUCHE  'G'
#define TIR     'T'

#define ESP32_JOLLY_JUMPI QString("jolly-jumpi")

class Bluetooth : public QObject
{
    Q_OBJECT

  public:
    explicit Bluetooth(QObject* parent = nullptr);
    ~Bluetooth();

    void initialiserCommunication();
    void envoyerTrame(const QString& trame);

  signals:
    void connecte();
    void deconnecte();

  private slots:
    void rechercherPeripherique(QBluetoothDeviceInfo peripherique);
    void terminerRecherchePeripherique();
    void connecter();
    void deconnecter();
    void connecterSocket();
    void deconnecterSocket();
    void recevoirTrame();

  private:
    QBluetoothSocket*               socket;
    QBluetoothDeviceDiscoveryAgent* agentDecouverteBluetooth;
    QBluetoothDeviceInfo            peripheriqueDistant;
    QBluetoothLocalDevice           peripheriqueLocal;

    bool traiterTrame(QString trame);
};

#endif // BLUETOOTH_H
