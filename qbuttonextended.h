#ifndef QBUTTONEXTENDED_H
#define QBUTTONEXTENDED_H

#include <QPushButton>

class QButtonExtended : public QPushButton
{
    Q_OBJECT
public:
    explicit QButtonExtended(QWidget *parent = 0);

private slots:
    void triggered();
    void press();

signals:
    void clicked(QString);
    void pressed(QString);
};

#endif // QBUTTONEXTENDED_H
