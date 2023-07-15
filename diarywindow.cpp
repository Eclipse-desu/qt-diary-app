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

DiaryWindow::DiaryWindow(const DataPack& _pack, QWidget *parent) :
    QWidget(parent)
{
    // this->setWindowTitle("日记");
    curDate = _pack.curDate;
    storagePath = _pack.storagePath;
    editable = _pack.editable;

    createTitleBox();
    textEdit = new QPlainTextEdit;
    saveButton = new QPushButton("保存");

    connect(saveButton, &QPushButton::clicked, this, &DiaryWindow::saveFile);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleBox);
    mainLayout->addWidget(textEdit);
    mainLayout->addWidget(saveButton);
    this->setLayout(mainLayout);

    loadFile();
    this->resize(800, 900);
}

DiaryWindow::~DiaryWindow() {
}

void DiaryWindow::createTitleBox() {
    // qDebug() << "pass1";
    titleBox = new QGroupBox;
    titleBox->setFlat(true);

    dateLabel = new QLabel(curDate.toString("yyyy'年'M'月'd'日'"), this);
    titleEdit = new QLineEdit;

    QFormLayout* titleLayout = new QFormLayout;
    titleLayout->addRow(dateLabel, titleEdit);
    titleBox->setLayout(titleLayout);
    // qDebug() << "pass2";
}

void DiaryWindow::loadFile() {
    QString filePath = storagePath + "/" + curDate.toString("yyyy'-'MM") + "/" + curDate.toString("yyyy'-'MM'-'dd") + ".md";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text) && curDate != QDate::currentDate()) {
        QMessageBox::warning(this, tr("错误"),
            tr("打开日记文件失败, 应打开文件:\n%1").arg(filePath));
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    textEdit->setPlainText(in.readAll());
    // qDebug() << editable;
    textEdit->setReadOnly(!editable);
    file.close();
}

void DiaryWindow::saveFile() {
    QString folderPath = storagePath + "/" + curDate.toString("yyyy'-'MM");
    QDir folder;
    if (!folder.exists(folderPath)) {
        folder.mkpath(folderPath);
    }
    QString filePath = folderPath + "/" + curDate.toString("yyyy'-'MM'-'dd") + ".md";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"),
            tr("打开日记文件失败, 应打开文件:\n%1").arg(filePath));
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << textEdit->toPlainText();
    file.close();
    this->close();
}