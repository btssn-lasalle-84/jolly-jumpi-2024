#include "partie.h"
#include <QFile>
#include <QDebug>

Partie::Partie(QWidget* parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;

    QFile file("/home/btssn2/Documents/BTS-2/jolly-jumpi-2024/jolly-jumpi-rpi/partie.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        setStyleSheet(styleSheet);
    } else {
        qDebug() << "Impossible de charger le fichier de style partie.qss";
    }
}

Partie::~Partie()
{
    qDebug() << Q_FUNC_INFO;
}

void Partie::fermerEcran()
{
    emit fermetureEcran("Partie");
}
