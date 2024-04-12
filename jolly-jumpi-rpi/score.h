#ifndef SCORE_H
#define SCORE_H

#include <QWidget>

class Score : public QWidget
{
    Q_OBJECT

    public:
        explicit Score(QWidget *parent = nullptr);
        ~Score();

    private slots:
        void abandonner();

    private:

};

#endif // SCORE_H
