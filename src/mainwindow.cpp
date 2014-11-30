#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Init tone generator
    output = new TonePlayer(this);

    // Set input validator for miliseconds fields
    ui->edToneTime->setValidator(new QIntValidator(1, 10000, this));
    ui->edGenToneLength->setValidator(new QIntValidator(1, 10000, this));
    ui->edGenToneInterval->setValidator(new QIntValidator(1, 10000, this));

    /* Connect UI elements */

    // Connect keyboard buttons grid to valid slots
    getKeyboardButtons();
    connectKeyboardButtons();

    // Radiobuttons for settings from keyboard tab
    connect(ui->rbToneSingle, SIGNAL(clicked()), this, SLOT(radioToneSingle()));
    connect(ui->rbToneContinuous, SIGNAL(clicked()), this, SLOT(radioToneContinuous()));

    // Fill frequency fields when keyboard buttons pressed
    connect(output, SIGNAL(playingTone(int,int)), this, SLOT(setFreqsFields(int,int)));
    connect(output, SIGNAL(stopped()), this, SLOT(clearFreqsFields()));

    // Buttons for generator
    connect(ui->btnGenStart, SIGNAL(clicked()), this, SLOT(dialerStart()));

    // Menu elements
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stopTone() {
    // Get sender
    QButtonExtended *btn = qobject_cast<QButtonExtended*>(QObject::sender());

    // When sended from button grid and it's single mode, don't stop
    if ( (btn != nullptr) && (continuous != true))
        return;

    // Stop generator and audio
    output->stopTone();

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

void MainWindow::connectKeyboardButtons() {
    // Iterate over all buttons in list for connect them with slot
    foreach(QWidget *element, keyboardButtonsList) {
        QButtonExtended *wid = qobject_cast<QButtonExtended*>(element);

        // Remove existing connections
        wid->disconnect(this);

        // Connect to correct slot
        connect(wid, SIGNAL(pressed(QString)), this, SLOT(buttonPlayToneAction(QString)));
        connect(wid, SIGNAL(released()), this, SLOT(stopTone()));
    }
}

void MainWindow::buttonPlayToneAction(QString btnName) {\
    // Get key code
    char key = btnName.at(btnName.length() - 1).toLatin1();

    // Start playing tone
    if (continuous)
        output->playTone(key);
    else
        output->playToneFor(key, ui->edToneTime->text().toInt());

}


void MainWindow::radioToneSingle() {
    ui->edToneTime->setEnabled(true);
    continuous = false;
}

void MainWindow::radioToneContinuous() {
    ui->edToneTime->setDisabled(true);
    continuous = true;
}

void MainWindow::setFreqsFields(int f1, int f2) {
    ui->edTone1->setText(QString::number(f1) + QString(" Hz"));
    ui->edTone2->setText(QString::number(f2) + QString(" Hz"));
}

void MainWindow::clearFreqsFields() {
    ui->edTone1->clear();
    ui->edTone2->clear();
}

void MainWindow::on_actionAbout_author_triggered()
{
    QString text = "DTMF Tool by Jan \"aso\" Szenborn, SP2ASO<br><br>"
                   "<a href=\"https://github.com/aso824/DTMFtool\">DTMFtool github</a><br>"
                   "<a href=\"http://aso.uh.net.pl\">Author homepage</a><br><br>"
                   "This program is on GNU GPL license. Read LICENSE.txt for more.";
    QMessageBox box(QMessageBox::Information, trUtf8("About author"), text, QMessageBox::Ok, this);
    box.exec();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, trUtf8("About Qt"));
}

void MainWindow::dialerStart() {
    // Block UI elements
    ui->edGeneratorInput->setReadOnly(true);
    ui->grGeneratorParameters->setDisabled(true);

    // Copy and prepare values from UI
    QString input = ui->edGeneratorInput->text().toUpper();
    unsigned short toneTime = ui->edGenToneLength->text().toInt(),
                   toneInterval = ui->edGenToneInterval->text().toInt();

    // Prepare thread
    dialer = new Dialer(this);
    dialer->setParameters(toneTime, toneInterval);
    dialer->setData(input);
    dialer->setTonePlayer(output);

    // Connect dialer to slots
    connect(dialer, SIGNAL(end()), this, SLOT(dialerStopped()));
    connect(dialer, SIGNAL(updateProgress(int)), ui->genProgress, SLOT(setValue(int)));
    connect(ui->genProgress, SIGNAL(valueChanged(int)), this, SLOT(updateDialerProgress(int)));

    // Run
    qDebug() << "Dialer started";
    dialer->start();

}

void MainWindow::dialerStopped() {
    qDebug() << "Dialer stopped";

    ui->edGeneratorInput->setReadOnly(false);
    ui->grGeneratorParameters->setEnabled(true);
}

void MainWindow::updateDialerProgress(int val) {
    ui->genProgress->setValue(val);
    ui->genProgress->update();
    qApp->processEvents();
}
