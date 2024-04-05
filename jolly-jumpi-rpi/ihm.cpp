#include "ihm.h"
#include "ui_ihm.h"
#include "partie.h"
#include <QDebug>
#include <QScreen>
#include <QHBoxLayout>
#include <QVBoxLayout>

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

IHM::IHM(QWidget* parent) : QMainWindow(parent), partie(nullptr), ui(new Ui::IHM)
{
    showMaximized();
    ui->setupUi(this);
    createBaniere();
    createBoutons();
}

void IHM::createBaniere()
{
    QFrame* baniere = new QFrame(this);
    baniere->setStyleSheet("background-color: blue; color: white; font-size: 24px;");
    QLabel* label = new QLabel("Jolly Jumpi", baniere);
    label->setAlignment(Qt::AlignCenter);

    QHBoxLayout* layout = new QHBoxLayout(baniere);
    layout->addWidget(label);

    baniere->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    setMenuWidget(baniere);
}

void IHM::createBoutons()
{
    QStringList buttonNames = {"Jouer", "Options", "Scores", "Quitter"};

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* leftButtonsLayout = new QHBoxLayout;
    leftButtonsLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* rightButtonsLayout = new QHBoxLayout;
    rightButtonsLayout->setAlignment(Qt::AlignCenter);

    for (int i = 0; i < buttonNames.size(); ++i)
    {
        QPushButton* button = new QPushButton(buttonNames.at(i), this);
        button->setStyleSheet("font-size: 18px;");
        if (i < 2)
        {
            leftButtonsLayout->addWidget(button);
        }
        else
        {
            rightButtonsLayout->addWidget(button);
        }
        if (i == 0) {
            connect(button, &QPushButton::clicked, this, &IHM::Jouer);
        }
    }

    mainLayout->addLayout(leftButtonsLayout);
    mainLayout->addLayout(rightButtonsLayout);

    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

IHM* IHM::lancerPartie()
{
    IHM* partieLance = new IHM();
    partieLance->showMaximized();
    return partieLance;
}

void IHM::Jouer()
{
    Partie* newWindow = new Partie("/home/btssn2/Documents/BTS-2/jolly-jumpi-2024/images/herbe.gif");
    newWindow->show();
    this->close();
}


IHM::~IHM()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}
