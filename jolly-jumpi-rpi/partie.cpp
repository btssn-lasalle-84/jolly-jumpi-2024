#include "partie.h"
#include <QFile>
#include <QDebug>

Partie::Partie(QWidget* parent) : QWidget(parent)
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

    for(int i = 0; i < NB_CHEVAUX_DEFAUT; i++)
    {
        pistes.push_back(new QLabel(this));
        imagesCheval.push_back(new QPixmap("../images/cheval" + QString::number(i + 1) + ".png"));
    }

    for(int i = 0; i < NB_CHEVAUX_DEFAUT; i++)
    {
        pistes[i]->setStyleSheet(
          "background-color: #b7f9ba;border: 5px solid black;border-radius: 8px;");
    }

    hippodrome = new QGridLayout();
    for(int i = 0; i < NB_CHEVAUX_DEFAUT; i++)
    {
        hippodrome->addWidget(pistes[i], i, 0, Qt::AlignCenter);
    }
    layoutFenetre->addLayout(hippodrome);

    for(int i = 0; i < NB_CHEVAUX_DEFAUT; i++)
    {
        afficherCheval(i, 0);
    }

    QVBoxLayout* layoutBoutons = new QVBoxLayout;
    layoutBoutons->setContentsMargins(150, 50, 150, 50);
    QPushButton* bouton = new QPushButton("Abandonner", this);
    bouton->setObjectName("abandonnerButton");
    layoutBoutons->addWidget(bouton);
    connect(bouton, &QPushButton::clicked, this, &Partie::fermerEcran);
    layoutFenetre->addLayout(layoutBoutons);

    setLayout(layoutFenetre);
    showMaximized();
}

void Partie::afficherCheval(int numero, int position)
{
    // on récupère l'image du cheval
    QImage cheval("../images/cheval" + QString::number(numero + 1) + ".png");
    // on récupère la piste du cheval
    QPixmap piste("../images/piste.png");
    // on dessine le cheval sur la piste
    QPainter p(&piste);
    p.drawImage(QPoint(position * TAILLE_CHEVAL, 0), cheval);
    p.end();
    // on place la nouvelle image
    pistes[numero]->setPixmap(piste);
}

void Partie::fermerEcran()
{
    emit fermetureEcran("Partie");
}
