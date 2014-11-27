#include "qbuttonextended.h"

QButtonExtended::QButtonExtended(QWidget *parent) :
    QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(triggered()));
}

void QButtonExtended::triggered() {
    emit clicked(this->objectName());
}
