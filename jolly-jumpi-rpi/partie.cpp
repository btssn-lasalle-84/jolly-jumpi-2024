#include "partie.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMovie>

Partie::Partie(const QString& imagePath, QWidget *parent) : QWidget(parent)
{
    setupUI(imagePath);
}

void Partie::setupUI(const QString& imagePath)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(5);

    QLabel* background = new QLabel(this);
    /*QPixmap image(imagePath);
    background->setPixmap(image);
    layout->addWidget(background);*/

    QMovie* fondAnime = new QMovie(imagePath);
    background->setMovie(fondAnime);
    fondAnime->start();
    layout->addWidget(background);

    setLayout(layout);
}
