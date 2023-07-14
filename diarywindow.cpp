#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTextCodec>

#include <QDebug>

#include "diarywindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("Main Window"));

    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the current file"));

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveAction);

    QWidget *centralWidget = new QWidget();

    // textEdit = new QTextEdit(centralWidget);
    // setCentralWidget(textEdit);

    calendar = new QCalendarWidget(centralWidget);
    calendar->setMinimumDate(QDate(1900, 1, 1));
    calendar->setMaximumDate(QDate(3000, 1, 1));
    calendar->setGridVisible(true);
    // calendar->setMinimumSize(300, 200);

    QGroupBox *calendarBox = new QGroupBox(centralWidget);
    QGridLayout *calendarLayout = new QGridLayout;
    calendarLayout->addWidget(calendar, 0, 0, Qt::AlignCenter);
    calendarLayout->setSizeConstraint(QLayout::SetFixedSize);
    calendarBox->setLayout(calendarLayout);

    connect(calendar, &QCalendarWidget::clicked, this, &MainWindow::onCalendarClicked);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(calendarBox, 0, 0);
    layout->addWidget(textEdit, 0, 1);
//    layout->setSizeConstraint(QLayout::SetFixedSize);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    // std::cout << calendar->width() << "," << calendar->height() << std::endl;
    calendar->resize(50, 300);
    // qDebug() << calendar->width() << "," << calendar->height();


}

MainWindow::~MainWindow()
{
}

/*
QSettings settings("Config.ini", QSettings::IniFormat);
settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
if (!QFile::exists("Config.ini"))
{
    settings.setValue("UI/height", 0.8);
    settings.setValue("UI/width", 0.2);
    settings.setValue("System/font", "Microsoft YaHei");
    settings.sync();
}
_height = settings.value("UI/height").toDouble();
_width = settings.value("UI/width").toDouble();
_font = settings.value("System/font").toString();
*/

void MainWindow::init() {
    configPath = QApplication::applicationDirPath() + "/config.ini";
    QSettings config(configPath, QSettings::IniFormat);
    config.setIniCodec(QTextCodec::codecForName("UTF-8"));
    if (!QFile::exists(configPath)) {
        config.setValue("System/Storage", QDir::homePath());
        config.sync();
    }
    storagePath = new QDir(config.value("System/Storage").toString());
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.md)"));

    if (!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
            return ;
        }

        QTextStream in(&file);
        in.setCodec(QTextCodec::codecForName("utf-8"));
        textEdit->setText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You didn't select any file."));
    }
}

void MainWindow::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Markdown Files(*.md)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"),
                                       tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
}

void MainWindow::onCalendarClicked(const QDate& date) {
    textEdit->setText(date.toString());
}