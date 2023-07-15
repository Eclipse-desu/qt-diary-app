#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFile>
#include <QSettings>
#include <QApplication>
#include <QMainWindow>

// widgets
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QCalendarWidget>

// layouts
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>

#include <diarywindow.h>

QT_BEGIN_NAMESPACE
class QCalendarWidget;
class QCheckBox;
class QComboBox;
class QDate;
class QDateEdit;
class QGridLayout;
class QGroupBox;
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    // initialize the program, fetch some data from config.ini
    void init();

    // change the storage path of diarys and accounting data.
    // When changed, data will be copied from the old file to the newer one. (not implemented)
    void changeStoragePath();

    // start a diary window. with three parameters transfered by a datapack.
    // 1. curDate: determines which date to be read.
    void invokeDiaryWindow(const DataPack&);
    void createCalendarBox();
    void createButtonBox();
    void createInfoBox();

    QSettings *config;
    QString configPath;
    QString storagePath;

    QAction *openAction;

    QLabel *testLabel;
    QPushButton *diaryButton, *accountingButton;
    QCalendarWidget *calendar;

    QGroupBox *calendarBox, *buttonBox, *infoBox;
private slots:
    void onCalendarClicked(const QDate&);
    void onStartClicked();
};
#endif // MAINWINDOW_H