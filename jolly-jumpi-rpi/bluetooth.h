#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include <QtBluetooth>
#include <QString>

#define ENTETE_TRAME     QString("$JPP")
#define FIN_TRAME        QString("\n")
#define DELIMITEUR_TRAME QString(",")
#define TYPE_TRAME       1

#define ABANDON      'A'
#define VALIDER      'V'
#define DROITE       'D'
#define GAUCHE       'G'
#define TIR          'T'
#define ACQUITTEMENT 'ACK'

#define ADRESSE_ESP32_SIMULATEUR QString("08:3a:f2:a8:e3:c2")
#define NOM_ESP32_SIMULATEUR     QString("jolly-jumpi-1")

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
