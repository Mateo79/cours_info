#include "threadphilo.h"

#include <QTextStream>
#include <QTime>

ThreadPhilo::ThreadPhilo(int n)
    : _number(n), _compteur(0)
{
}

int ThreadPhilo::tempsAleatoire(int min, int max) {
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec() +_number);
    return qrand() % ((max + 1) - min) + min;
}

void ThreadPhilo::setMutex(QMutex * t)
{
    _tabMutex = t;
}

void ThreadPhilo::setMax(int m)
{
    _max = m;
}

void ThreadPhilo::setNumber(int n)
{
    _number = n;
}

void ThreadPhilo::run()
{
    QTextStream out(stdout);

    int gauche = _number;
    int droit  = _number - 1;

    if (_number == 0) droit = _max - 1;

    while (true)
    {
        out << "philosophe " << _number << " reveil" << endl;
        if (_tabMutex[gauche].tryLock(2)) {
            _tabMutex[droit].lock();
            out << "philosophe " << _number << " mange";
            _compteur++;
            for(int i = 0; i < _compteur; i++) out << '.';
            out << endl;
            msleep(tempsAleatoire(500,1000));
            _tabMutex[gauche].unlock();
            _tabMutex[droit].unlock();
        }
        out << "philosophe " << _number << " dort" << endl;
        msleep(tempsAleatoire(500,1000));
    }
 }





