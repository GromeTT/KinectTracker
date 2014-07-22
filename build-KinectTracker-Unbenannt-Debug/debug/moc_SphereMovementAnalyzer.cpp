/****************************************************************************
** Meta object code from reading C++ file 'SphereMovementAnalyzer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/Analyzer/inc/SphereMovementAnalyzer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SphereMovementAnalyzer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SphereMovementAnalyzer_t {
    QByteArrayData data[4];
    char stringdata[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SphereMovementAnalyzer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SphereMovementAnalyzer_t qt_meta_stringdata_SphereMovementAnalyzer = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 13),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 6)
    },
    "SphereMovementAnalyzer\0radiusChanged\0"
    "\0radius\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SphereMovementAnalyzer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       1,   20, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06,

 // signals: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::Float, 0x00495103,

 // properties: notify_signal_id
       0,

       0        // eod
};

void SphereMovementAnalyzer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SphereMovementAnalyzer *_t = static_cast<SphereMovementAnalyzer *>(_o);
        switch (_id) {
        case 0: _t->radiusChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SphereMovementAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SphereMovementAnalyzer::radiusChanged)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SphereMovementAnalyzer::staticMetaObject = {
    { &MovementAnalyzer::staticMetaObject, qt_meta_stringdata_SphereMovementAnalyzer.data,
      qt_meta_data_SphereMovementAnalyzer,  qt_static_metacall, 0, 0}
};


const QMetaObject *SphereMovementAnalyzer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SphereMovementAnalyzer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SphereMovementAnalyzer.stringdata))
        return static_cast<void*>(const_cast< SphereMovementAnalyzer*>(this));
    return MovementAnalyzer::qt_metacast(_clname);
}

int SphereMovementAnalyzer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MovementAnalyzer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = radius(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setRadius(*reinterpret_cast< float*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SphereMovementAnalyzer::radiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
