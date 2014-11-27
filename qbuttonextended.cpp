#include "qbuttonextended.h"

QButtonExtended::QButtonExtended(QWidget *parent) :
    QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(triggered()));
    connect(this, SIGNAL(pressed()), this, SLOT(press()));
}

void QButtonExtended::triggered() {
    emit clicked(this->objectName());
}

void QButtonExtended::press() {
    emit pressed(this->objectName());
}
