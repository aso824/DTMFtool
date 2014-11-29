#ifndef TONEPLAYER_H
#define TONEPLAYER_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QTimer>
#include <QDebug>

#include <map>

#include "generator.h"
#include "freqs.h"

class TonePlayer : public QObject
{
    Q_OBJECT
public:
    explicit TonePlayer(QObject *parent = 0);

    void playToneFor(char ch, unsigned short msecs);

public slots:
    void playTone(char ch);
    void stopTone();

signals:
    void playingTone(int, int);
    void stopped();

private:
    QAudioDeviceInfo device;
    QAudioOutput *output;
    QAudioFormat format;
    Generator *generator;
    std::map<char, std::pair<unsigned short, unsigned short>> keys;

    void initAudio();
    void initKeys();
};

#endif // TONEPLAYER_H
