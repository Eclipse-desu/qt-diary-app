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
    mainView = new QSplitter;
    textEdit = new QPlainTextEdit;
    markdownView = new QTextEdit;
    markdownDoc = new QTextDocument;
    mainView->addWidget(textEdit);
    mainView->addWidget(markdownView);
    saveButton = new QPushButton("保存");

    connect(saveButton, &QPushButton::clicked, this, &DiaryWindow::saveFile);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    // mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(titleBox);
    mainLayout->addWidget(mainView);
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
    // titleBox->setFlat(true);

    dateLabel = new QLabel(curDate.toString("yyyy'年'M'月'd'日'"), this);
    titleEdit = new QLineEdit;

    QFormLayout* titleLayout = new QFormLayout;
    titleLayout->addRow(dateLabel, titleEdit);
    // titleLayout->setContentsMargins(0, 0, 0, 0);
    titleBox->setLayout(titleLayout);
    titleBox->setFixedHeight(titleLayout->sizeHint().height());
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
    QString doc = in.readAll();
    textEdit->setPlainText(doc);
    markdownDoc->setMarkdown(doc);
    markdownView->setDocument(markdownDoc);
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