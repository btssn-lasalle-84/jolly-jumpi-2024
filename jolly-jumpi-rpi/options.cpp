#include "options.h"
#include <QPushButton>
#include <QVBoxLayout>

Options::Options(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *abandonnerButton = new QPushButton("Abandonner", this);
    connect(abandonnerButton, &QPushButton::clicked, this, &Options::abandonner);
    layout->addWidget(abandonnerButton);
}

Options::~Options()
{
}

void Options::abandonner()
{

}
