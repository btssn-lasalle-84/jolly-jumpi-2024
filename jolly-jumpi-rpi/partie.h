#ifndef PARTIE_H
#define PARTIE_H

#include <QtWidgets>

class Partie : public QWidget
{
    Q_OBJECT

  public:
    explicit Partie(QWidget* parent);
    ~Partie();

  private slots:
    void fermerEcran();

  private:
    QString imageFond;
    void    initialiserEcran();

  signals:
    void fermetureEcran(QString nomEcran);
};

#endif // PARTIE_H
