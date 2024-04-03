#include "ihm.h"
#include "ui_ihm.h"
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
IHM::IHM(QWidget* parent) : QMainWindow(parent), partie(nullptr), ui(new Ui::IHM)
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);
}

IHM::~IHM()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}
