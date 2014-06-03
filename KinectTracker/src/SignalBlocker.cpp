#include "../Inc/SignalBlocker.h"
#include <QObject>

SignalBlocker::SignalBlocker( QObject* object )
    : mp_object( object )

{
    Q_ASSERT( mp_object );
    mp_object->blockSignals( true );
}

SignalBlocker::~SignalBlocker()
{
    Q_ASSERT( mp_object );
    mp_object->blockSignals( false );
}
