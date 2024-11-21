#include <QtCore/QCoreApplication>
#include <QMutex>

#include "threadphilo.h"

#define N 10

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ThreadPhilo tabPhilo[N];
    QMutex      tabMutex[N];

    for (int i = 0; i < N; ++i)
    {
        tabPhilo[i].setMutex(tabMutex);
        tabPhilo[i].setMax(N);
        tabPhilo[i].setNumber(i);
        tabPhilo[i].start();
    }

    return a.exec();
}
