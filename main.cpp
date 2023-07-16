#include "mainwindow.h"

#include <QApplication>

#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow win;
    // win.resize(1600, 900);
    win.show();
    return app.exec();
}
