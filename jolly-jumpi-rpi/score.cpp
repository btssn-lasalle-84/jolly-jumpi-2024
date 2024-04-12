#include "score.h"
#include <QPushButton>
#include <QVBoxLayout>

Score::Score(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *abandonnerButton = new QPushButton("Abandonner", this);
    connect(abandonnerButton, &QPushButton::clicked, this, &Score::abandonner);
    layout->addWidget(abandonnerButton);
}

Score::~Score()
{
}

void Score::abandonner()
{

}
