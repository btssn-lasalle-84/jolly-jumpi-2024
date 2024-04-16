#include "ihm.h"
#include "partie.h"
#include "options.h"
#include "score.h"
#include <QDebug>

/**
 * @file ihm.cpp
 * @brief Définition de la classe IHM
 * @author ARMANDO Célian
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe IHM
 *
 * @fn IHM::IHM
 * @param parent L'adresse de l'objet parent, si nullptr IHM sera la
 * fenêtre principale de l'application
 */

IHM::IHM(QWidget* parent) :
    QMainWindow(parent), partie(new Partie(this)), options(new Options(this)),
    score(new Score(this)), choixBouton(Bouton::B_Jouer)
{
    qDebug() << Q_FUNC_INFO;

    creerEcrans();
    creerBanniere();
    creerBoutons();
    creerNavigation();

    showMaximized();
}

IHM::~IHM()
{
    qDebug() << Q_FUNC_INFO;
}

void IHM::afficherAccueil()
{
    qDebug() << Q_FUNC_INFO;
    ecrans->setCurrentWidget(accueil);
}

void IHM::jouer()
{
    qDebug() << Q_FUNC_INFO;
    ecrans->setCurrentWidget(partie);
}

void IHM::reglerParametres()
{
    qDebug() << Q_FUNC_INFO;
    ecrans->setCurrentWidget(options);
}

void IHM::afficherScores()
{
    qDebug() << Q_FUNC_INFO;
    ecrans->setCurrentWidget(score);
}

void IHM::creerEcrans()
{
    qDebug() << Q_FUNC_INFO;
    ecranPrincipal  = new QWidget;
    layoutPrincipal = new QVBoxLayout;
    ecranPrincipal->setLayout(layoutPrincipal);
    setCentralWidget(ecranPrincipal);

    // les écrans
    ecrans = new QStackedWidget(this);

    // écran d'accueil
    accueil       = new QWidget;
    layoutAccueil = new QVBoxLayout;
    accueil->setLayout(layoutAccueil);

    // les autes écrans
    ecrans->addWidget(accueil);
    ecrans->addWidget(partie);
    ecrans->addWidget(options);
    ecrans->addWidget(score);

    layoutPrincipal->addWidget(ecrans);
}

void IHM::creerBanniere()
{
    QFrame* banniere = new QFrame(this);
    banniere->setStyleSheet("background-color: blue; color: white; font-size: 24px;");
    QLabel* labelBanniere = new QLabel(NOM_APPLICATION, banniere);
    labelBanniere->setAlignment(Qt::AlignCenter);
    QHBoxLayout* layoutBanniere = new QHBoxLayout(banniere);
    layoutBanniere->addWidget(labelBanniere);
    banniere->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setMenuWidget(banniere);
}

void IHM::creerBoutons()
{
    QStringList nomBoutons = { "Jouer", "Options", "Scores" };

    layoutAccueil->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout* layoutBoutons = new QVBoxLayout;
    layoutBoutons->setContentsMargins(150, 5, 150, 5);
    layoutBoutons->setSpacing(50);

    for(int i = 0; i < nomBoutons.size(); ++i)
    {
        QPushButton* bouton = new QPushButton(nomBoutons.at(i), this);
        bouton->setStyleSheet("font-size: 60px;");
        boutons.push_back(bouton);
        layoutBoutons->addWidget(bouton);

        connect(boutons[i],
                &QPushButton::clicked,
                [this, i]()
                {
                    switch(i)
                    {
                        case B_Jouer:
                            jouer();
                            break;
                        case B_Options:
                            reglerParametres();
                            break;
                        case B_Score:
                            afficherScores();
                            break;
                        default:
                            break;
                    }
                });
    }
    layoutAccueil->addLayout(layoutBoutons);
}

void IHM::creerNavigation()
{
    // Retour à l'écran d'accueil
    connect(partie, &Partie::fermetureEcran, this, &IHM::afficherAccueil);
    connect(options, &Options::abandon, this, &IHM::afficherAccueil);
    connect(score, &Score::abandon, this, &IHM::afficherAccueil);
}
