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
    QVBoxLayout* layout           = new QVBoxLayout(this);
    QPushButton* abandonnerButton = new QPushButton("Abandonner", this);
    connect(abandonnerButton, &QPushButton::clicked, this, &Score::abandonner);
    layout->addWidget(abandonnerButton);
}

void Score::abandonner()
{
    emit abandon("Score");
}
