#include "ihm.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application
 * @author ARMANDO Célian
 * @version 0.2
 *
 * @param argc
 * @param argv[]
 * @return int
 *
 */
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    IHM          ihm;

    QFile fichier(":/qss/JollyJumpi.qss");
    if(fichier.open(QFile::ReadOnly))
    {
        QString feuilleStyle = QLatin1String(fichier.readAll());
        a.setStyleSheet(feuilleStyle);
    }

    ihm.show();

    return a.exec();
}
