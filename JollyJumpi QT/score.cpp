#include "score.h"

Score::Score(QObject *parent) : QObject(parent), points(0)
{
}

Score::~Score()
{
}

int Score::valeur() const
{
    return points;
}

void Score::incrementer()
{
    ++points;
    emit valeurChangee(points);
}

void Score::reset()
{
    points = 0;
    emit valeurChangee(points);
}
