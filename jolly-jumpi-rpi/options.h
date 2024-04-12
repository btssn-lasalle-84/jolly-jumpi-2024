#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>

class Options : public QWidget
{
    Q_OBJECT

    public:
        explicit Options(QWidget *parent = nullptr);
        ~Options();

    private slots:
        void abandonner();

    private:

};

#endif // OPTIONS_H
