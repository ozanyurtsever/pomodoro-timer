#include "pomodorotimer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PomodoroTimer w;
    w.show();

    return a.exec();
}
