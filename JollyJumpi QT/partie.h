#ifndef PARTIE_H
#define PARTIE_H

#include <QObject>
#include <QList>
#include "joueur.h"
#include "main.h"
#include "options.h"

class Partie : public QObject
{
    Q_OBJECT

    public:
        explicit Partie(QObject *parent = nullptr);
        ~Partie();

    private:

};

#endif // PARTIE_H
