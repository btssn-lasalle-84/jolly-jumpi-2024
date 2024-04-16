#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 * @brief Déclaration de la classe IHM
 * @author ARMANDO Célian
 * @version 0.1
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

    void creerEcrans();
    void creerBanniere();
    void creerBoutons();
    void creerNavigation();

  private slots:
    void afficherAccueil();
    void jouer();
    void reglerParametres();
    void afficherScores();
};

#endif // IHM_H
