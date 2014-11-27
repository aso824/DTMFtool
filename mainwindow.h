#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include "generator.h"
#include "freqs.h"

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

    QAudioDeviceInfo device;
    QAudioOutput *output;
    QAudioFormat format;
    Generator *generator;

    void initAudio();

};

#endif // MAINWINDOW_H
