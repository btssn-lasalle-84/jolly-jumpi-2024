#ifndef SCORE_H
#define SCORE_H

#include <QtWidgets>

class Score : public QWidget
{
    Q_OBJECT

  public:
    explicit Score(QWidget* parent = nullptr);
    ~Score();

  private slots:
    void abandonner();

  private:
    void initialiserEcran();

  signals:
    void abandon(QString nomEcran);
};

#endif // SCORE_H
