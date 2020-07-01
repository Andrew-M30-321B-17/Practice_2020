#include "thclass.h"
#include <QDebug>
#include <QMutex>


void thclass::run()
{
for(int i = 0; i <= 100; i++)
{
emit send(i);
    QMutex mutex;
    mutex.lock();
    mutex.tryLock(2000);
    mutex.unlock();
}
}
