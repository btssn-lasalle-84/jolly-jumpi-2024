#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 * @brief Déclaration de la classe IHM
 * @author ARMANDO Célian
 * @version 0.1
 */

#include <QStackedWidget>
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

  private:

    enum Bouton
    {
        Jouer = 0,
        Options,
        Score,
        NbBoutons
    };

    Partie *partie;
    Options *options;
    Score *score;
    QVector<QPushButton*> boutons;
    QStackedWidget* stackedWidget;

    /**
     * @enum Bouton
     * @brief Définit les différentes boutons de l'IHM
     *
     */
    void creerBanniere();
    void creerBoutons();

  private slots:
    void jouer();
    void reglerParametres();
    void afficherScores();
};

#endif // IHM_H
