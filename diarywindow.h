#ifndef DIARYWINDOW_H
#define DIARYWINDOW_H

#include <QDate>
#include <QWidget>
#include <QSettings>

// widgets
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>

// layouts
#include <QGroupBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class DataPack {
public:
    QDate curDate;
    QString storagePath;
    bool editable;

    DataPack(const QDate& _date, const QString& _dir, bool _able) : curDate(_date), storagePath(_dir), editable(_able) {}
};

class DiaryWindow : public QWidget
{
    Q_OBJECT
public:
    DiaryWindow(const DataPack& _pack, QWidget *parent = 0);
    ~DiaryWindow();

private:
    void createTitleBox();

    void loadFile();
    void saveFile();
    
    QDate curDate;
    QString storagePath;
    bool editable;

    QLabel *dateLabel;
    QLineEdit *titleEdit;
    QPlainTextEdit *textEdit;
    QPushButton *saveButton;

    QGroupBox *titleBox;

signals:
    void askStoragePath();

// private slots:
    // void stringMainwindow(const QString&);
};
#endif // DIARYWINDOW_H