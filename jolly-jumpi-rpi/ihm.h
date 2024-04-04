#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 * @brief Déclaration de la classe IHM
 * @author ARMANDO Célian
 * @version 0.1
 */

#include <QtWidgets>

class Partie;

namespace Ui
{
class IHM;
}

/**
 * @class IHM
 * @brief Déclaration de la classe IHM
 * @details Cette classe gère l'affichage sur l'écran de la Raspberry Pi
 */
class IHM : public QMainWindow
{
    Q_OBJECT

  public:
    explicit IHM(QWidget* parent = nullptr);
    ~IHM();

  private:
    Partie* partie; //!< association vers la classe Quizzy
    // La GUI
    Ui::IHM* ui; //!< la GUI de cette classe
};

#endif // IHM_H
