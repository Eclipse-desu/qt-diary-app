#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTextCodec>

#include <QDebug>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("主界面");

    init();

    openAction = new QAction(tr("&Set storage path"), this);

    connect(openAction, &QAction::triggered, this, &MainWindow::changeStoragePath);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);

    QWidget *centralWidget = new QWidget();

// ==================== calendar ====================

    calendar = new QCalendarWidget(this->centralWidget());
    calendar->setMinimumDate(QDate(1900, 1, 1));
    calendar->setMaximumDate(QDate(3000, 1, 1));
    calendar->setGridVisible(true);

    connect(calendar, &QCalendarWidget::clicked, this, &MainWindow::onCalendarClicked);

// ==================== button ====================

    diaryButton = new QPushButton(tr("日记"), this->centralWidget());
    accountingButton = new QPushButton(tr("记账"), this->centralWidget());

    connect(diaryButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);

// ==================== testlabel ====================

    testLabel = new QLabel("");
    testLabel->setMaximumHeight(900);

// ==================== layout ====================

    createCalendarBox();
    createButtonBox();
    createInfoBox();
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(calendarBox, 0, 0);
    layout->addWidget(buttonBox, 1, 0);
    layout->addWidget(infoBox, 0, 1, 2, 1);
    layout->setColumnStretch(1, 1);
//    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setMargin(config->value("UIMain/Margin").toInt());
    layout->setContentsMargins(config->value("UIMain/ContainerMarginL").toInt(),
                               config->value("UIMain/ContainerMarginR").toInt(),
                               config->value("UIMain/ContainerMarginU").toInt(),
                               config->value("UIMain/ContainerMarginD").toInt());
    layout->setVerticalSpacing(10);
    layout->setHorizontalSpacing(10);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    // calendarBox->setColumnMinimumWidth(0, calendar->sizeHint().width());
    setFixedSize(this->sizeHint());
    
}

MainWindow::~MainWindow()
{
}

void MainWindow::init() {
    configPath = QApplication::applicationDirPath() + "/config.ini";
    config = new QSettings(configPath, QSettings::IniFormat);
    config->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if (!QFile::exists(configPath)) {
        config->setValue("System/Storage", QDir::homePath() + "/MyDiary");
        config->setValue("UIMain/Margin", 10);
        config->setValue("UIMain/ContainerMarginL", 0);
        config->setValue("UIMain/ContainerMarginR", 0);
        config->setValue("UIMain/ContainerMarginU", 0);
        config->setValue("UIMain/ContainerMarginD", 0);
        config->sync();
    }
    storagePath = config->value("System/Storage").toString();
}

void MainWindow::changeStoragePath()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("打开文件夹"));

    storagePath = path;
    config->setValue("System/Storage", path);
}

void MainWindow::invokeDiaryWindow(const DataPack& _pack) {
    DiaryWindow *win = new DiaryWindow(_pack, nullptr);
    win->show();
}

void MainWindow::onCalendarClicked(const QDate& date) {
    if (date > QDate::currentDate()) return ;
    QString filePath = storagePath + "/" + date.toString("yyyy'-'MM") + "/" + date.toString("yyyy'-'MM'-'dd") + ".md";
    if (date != QDate::currentDate() && !QFile(filePath).exists()) {
        QMessageBox::warning(this, "提示", QString("%1没有日记哦~").arg(date.toString("yyyy'年'M'月'd'日'")));
        return ;
    }
    invokeDiaryWindow(DataPack(date, storagePath, date == QDate::currentDate() ? true : false));
}

void MainWindow::onStartClicked() {
    invokeDiaryWindow(DataPack(QDate::currentDate(), storagePath, true));
}

void MainWindow::createCalendarBox() {
    calendarBox = new QGroupBox("日历", this->centralWidget());
    QGridLayout *calendarLayout = new QGridLayout;
    calendarLayout->addWidget(calendar, 0, 0, Qt::AlignCenter);
    calendarLayout->setSizeConstraint(QLayout::SetFixedSize);
    calendarBox->setLayout(calendarLayout);
}

void MainWindow::createButtonBox() {
    buttonBox = new QGroupBox(this->centralWidget());
    QGridLayout *buttonLayout = new QGridLayout;
    buttonLayout->addWidget(diaryButton, 0, 0, Qt::AlignCenter);
    buttonLayout->addWidget(accountingButton, 1, 0, Qt::AlignCenter);
    diaryButton->setMinimumWidth(calendar->sizeHint().width());
    accountingButton->setMinimumWidth(diaryButton->minimumWidth());
    buttonLayout->setSizeConstraint(QLayout::SetFixedSize);
    buttonBox->setLayout(buttonLayout);
}

void MainWindow::createInfoBox() {
    infoBox = new QGroupBox("信息", this->centralWidget());
    QGridLayout *infoLayout = new QGridLayout;
    infoLayout->addWidget(testLabel, 0, 0, Qt::AlignCenter);
    testLabel->setMinimumWidth(calendar->sizeHint().width());
    // infoLayout->setSizeConstraint(QLayout::SetFixedSize);
    infoBox->setLayout(infoLayout);
}
