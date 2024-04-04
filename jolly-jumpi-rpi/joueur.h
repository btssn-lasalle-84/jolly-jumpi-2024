#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>

class Joueur
{
  public:
    Joueur(const QString& nom);
    ~Joueur();

  private:
    QString nom;
    int     score;
};

#endif // JOUEUR_H
