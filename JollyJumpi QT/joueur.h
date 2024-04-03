#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>

class Joueur
{
public:
    Joueur(const QString &nom);

private:
    QString nom_joueur;
    int score_joueur;
};

#endif // JOUEUR_H
