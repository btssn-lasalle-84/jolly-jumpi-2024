#ifndef OPTIONS_H
#define OPTIONS_H

#include <QtWidgets>

class Options : public QWidget
{
    Q_OBJECT

  public:
    explicit Options(QWidget* parent = nullptr);
    ~Options();

  private slots:
    void abandonner();

  private:
    void initialiserEcran();

  signals:
    void abandon(QString nomEcran);
};

#endif // OPTIONS_H
