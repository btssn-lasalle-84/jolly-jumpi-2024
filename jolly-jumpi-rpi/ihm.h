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
    Partie*               partie; //!< association vers la classe Quizzy
    QVector<QPushButton*> boutons;

    /**
     * @enum Bouton
     * @brief Définit les différentes boutons de l'IHM
     *
     */
    enum Bouton
    {
        Jouer = 0,
        Options,
        Scores,
        NbBoutons
    };

    void creerBanniere();
    void creerBoutons();

  private slots:
    void jouer();
    void reglerParametres();
    void afficherScores();
};

#endif // IHM_H
