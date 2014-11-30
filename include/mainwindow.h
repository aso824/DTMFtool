#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QList>
#include <QDebug>
#include <QPushButton>
#include <QTimer>
#include <QIntValidator>
#include <QMessageBox>
#include <QThread>

#include "toneplayer.h"
#include "dialer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TonePlayer *output;
    QThread *outputThread;
    Dialer *dialer;

    bool continuous = false;
    QList<QWidget*> keyboardButtonsList;

    void getKeyboardButtons();
    void connectKeyboardButtons();

private slots:
    void stopTone();

    void buttonPlayToneAction(QString btnName);
    void radioToneSingle();
    void radioToneContinuous();
    void setFreqsFields(int f1, int f2);
    void clearFreqsFields();

    void dialerStart();
    void dialerStopped();
    void updateDialerProgress(int val);

    void on_actionAbout_author_triggered();
    void on_actionAbout_Qt_triggered();

};

#endif // MAINWINDOW_H
