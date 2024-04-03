#ifndef PARTIE_H
#define PARTIE_H

#include <QObject>

class Partie : public QObject
{
    Q_OBJECT

  public:
    explicit Partie(QObject* parent = nullptr);
    ~Partie();

  private:
};

#endif // PARTIE_H
