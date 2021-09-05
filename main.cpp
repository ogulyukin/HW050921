#include "homwwork.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomwWork w;
    w.show();
    return a.exec();
}
