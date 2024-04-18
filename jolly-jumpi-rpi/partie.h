#ifndef PARTIE_H
#define PARTIE_H

#include <QtWidgets>
#include <QLabel>

class Partie : public QWidget
{
    Q_OBJECT

  public:
    explicit Partie(QWidget *parent = nullptr);
    ~Partie();

  private slots:
    void fermerEcran();

  private:


  signals:
    void fermetureEcran(QString nomEcran);
};

#endif // PARTIE_H
