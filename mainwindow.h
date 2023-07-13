#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QCalendarWidget>

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
    void openFile();
    void saveFile();
    QAction *openAction, *saveAction;
    QTextEdit *textEdit;
    QCalendarWidget *calendar;
private slots:
    void onCalendarClicked(const QDate&);
};
#endif // MAINWINDOW_H