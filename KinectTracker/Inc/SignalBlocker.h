#ifndef SIGNALBLOCKER_H
#define SIGNALBLOCKER_H

class QObject;

class SignalBlocker
{
public:
    SignalBlocker( QObject* object );
    ~SignalBlocker();

private:
    QObject* mp_object;
};

#endif // SIGNALBLOCKER_H
