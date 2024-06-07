#include "partie.h"
#include <QFile>
#include <QDebug>

Partie::Partie(QWidget* parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;

    initialiserEcran();
#ifdef SIMULATION_CLAVIER
    numeroChevalSelectionne = 0;
    for(int i = 0; i < NB_CHEVAUX_DEFAUT; i++)
    {
        positionsChevaux.push_back(0);
    }
    initialiserPositionsChevaux();
    installerModeSimulationClavier();
#endif
}

Partie::~Partie()
{
    qDebug() << Q_FUNC_INFO;
}

void Partie::initialiser()
{
#ifdef SIMULATION_CLAVIER
    numeroChevalSelectionne = 0;
    initialiserPositionsChevaux();
#endif
}

void Partie::avancerCheval(int numero, int position)
{
    qDebug() << Q_FUNC_INFO << "numero" << numero << "position" << position;
    int points = 0;
    if(position >= 1 && position <= 3)
        points = 1;
    if(position >= 4 && position <= 5)
        points = 2;
    if(position == 6)
        points = 3;
    qDebug() << Q_FUNC_INFO << "numero" << numero << "points" << points;
    positionsChevaux[numero - 1] += points;
    if(positionsChevaux[numero - 1] < LONGUEUR_COURSE_DEFAUT)
        afficherCheval(numero - 1, positionsChevaux[numero - 1]);
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
    bouton->setStyleSheet("background-color: blue;");
    bouton->setObjectName("abandonnerButton");
    layoutBoutons->addWidget(bouton);
    connect(bouton, &QPushButton::clicked, this, &Partie::fermerEcran);
    layoutFenetre->addLayout(layoutBoutons);

    setLayout(layoutFenetre);
    showMaximized();
}

void Partie::afficherCheval(int numero, int position)
{
    qDebug() << Q_FUNC_INFO << "numero" << numero << "position" << position;
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

#ifdef SIMULATION_CLAVIER
void Partie::installerModeSimulationClavier()
{
    qDebug() << Q_FUNC_INFO;
    QAction* avancerCheval = new QAction(this);
    avancerCheval->setShortcut(QKeySequence(Qt::Key_Right));
    addAction(avancerCheval);
    connect(avancerCheval, SIGNAL(triggered()), this, SLOT(simulerAvancementCheval()));

    QAction* simulerSelectionPrecedent = new QAction(this);
    simulerSelectionPrecedent->setShortcut(QKeySequence(Qt::Key_Up));
    addAction(simulerSelectionPrecedent);
    connect(simulerSelectionPrecedent,
            SIGNAL(triggered()),
            this,
            SLOT(selectionnerChevalPrecedent()));

    QAction* simulerSelectionSuivant = new QAction(this);
    simulerSelectionSuivant->setShortcut(QKeySequence(Qt::Key_Down));
    addAction(simulerSelectionSuivant);
    connect(simulerSelectionSuivant, SIGNAL(triggered()), this, SLOT(selectionnerChevalSuivant()));
}

void Partie::initialiserPositionsChevaux()
{
    for(int i = 0; i < NB_CHEVAUX_DEFAUT; i++)
    {
        positionsChevaux[i] = 0;
        afficherCheval(i, positionsChevaux[i]);
    }
}

void Partie::simulerAvancementCheval()
{
    positionsChevaux[numeroChevalSelectionne]++;
    if(positionsChevaux[numeroChevalSelectionne] < LONGUEUR_COURSE_DEFAUT)
        afficherCheval(numeroChevalSelectionne, positionsChevaux[numeroChevalSelectionne]);
}

void Partie::selectionnerChevalPrecedent()
{
    --numeroChevalSelectionne;
    if(numeroChevalSelectionne < 0)
        numeroChevalSelectionne = NB_CHEVAUX_DEFAUT - 1;
}

void Partie::selectionnerChevalSuivant()
{
    ++numeroChevalSelectionne;
    if(numeroChevalSelectionne >= NB_CHEVAUX_DEFAUT)
        numeroChevalSelectionne = 0;
}

#endif
