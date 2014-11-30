#ifndef DIALER_H
#define DIALER_H

#include <QThread>
#include <QString>
#include <QTimer>

#include "toneplayer.h"

class Dialer : public QThread
{
    Q_OBJECT
public:
    explicit Dialer(QObject *parent = 0);
    ~Dialer();

    void setParameters(unsigned short digitTime, unsigned short digitInterval);
    void setData(QString dialerData);
    void setTonePlayer(TonePlayer *tonePlayer);


signals:
    void end();
    void updateProgress(int);

public slots:
    void pause();
    void resume();

private slots:
    void play();

private:
    unsigned short time = 0,
                   interval = 0,
                   dataLen = 0,
                   currentPos = 0;
    QString data;
    TonePlayer *output;
    QTimer timerPlay, timerStop, timerInterval;

    bool paused = false;

    void sendProgress();
    void run();

};

#endif // DIALER_H
