/****************************************************************************
** Meta object code from reading C++ file 'BBMovementAnalyzer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/Analyzer/inc/BBMovementAnalyzer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BBMovementAnalyzer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BBMovementAnalyzer_t {
    QByteArrayData data[8];
    char stringdata[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_BBMovementAnalyzer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_BBMovementAnalyzer_t qt_meta_stringdata_BBMovementAnalyzer = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 13),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 13),
QT_MOC_LITERAL(4, 48, 13),
QT_MOC_LITERAL(5, 62, 6),
QT_MOC_LITERAL(6, 69, 6),
QT_MOC_LITERAL(7, 76, 6)
    },
    "BBMovementAnalyzer\0deltaXChanged\0\0"
    "deltaYChanged\0deltaZChanged\0deltaX\0"
    "deltaY\0deltaZ\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BBMovementAnalyzer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       3,   32, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06,
       3,    0,   30,    2, 0x06,
       4,    0,   31,    2, 0x06,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       5, QMetaType::Float, 0x00495103,
       6, QMetaType::Float, 0x00495103,
       7, QMetaType::Float, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void BBMovementAnalyzer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BBMovementAnalyzer *_t = static_cast<BBMovementAnalyzer *>(_o);
        switch (_id) {
        case 0: _t->deltaXChanged(); break;
        case 1: _t->deltaYChanged(); break;
        case 2: _t->deltaZChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BBMovementAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BBMovementAnalyzer::deltaXChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (BBMovementAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BBMovementAnalyzer::deltaYChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (BBMovementAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BBMovementAnalyzer::deltaZChanged)) {
                *result = 2;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject BBMovementAnalyzer::staticMetaObject = {
    { &MovementAnalyzer::staticMetaObject, qt_meta_stringdata_BBMovementAnalyzer.data,
      qt_meta_data_BBMovementAnalyzer,  qt_static_metacall, 0, 0}
};


const QMetaObject *BBMovementAnalyzer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BBMovementAnalyzer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BBMovementAnalyzer.stringdata))
        return static_cast<void*>(const_cast< BBMovementAnalyzer*>(this));
    return MovementAnalyzer::qt_metacast(_clname);
}

int BBMovementAnalyzer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MovementAnalyzer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = deltaX(); break;
        case 1: *reinterpret_cast< float*>(_v) = deltaY(); break;
        case 2: *reinterpret_cast< float*>(_v) = deltaZ(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setDeltaX(*reinterpret_cast< float*>(_v)); break;
        case 1: setDeltaY(*reinterpret_cast< float*>(_v)); break;
        case 2: setDeltaZ(*reinterpret_cast< float*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void BBMovementAnalyzer::deltaXChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void BBMovementAnalyzer::deltaYChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void BBMovementAnalyzer::deltaZChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
