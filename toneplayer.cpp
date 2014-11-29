#include "toneplayer.h"

TonePlayer::TonePlayer(QObject *parent) :
    QObject(parent)
{
    /* RAII */
    initAudio();
    initKeys();
}

void TonePlayer::initAudio() {
    // Initialize audio format
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    // Check support of created format
    device = QAudioDeviceInfo::defaultOutputDevice();
    if (!device.isFormatSupported(format))
        format = device.nearestFormat(format);

    // Create audio output
    output = new QAudioOutput(device, format, this);
}

void TonePlayer::initKeys() {
    keys['1'] = std::make_pair(0, 0);
    keys['2'] = std::make_pair(1, 0);
    keys['3'] = std::make_pair(2, 0);
    keys['A'] = std::make_pair(3, 0);

    keys['4'] = std::make_pair(0, 1);
    keys['5'] = std::make_pair(1, 1);
    keys['6'] = std::make_pair(2, 1);
    keys['B'] = std::make_pair(3, 1);

    keys['7'] = std::make_pair(0, 2);
    keys['8'] = std::make_pair(1, 2);
    keys['9'] = std::make_pair(2, 2);
    keys['C'] = std::make_pair(3, 2);

    keys['S'] = std::make_pair(0, 3);
    keys['0'] = std::make_pair(1, 3);
    keys['H'] = std::make_pair(2, 3);
    keys['D'] = std::make_pair(3, 3);
}

void TonePlayer::playTone(char ch) {
    // Get tones
    unsigned short tone1 = DTMFfreq[0][keys[ch].first],
                   tone2 = DTMFfreq[1][keys[ch].second];

    emit playingTone(tone1, tone2);
    qDebug() << "[TonePlayer] Playing tone" << ch << ", freq" << tone1 << "Hz /" << tone2 << "Hz";

    // Start generator and audio output
    generator = new Generator(format, 100000, tone1, tone2, this);
    generator->start();
    output->start(generator);
}

void TonePlayer::playToneFor(char ch, unsigned short msecs) {
    playTone(ch);
    QTimer::singleShot(msecs, this, SLOT(stopTone()));
}

void TonePlayer::stopTone() {
    // Stop generator and audio
    output->stop();
    generator->stop();

    emit stopped();
    qDebug() << "[TonePlayer] Stopped";
}
