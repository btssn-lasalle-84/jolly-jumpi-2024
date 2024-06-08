#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include <QtBluetooth>
#include <QString>

#define ENTETE_TRAME_PUPITRE    QString("$JJP")
#define ENTETE_TRAME_SIMULATEUR QString("$JPP")

// choisir
#define ENTETE_TRAME ENTETE_TRAME_SIMULATEUR

#define FIN_TRAME        QString("\n")
#define DELIMITEUR_TRAME QString(",")
#define TYPE_TRAME       1

#define ABANDON      'A'
#define VALIDER      'V'
#define DROITE       'D'
#define GAUCHE       'G'
#define TIR          'T'
#define ACQUITTEMENT 'ACK'

//#define ADRESSE_ESP32_SIMULATEUR QString("08:3a:f2:a8:e3:c2")
#define ESP32_PUPITRE    QString("jumpi-Table")
#define ESP32_SIMULATEUR QString("jolly-jumpi-1")

// choisir
#define ESP32_BLUETOOTH ESP32_SIMULATEUR

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
    void acquittement();
    void abandonPartie();
    void boutonValider();
    void encodeurDroite();
    void encodeurGauche();
    void tirReussi(int numeroTable, int numeroTrou);

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
