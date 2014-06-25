#include "../inc/ConnectionHelper.h"

/*!
   \brief ConnectionHelper::ConnectionHelper
   Disconnects the objects.
 */
ConnectionHelper::ConnectionHelper( QObject* signalObject,
                                    QMetaMethod& signal,
                                    QObject* slotObject,
                                    QMetaMethod& slot )
    : mp_signalObject( signalObject )
    , m_signal( signal )
    , mp_slotObject( slotObject )
    , m_slot( slot )
{
    QObject::disconnect( mp_signalObject, m_signal, mp_slotObject, m_slot );
}

/*!
   \brief ConnectionHelper::~ConnectionHelper
   Connects the objects.
 */
ConnectionHelper::~ConnectionHelper()
{
    QObject::connect( mp_signalObject, m_signal, mp_slotObject, m_slot );
}
