#include <QCoreApplication>
#include "JoystickMonitor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JoystickMonitor monitor;
    return a.exec();
}
