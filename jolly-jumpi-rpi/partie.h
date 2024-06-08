#ifndef PARTIE_H
#define PARTIE_H

#include <QtWidgets>
#include <QLabel>

/**
 * @def NB_CHEVAUX_DEFAUT
 * @brief Le nombre de chevaux par défaut pour une course
 */
#define NB_CHEVAUX_DEFAUT 6

/**
 * @def LONGUEUR_COURSE_DEFAUT
 * @brief La longueur par défaut d'une course
 */
#define LONGUEUR_COURSE_DEFAUT 10

#define TAILLE_CHEVAL 256

#define SIMULATION_CLAVIER

class Partie : public QWidget
{
    Q_OBJECT

  public:
    explicit Partie(QWidget* parent = nullptr);
    ~Partie();

    void initialiser();

  public slots:
    void avancerCheval(int numero, int position);

  private slots:
    void fermerEcran();
#ifdef SIMULATION_CLAVIER
    void simulerAvancementCheval();
    void selectionnerChevalPrecedent();
    void selectionnerChevalSuivant();
#endif

  private:
    QGridLayout*      hippodrome;
    QVector<QLabel*>  pistes;
    QVector<QPixmap*> imagesCheval;
    QVector<int>      positionsChevaux;
#ifdef SIMULATION_CLAVIER
    int numeroChevalSelectionne;
#endif

    void initialiserEcran();
    void afficherCheval(int numero, int position);
#ifdef SIMULATION_CLAVIER
    void installerModeSimulationClavier();
    void initialiserPositionsChevaux();
#endif
  signals:
    void fermetureEcran(QString nomEcran);
};

#endif // PARTIE_H
