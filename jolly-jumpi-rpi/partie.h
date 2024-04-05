#ifndef PARTIE_H
#define PARTIE_H

#include <QWidget>

class Partie : public QWidget
{
    Q_OBJECT

public:
    explicit Partie(const QString& imagePath, QWidget *parent = nullptr);

private:
    void setupUI(const QString& imagePath);
};

#endif // PARTIE_H
