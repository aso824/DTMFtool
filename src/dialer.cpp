#include "include/dialer.h"

Dialer::Dialer(QObject *parent) :
    QThread(parent)
{
}

Dialer::~Dialer() {
    emit end();
}

void Dialer::setParameters(unsigned short digitTime, unsigned short digitInterval) {
    time = digitTime;
    interval = digitInterval;
}

void Dialer::setData(QString dialerData) {
    data.clear();

    // Filter characters
    foreach (QChar ch, dialerData.toUpper()) {
        if (( (ch >= '0') && (ch <= '9')) || ( (ch >= 'A') && (ch <= 'D')))
            data += ch;
    }

    dataLen = data.length();
}

 void Dialer::setTonePlayer(TonePlayer *tonePlayer) {
     output = tonePlayer;
 }

void Dialer::run() {
    play();
}

void Dialer::play() {
    foreach(QChar ch, data) {
        while (paused)
            msleep(100);

        currentPos++;
        sendProgress();

        output->playTone(ch.toLatin1());
        msleep(time);
        output->stopTone();
        msleep(interval);
    }

    emit end();
}

void Dialer::pause() {
    paused = true;
}

void Dialer::resume() {
    paused = false;
}

void Dialer::sendProgress() {
    int progress = (currentPos / dataLen) * 100;
    emit updateProgress(progress);
}
