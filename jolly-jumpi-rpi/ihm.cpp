#include "ihm.h"
#include "partie.h"
#include "options.h"
#include "score.h"
#include "bluetooth.h"
#include <QDebug>

/**
 * @file ihm.cpp
 * @brief Définition de la classe IHM
 * @author ARMANDO Célian
 * @version 0.2
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
    score(new Score(this)), choixBouton(Bouton::B_Jouer), bluetooth(new Bluetooth(this))
{
    qDebug() << Q_FUNC_INFO;

    // Obtenir les dimensions de l'écran disponible
    QRect screenGeometry = qApp->primaryScreen()->availableGeometry();
    qDebug() << "Screen Geometry:" << screenGeometry;

    // Définir la taille de la fenêtre pour qu'elle s'ajuste à l'écran
    resize(screenGeometry.width(), screenGeometry.height());
    setFixedSize(screenGeometry.width(), screenGeometry.height());

    // Appels aux fonctions pour créer l'interface utilisateur
    creerEcrans();
    creerBanniere();
    creerBoutons();
    creerNavigation();

    // Afficher la fenêtre
    show();

    // Initialiser la communication Bluetooth
    bluetooth->initialiserCommunication();
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
    partie->initialiser();
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


    // Fond en vert clair
    setStyleSheet("background-color: lightgreen;");

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
    qDebug() << Q_FUNC_INFO;

    QFrame* banniere = new QFrame(this);
    QHBoxLayout* layoutBanniere = new QHBoxLayout;

    banniere->setLayout(layoutBanniere);
    banniere->setStyleSheet("background-color: blue; height: 100px;");

    QLabel* labelBanniere = new QLabel("Jolly Jumpi");
    labelBanniere->setAlignment(Qt::AlignCenter);
    labelBanniere->setStyleSheet("font-size: 60px; font-weight: bold; color: white;");

    layoutBanniere->addWidget(labelBanniere);
    banniere->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setMenuWidget(banniere);
}

void IHM::gererAffichageBanniere()
{
    if(ecrans->currentWidget() == accueil)
    {
        menuWidget()->show(); // Afficher la bannière
    }
    else
    {
        menuWidget()->hide(); // Cacher la bannière
    }
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
        bouton->setStyleSheet("font-size: 70px;");
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

    connect(ecrans, &QStackedWidget::currentChanged, this, &IHM::gererAffichageBanniere);
}
