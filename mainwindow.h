#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <stdlib.h>
#include <regex>
#include <thread>
#include <filesystem>
#include <fstream>
#include <pthread.h>
#include <signal.h>
#include <algorithm>

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QTreeView>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <QMessageBox>
#include <QStandardPaths>
#include <QInputDialog>
#include <QLineEdit>
#include <QTimer>

#include <qhotkey.h>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

struct PulseAudioRecordingStream
{
    int index;
    string driver;
    string flags;
    string state;
    string source;
    bool muted;
    string applicationName;
    int processId;
    string processBinary;
};

struct PulseAudioPlaybackStream
{
    int index;
    string applicationName;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    bool isValidDevice(PulseAudioRecordingStream *stream);
    bool loadSources();
    void playSound(string path);
    void clearSoundFiles();
    void saveSoundFiles();
    void loadSoundFiles();
    string getCommandOutput(char cmd[]);
    QListWidget *getActiveView();
    QListWidgetItem *getSelectedItem();
    QListWidget *createTab(QString title);
    void addSoundToView(QFile &file, QListWidget *widget);
    void syncVolume();
    void checkAndChangeVolume(PulseAudioPlaybackStream *stream, int value);
    void registerHotkey(QListWidgetItem* it, QString keys);
    void unregisterHotkey(QListWidgetItem* it);

private slots:
    void on_addTabButton_clicked();
    void on_soundsListWidget_itemDoubleClicked(QListWidgetItem *listWidgetItem);
    void on_refreshAppsButton_clicked();
    void on_stopButton_clicked();
    void on_addSoundButton_clicked();
    void on_removeSoundButton_clicked();
    void on_clearSoundsButton_clicked();
    void on_playSoundButton_clicked();
    void on_setHotkeyButton_clicked();
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_tabBarDoubleClicked(int index);
    void on_addFolderButton_clicked();
    void on_volumeSlider_valueChanged(int value);
};
#endif // MAINWINDOW_H
