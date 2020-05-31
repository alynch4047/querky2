#include "main_window.h"
#include <QtWidgets/QApplication>
#include <QtGui/QFont>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_Use96Dpi);

    QApplication a(argc, argv);

    QFont font = qApp->font();
    font.setPixelSize(12);
    qApp->setFont(font);

    MainWindow w;
    w.show();
    return a.exec();
}
