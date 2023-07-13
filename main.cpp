#include "mainwindow.h"

#include <QApplication>

#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow win;
    win.resize(1600, 900);
    win.show();
    return app.exec();
}
// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);
//     QWidget window;
//     window.setWindowTitle("Enter your age");
//     QSpinBox *spinBox = new QSpinBox(&window);
//     QSlider *slider = new QSlider(Qt::Horizontal, &window);
//     spinBox->setRange(0, 130);
//     slider->setRange(0, 130);
//     QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
//     void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
//     QObject::connect(spinBox, spinBoxSignal, slider, &QSlider::setValue);
//     spinBox->setValue(35);
//     QHBoxLayout *layout = new QHBoxLayout;
//     layout->addWidget(spinBox);
//     layout->addWidget(slider);
//     window.setLayout(layout);
//     window.show();
//     return app.exec();
// }