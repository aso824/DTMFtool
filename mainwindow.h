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

#include <map>

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

    QList<QWidget*> keyboardButtonsList;
    std::map<char, std::pair<unsigned short, unsigned short>> keyLayoutMap;

    void createKeyLayoutMap();
    void initAudio();
    void playTone(char key);

    void getKeyboardButtons();
    void connectKeyboardButtons(bool continuous = false);

private slots:
    void buttonPlaySingleTone(QString btnName);
    void stopTone();

};

#endif // MAINWINDOW_H
