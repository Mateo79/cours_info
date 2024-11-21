#ifndef THREADPHILO_H
#define THREADPHILO_H

#include <QThread>
#include <QMutex>

class ThreadPhilo : public QThread
{
private:
    QMutex * _tabMutex;
    int _max;
    int _number;
    int _compteur;

public:
    ThreadPhilo(int = 0);

    int tempsAleatoire(int min, int max);

    void setMutex(QMutex * = 0);
    void setMax(int = 1);
    void setNumber(int = 0);

    void run();
};

#endif // THREADPHILO_H
