#include "score.h"
#include <QDebug>

Score::Score(QWidget* parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;
    initialiserEcran();
}

Score::~Score()
{
    qDebug() << Q_FUNC_INFO;
}

void Score::initialiserEcran()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Layout horizontal
    QHBoxLayout* playerLayout = new QHBoxLayout();

    // Création 6 colomnes
    for (int i = 1; i <= 6; ++i)
    {
        // Création layout vertical
        QVBoxLayout* columnLayout = new QVBoxLayout();

        // Label joueur
        QLabel* playerLabel = new QLabel(QString("Joueur %1").arg(i), this);
        playerLabel->setAlignment(Qt::AlignCenter);
        playerLabel->setStyleSheet("font-weight: bold; color: blue; font-size: 60px;");
        columnLayout->addWidget(playerLabel);

        // Espace colomne
        columnLayout->addStretch();

        // Layout colomne dans layout joueur
        playerLayout->addLayout(columnLayout);

        // Séparateur vertical
        if (i < 6)
        {
            QFrame* line = new QFrame();
            line->setFrameShape(QFrame::VLine);
            line->setFrameShadow(QFrame::Sunken);
            line->setStyleSheet("color: white;");
            playerLayout->addWidget(line);
        }
    }

    // Ajout joueur layout
    mainLayout->addLayout(playerLayout);

    // Bouton retour
    QPushButton* abandonnerButton = new QPushButton("Retour", this);
   connect(abandonnerButton, &QPushButton::clicked, this, &Score::abandonner);
   abandonnerButton->setStyleSheet("font-size: 60px;");
   abandonnerButton->setFixedSize(1200, 100);
   mainLayout->addWidget(abandonnerButton);
   mainLayout->setAlignment(abandonnerButton, Qt::AlignHCenter | Qt::AlignBottom);


    setLayout(mainLayout);
}

void Score::abandonner()
{
    emit abandon("Score");
}
