#ifndef PARTIE_H
#define PARTIE_H

#include <QtWidgets>

class Partie : public QWidget
{
    Q_OBJECT

  public:
    explicit Partie(QWidget* ihm);
    ~Partie();

  private:
    QWidget* ihm;
    QString  imageFond;
    void     initialiserFenetre();

  private slots:
    void fermerFenetre();
};

#endif // PARTIE_H
