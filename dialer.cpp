#include "dialer.h"

Dialer::Dialer(QObject *parent) :
    QThread(parent)
{
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
}

void Dialer::run() {
    // Parameters for progress bar
    unsigned short len = data.length();

    // Main thread loop
    for (unsigned short i = 0; i < len; i++) {
        // Wait if paused
        while (paused) {
            msleep(10);
        }

        // Emit data for progress bar
        int progress = (i / len) * 100;
        emit updateProgress(progress);

        // Make sound
        emit playTone(data[i].toLatin1());
        msleep(time);
        emit stopTone();

        // Wait time between digits
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
