#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initAudio();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAudio() {
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
