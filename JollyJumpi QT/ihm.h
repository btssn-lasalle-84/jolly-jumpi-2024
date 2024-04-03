#ifndef IHM_H
#define IHM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "partie.h"

class IHM : public QWidget
{
    Q_OBJECT

    public:
        explicit IHM(QWidget *parent = nullptr);

    private:
        Partie *partie;
        QVBoxLayout *layoutPrincipal;
        QLabel *labelInfo;
        QPushButton *boutonDemarrer;
        QPushButton *boutonArreter;
};

#endif // IHM_H
