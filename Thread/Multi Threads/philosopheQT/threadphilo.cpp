#include "threadphilo.h"
#include <QTextStream>
#include <QTime>

ThreadPhilo::ThreadPhilo(int n)
    : number(n), compteur(0)
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());
}

int ThreadPhilo::tempsAleatoire(int min, int max) {
    return qrand() % ((max + 1) - min) + min;
}

void ThreadPhilo::setMutex(QMutex * t)
{
    tabMutex = t;
}

void ThreadPhilo::setMax(int m)
{
    max = m;
}

void ThreadPhilo::setNumber(int n)
{
    number = n;
}

void ThreadPhilo::run()
{
    QTextStream out(stdout);
    while (true)
    {
        int gauche = number;
        int droite = number + 1;

        /* cyclique */
        if (droite == max) droite = 0;

        out << "philosophe " << number << " attend." << endl;
        tabMutex[gauche].lock();

        if (tabMutex[droite].tryLock(tempsAleatoire(1, 4)))
        {
            out << "philosophe " << number << " mange.";
            for (int i = 0; i < compteur; ++i) out << ".";
            out << endl;
            ++compteur;
            sleep(tempsAleatoire(1, 10));
            tabMutex[droite].unlock();
        }
        else
        {
            out << "philosophe " << number << " ne mange pas." << endl;
        }

        tabMutex[gauche].unlock();
        out << "philosophe " << number << " pense." << endl;
        sleep(2);
    }
    //exec();
}
