#include "ihm.h"
#include "partie.h"
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

IHM::IHM(QWidget* parent) : QMainWindow(parent), partie(nullptr)
{
    qDebug() << Q_FUNC_INFO;
    creerBanniere();
    creerBoutons();

    stackedWidget = new QStackedWidget(this);
    partie = new Partie;
    options = new Options;
    score = new Score;

    stackedWidget->addWidget(partie);
    stackedWidget->addWidget(options);
    stackedWidget->addWidget(score);
    setCentralWidget(stackedWidget);

    showMaximized();
}

IHM::~IHM()
{
    qDebug() << Q_FUNC_INFO;
}

void IHM::jouer()
{
    stackedWidget->setCurrentWidget(partie);
}

void IHM::reglerParametres()
{
    stackedWidget->setCurrentWidget(options);
}

void IHM::afficherScores()
{
    stackedWidget->setCurrentWidget(score);
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
    // @warning il n'y a pas de bouton Quitter dans un mode kiosk !
    QStringList  nomBoutons      = { "Jouer", "Options", "Scores" };
    QVBoxLayout* layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout* layoutBoutons = new QVBoxLayout;
    layoutBoutons->setContentsMargins(150, 5, 150, 5);
    layoutBoutons->setSpacing(50);

    for(int i = 0; i < nomBoutons.size(); ++i)
    {
        QPushButton* bouton = new QPushButton(nomBoutons.at(i), this);
        bouton->setStyleSheet("font-size: 60px;");
        boutons.push_back(bouton);
        layoutBoutons->addWidget(bouton);

        connect(boutons[i], &QPushButton::clicked, [this, i](){
                    switch (i)
                    {
                        case Jouer:
                            jouer();
                            break;
                        case Options:
                            reglerParametres();
                            break;
                        case Scores:
                            afficherScores();
                            break;
                        default:
                            break;
                    }
        });
    }
    layoutPrincipal->addLayout(layoutBoutons);

    connect(boutons[Bouton::Jouer], &QPushButton::clicked, this, &IHM::jouer);
    connect(boutons[Bouton::Options], &QPushButton::clicked, this, &IHM::reglerParametres);
    connect(boutons[Bouton::Scores], &QPushButton::clicked, this, &IHM::afficherScores);

    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(layoutPrincipal);
    setCentralWidget(centralWidget);
}
