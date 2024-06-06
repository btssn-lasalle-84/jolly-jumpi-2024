#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 * @brief Déclaration de la classe IHM
 * @author ARMANDO Célian
 * @version 0.2
 */

#include <QtWidgets>
#include <QVector>

/**
 * @def NOM_APPLICATION
 * @brief Le nom de l'application
 */
#define NOM_APPLICATION "Jolly Jumpi"

class Partie;
class Options;
class Score;
class Bluetooth;

/**
 * @class IHM
 * @brief Déclaration de la classe IHM
 * @details Cette classe gère l'affichage sur l'écran de la Raspberry Pi
 */

class IHM : public QMainWindow
{
    Q_OBJECT

    public:
        explicit IHM(QWidget* parent = nullptr);
        ~IHM();

        /**
         * @enum Bouton
         * @brief Définit les différentes boutons de l'IHM
         *
         */
        enum Bouton
        {
            Accueil = -1,
            B_Jouer,
            B_Options,
            B_Score,
            NbBoutons
    };

    public slots:
        void gestionNavigation();

    private:
        Partie*               partie;
        Options*              options;
        Score*                score;
        QWidget*              ecranPrincipal;
        QVBoxLayout*          layoutPrincipal;
        QStackedWidget*       ecrans;
        QWidget*              accueil;
        QVBoxLayout*          layoutAccueil;
        QVector<QPushButton*> boutons;
        Bouton                choixBouton;
        Bluetooth*            bluetooth;

        void creerEcrans();
        void creerBanniere();
        void creerBoutons();
        void creerNavigation();
        void creerInteraction();

    private slots:
        void afficherAccueil();
        void jouer();
        void reglerParametres();
        void afficherScores();
        void gererAffichageBanniere();
};

#endif // IHM_H
