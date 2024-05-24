#include "options.h"
#include <QDebug>

Options::Options(QWidget* parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;
    initialiserEcran();
}

Options::~Options()
{
    qDebug() << Q_FUNC_INFO;
}

void Options::initialiserEcran()
{
    QVBoxLayout* layout           = new QVBoxLayout(this);
    QPushButton* abandonnerButton = new QPushButton("Abandonner", this);
    connect(abandonnerButton, &QPushButton::clicked, this, &Options::abandonner);
    abandonnerButton->setStyleSheet("font-size: 30px;");
    layout->setAlignment(Qt::AlignCenter);
    abandonnerButton->setFixedSize(200, 50);
    layout->addWidget(abandonnerButton);
}

void Options::abandonner()
{
    emit abandon("Options");
}
