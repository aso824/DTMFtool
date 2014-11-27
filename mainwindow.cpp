#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initAudio();

    createKeyLayoutMap();
    getKeyboardButtons();
    connectKeyboardButtons();

    // Set input validator for miliseconds field
    ui->edToneTime->setValidator(new QIntValidator(1, 10000, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createKeyLayoutMap() {
    keyLayoutMap['1'] = std::make_pair(0, 0);
    keyLayoutMap['2'] = std::make_pair(1, 0);
    keyLayoutMap['3'] = std::make_pair(2, 0);
    keyLayoutMap['A'] = std::make_pair(3, 0);

    keyLayoutMap['4'] = std::make_pair(0, 1);
    keyLayoutMap['5'] = std::make_pair(1, 1);
    keyLayoutMap['6'] = std::make_pair(2, 1);
    keyLayoutMap['B'] = std::make_pair(3, 1);

    keyLayoutMap['7'] = std::make_pair(0, 2);
    keyLayoutMap['8'] = std::make_pair(1, 2);
    keyLayoutMap['9'] = std::make_pair(2, 2);
    keyLayoutMap['C'] = std::make_pair(3, 2);

    keyLayoutMap['S'] = std::make_pair(0, 3);
    keyLayoutMap['0'] = std::make_pair(1, 3);
    keyLayoutMap['H'] = std::make_pair(2, 3);
    keyLayoutMap['D'] = std::make_pair(3, 3);
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

void MainWindow::stopTone() {
    // Stop generator and audio
    output->stop();
    generator->stop();

    // Clear UI fields
    ui->edTone1->clear();
    ui->edTone2->clear();
}

void MainWindow::getKeyboardButtons() {
    // Iterate over all buttons in grid layout (keyboard)
    for (int i = 0; i < ui->gridKeyboard->count(); i++) {
        if (QWidgetItem *element = dynamic_cast<QWidgetItem*>(ui->gridKeyboard->itemAt(i)))
            keyboardButtonsList << element->widget();
    }
}

void MainWindow::connectKeyboardButtons(bool continuous) {
    // Iterate over all buttons in list for connect them with slot
    foreach(QWidget *element, keyboardButtonsList) {
        QButtonExtended *wid = qobject_cast<QButtonExtended*>(element);

        // Remove existing connections
        wid->disconnect(this);

        // Connect to correct slot
        if (continuous) {
            // Button will emit tone continuously when pressed
            connect(wid, SIGNAL(pressed(QString)), this, SLOT(buttonPlayContinuousTone(QString)));
            connect(wid, SIGNAL(released()), this, SLOT(stopTone()));
        } else {
            // Only one signal will be emitted when pressed
            connect(wid, SIGNAL(clicked(QString)), this, SLOT(buttonPlaySingleTone(QString)));
        }
    }
}

void MainWindow::playTone(char key) {
    // Get tones
    unsigned short tone1 = DTMFfreq[0][keyLayoutMap[key].first],
                   tone2 = DTMFfreq[1][keyLayoutMap[key].second];

    // Fill UI fields
    QString t1 = QString::number(tone1) + QString(" Hz");
    QString t2 = QString::number(tone2) + QString(" Hz");
    ui->edTone1->setText(t1);
    ui->edTone2->setText(t2);

    // Start generator and audio output
    generator = new Generator(format, 100000, tone1, tone2, this);
    generator->start();
    output->start(generator);
}

void MainWindow::buttonPlaySingleTone(QString btnName) {\
    // Get key code
    char key = btnName.at(btnName.length() - 1).toLatin1();

    // Start playing tone
    playTone(key);

    // Create single-shot timer to stop playing tone (non-continuous mode)
    QTimer::singleShot(ui->edToneTime->text().toInt(), this, SLOT(stopTone()));
}

void MainWindow::buttonPlayContinuousTone(QString btnName) {
    // Get key code
    char key = btnName.at(btnName.length() - 1).toLatin1();

    // Start playing tone
    playTone(key);
}

void MainWindow::on_rbToneContinuous_clicked()
{
    ui->edToneTime->setDisabled(true);
    connectKeyboardButtons(true);
}

void MainWindow::on_rbToneSingle_clicked()
{
    ui->edToneTime->setEnabled(true);
    connectKeyboardButtons(false);
}
