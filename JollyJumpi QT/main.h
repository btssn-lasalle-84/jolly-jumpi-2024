#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include "partie.h"
#include "ihm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Main; }
QT_END_NAMESPACE

class Main : public QMainWindow
{
    Q_OBJECT

    public:
        Main(QWidget *parent = nullptr);
        ~Main();

    private:
        Partie *partie;
        IHM *ihm;
};

#endif // MAIN_H
