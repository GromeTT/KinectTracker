/****************************************************************************
** Meta object code from reading C++ file 'SizeAnalyzer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/Analyzer/inc/SizeAnalyzer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SizeAnalyzer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SizeAnalyzer_t {
    QByteArrayData data[19];
    char stringdata[371];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SizeAnalyzer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SizeAnalyzer_t qt_meta_stringdata_SizeAnalyzer = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 24),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 22),
QT_MOC_LITERAL(4, 62, 19),
QT_MOC_LITERAL(5, 82, 24),
QT_MOC_LITERAL(6, 107, 21),
QT_MOC_LITERAL(7, 129, 28),
QT_MOC_LITERAL(8, 158, 27),
QT_MOC_LITERAL(9, 186, 24),
QT_MOC_LITERAL(10, 211, 17),
QT_MOC_LITERAL(11, 229, 17),
QT_MOC_LITERAL(12, 247, 15),
QT_MOC_LITERAL(13, 263, 12),
QT_MOC_LITERAL(14, 276, 17),
QT_MOC_LITERAL(15, 294, 14),
QT_MOC_LITERAL(16, 309, 21),
QT_MOC_LITERAL(17, 331, 20),
QT_MOC_LITERAL(18, 352, 17)
    },
    "SizeAnalyzer\0estimatedBodySizeChanged\0"
    "\0currentBodySizeChanged\0workerStatusChanged\0"
    "kneelingThresholdChanged\0lyingThresholdChanged\0"
    "distanceHeadRightFoodChanged\0"
    "distanceHeadLeftFoodChanged\0"
    "distanceFloorHeadChanged\0assumptionChanged\0"
    "estimatedBodySize\0currentBodySize\0"
    "workerStatus\0kneelingThreshold\0"
    "lyingThreshold\0distanceHeadRightFood\0"
    "distanceHeadLeftFood\0distanceFloorHead\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SizeAnalyzer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       8,   68, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06,
       3,    0,   60,    2, 0x06,
       4,    0,   61,    2, 0x06,
       5,    0,   62,    2, 0x06,
       6,    0,   63,    2, 0x06,
       7,    0,   64,    2, 0x06,
       8,    0,   65,    2, 0x06,
       9,    0,   66,    2, 0x06,
      10,    0,   67,    2, 0x06,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      11, QMetaType::Float, 0x00495001,
      12, QMetaType::Float, 0x00495001,
      13, QMetaType::QString, 0x00495001,
      14, QMetaType::Float, 0x00495103,
      15, QMetaType::Float, 0x00495103,
      16, QMetaType::Float, 0x00495001,
      17, QMetaType::Float, 0x00495001,
      18, QMetaType::Float, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,

       0        // eod
};

void SizeAnalyzer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SizeAnalyzer *_t = static_cast<SizeAnalyzer *>(_o);
        switch (_id) {
        case 0: _t->estimatedBodySizeChanged(); break;
        case 1: _t->currentBodySizeChanged(); break;
        case 2: _t->workerStatusChanged(); break;
        case 3: _t->kneelingThresholdChanged(); break;
        case 4: _t->lyingThresholdChanged(); break;
        case 5: _t->distanceHeadRightFoodChanged(); break;
        case 6: _t->distanceHeadLeftFoodChanged(); break;
        case 7: _t->distanceFloorHeadChanged(); break;
        case 8: _t->assumptionChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SizeAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SizeAnalyzer::estimatedBodySizeChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (SizeAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SizeAnalyzer::currentBodySizeChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (SizeAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SizeAnalyzer::workerStatusChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (SizeAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SizeAnalyzer::kneelingThresholdChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (SizeAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SizeAnalyzer::lyingThresholdChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (SizeAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SizeAnalyzer::distanceHeadRightFoodChanged)) {
                *result = 5;
            }
        }
        {
            typedef void (SizeAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SizeAnalyzer::distanceHeadLeftFoodChanged)) {
                *result = 6;
            }
        }
        {
            typedef void (SizeAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SizeAnalyzer::distanceFloorHeadChanged)) {
                *result = 7;
            }
        }
        {
            typedef void (SizeAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SizeAnalyzer::assumptionChanged)) {
                *result = 8;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SizeAnalyzer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SizeAnalyzer.data,
      qt_meta_data_SizeAnalyzer,  qt_static_metacall, 0, 0}
};


const QMetaObject *SizeAnalyzer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SizeAnalyzer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SizeAnalyzer.stringdata))
        return static_cast<void*>(const_cast< SizeAnalyzer*>(this));
    return QObject::qt_metacast(_clname);
}

int SizeAnalyzer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = estimatedBodySize(); break;
        case 1: *reinterpret_cast< float*>(_v) = currentBodySize(); break;
        case 2: *reinterpret_cast< QString*>(_v) = workerStatusToString(); break;
        case 3: *reinterpret_cast< float*>(_v) = kneelingThreshold(); break;
        case 4: *reinterpret_cast< float*>(_v) = lyingThreshold(); break;
        case 5: *reinterpret_cast< float*>(_v) = distanceHeadRightFood(); break;
        case 6: *reinterpret_cast< float*>(_v) = distanceHeadLeftFood(); break;
        case 7: *reinterpret_cast< float*>(_v) = distanceFloorHead(); break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 3: setKneelingThreshold(*reinterpret_cast< float*>(_v)); break;
        case 4: setLyingThreshold(*reinterpret_cast< float*>(_v)); break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SizeAnalyzer::estimatedBodySizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SizeAnalyzer::currentBodySizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SizeAnalyzer::workerStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SizeAnalyzer::kneelingThresholdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void SizeAnalyzer::lyingThresholdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void SizeAnalyzer::distanceHeadRightFoodChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void SizeAnalyzer::distanceHeadLeftFoodChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void SizeAnalyzer::distanceFloorHeadChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void SizeAnalyzer::assumptionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE
