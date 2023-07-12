#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QHBoxLayout>

#include "mainwindow.h"

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

    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    calendar = new QCalendarWidget(this);
    calendar->setGridVisible(true);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(calendar);
    layout->setSpacing(100);
    this->setLayout(layout);
}

MainWindow::~MainWindow()
{
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