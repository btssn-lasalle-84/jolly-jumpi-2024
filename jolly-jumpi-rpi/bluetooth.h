#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QString>

#define ENTETE_TRAME     QString("$JJP")
#define FIN_TRAME        QString("\n")
#define DELIMITEUR_TRAME QString(",")

#define ABANDONER    'A'
#define VALIDER      'V'
#define DROITE       'D'
#define GAUCHE       'G'
#define FIN          'F'
#define ACQUITTEMENT 'ACK'

class partie;
class ihm;

class bluetooth
{
    Q_OBJECT

    private:
        ihm*    ihm;
        Partie* partie;
    public:
        bluetooth(ihm* ihm);
        ~bluetooth();
};

#endif // BLUETOOTH_H
