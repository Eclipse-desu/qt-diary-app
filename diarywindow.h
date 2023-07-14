#ifndef DIARYWINDOW_H
#define DIARYWINDOW_H

#include <QWidget>
#include <QSettings>

// widgets
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

// layouts
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>

class DiaryWindow : public QWidget
{
    Q_OBJECT
public:
    DiaryWindow(QWidget *parent = 0);
    ~DiaryWindow();

private:
    void createTextBox();
    void createTitleBox();
    void createbuttonBox();

    void saveFile();
    
    QLabel dateLabel;
    QLineEdit *titleEdit;
    QTextEdit *textEdit;
    QPushButton *saveButton;

    QGroupBox *textBox, *titleBox, *buttonBox;

signals:
    void askStoragePath();

private slots:
    void stringMainwindow(const QString&);
};
#endif // DIARYWINDOW_H