#include "partie.h"
#include <QMovie>
#include <QDebug>

Partie::Partie(QWidget* parent) : QWidget(parent), imageFond("../images/herbe.gif")
{
    qDebug() << Q_FUNC_INFO;
    initialiserEcran();
}

Partie::~Partie()
{
    qDebug() << Q_FUNC_INFO;
}

void Partie::initialiserEcran()
{
    QVBoxLayout* layoutFenetre = new QVBoxLayout();
    layoutFenetre->setContentsMargins(0, 0, 0, 0);

    QLabel* fondFenetre = new QLabel(this);
    /*QPixmap image(imageFond);
    fondFenetre->setPixmap(image);*/

    QMovie* fondAnime = new QMovie(imageFond);
    fondFenetre->setMovie(fondAnime);
    fondAnime->start();
    layoutFenetre->addWidget(fondFenetre);

    QVBoxLayout* layoutBoutons = new QVBoxLayout;
    layoutBoutons->setContentsMargins(150, 50, 150, 50);
    QPushButton* bouton = new QPushButton("Abandonner", this);
    bouton->setStyleSheet("font-size: 60px;");
    layoutBoutons->addWidget(bouton);
    connect(bouton, &QPushButton::clicked, this, &Partie::fermerEcran);
    layoutFenetre->addLayout(layoutBoutons);

    setLayout(layoutFenetre);
    showMaximized();
}

void Partie::fermerEcran()
{
    emit fermetureEcran("Partie");
}
