#ifndef CONNECTIONHELPER_H
#define CONNECTIONHELPER_H

#include <QMetaMethod>
#include <QMetaProperty>

class QObject;

class ConnectionHelper
{
public:
    ConnectionHelper( QObject* signalObject,
                      QMetaMethod& signal,
                      QObject* slotObject,
                      QMetaMethod& slot );
    ~ConnectionHelper();

private:
    QObject*        mp_signalObject;
    QMetaMethod&    m_signal;
    QObject*        mp_slotObject;
    QMetaMethod     m_slot;
};

#endif // CONNECTIONHELPER_H
