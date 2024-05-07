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

class Partie : public QWidget
{
    Q_OBJECT

  public:
    explicit Partie(QWidget* parent = nullptr);
    ~Partie();

  private slots:
    void fermerEcran();

  private:
    QGridLayout*      hippodrome;
    QVector<QLabel*>  pistes;
    QVector<QPixmap*> imagesCheval;

    void initialiserEcran();
    void afficherCheval(int numero, int position);

  signals:
    void fermetureEcran(QString nomEcran);
};

#endif // PARTIE_H
