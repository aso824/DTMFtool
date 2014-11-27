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
        } else {
            // Only one signal will be emitted when pressed
            connect(wid, SIGNAL(clicked(QString)), this, SLOT(buttonPlayTone(QString)));
        }
    }
}

void MainWindow::buttonPlayTone(QString btnName) {
    // Get key code
    char keyCode = btnName.at(btnName.length() - 1).toLatin1();

    // Call function
    buttonSingleTone(keyCode);
}

void MainWindow::buttonSingleTone(char key) {
    qDebug() << "Playing tone" << key;

    unsigned short tone1 = DTMFfreq[0][keyLayoutMap[key].first],
                   tone2 = DTMFfreq[1][keyLayoutMap[key].second];

    generator = new Generator(format, 100000, tone1, tone2, this);
    generator->start();
    output->start(generator);
}
