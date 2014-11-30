#ifndef DIALER_H
#define DIALER_H

#include <QThread>
#include <QString>

class Dialer : public QThread
{
    Q_OBJECT
public:
    explicit Dialer(QObject *parent = 0);

    void setParameters(unsigned short digitTime, unsigned short digitInterval);
    void setData(QString dialerData);
    void run();

signals:
    void playTone(char ch);
    void stopTone();

    void end();
    void updateProgress(int);

public slots:
    void pause();
    void resume();

private:
    unsigned short time = 0,
                   interval = 0;
    QString data;
    bool paused = false;

};

#endif // DIALER_H
