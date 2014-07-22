/****************************************************************************
** Meta object code from reading C++ file 'Threshold.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/ProcessingPipelines/inc/Threshold.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Threshold.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Threshold_t {
    QByteArrayData data[14];
    char stringdata[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Threshold_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Threshold_t qt_meta_stringdata_Threshold = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 15),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 16),
QT_MOC_LITERAL(4, 44, 20),
QT_MOC_LITERAL(5, 65, 8),
QT_MOC_LITERAL(6, 74, 9),
QT_MOC_LITERAL(7, 84, 13),
QT_MOC_LITERAL(8, 98, 13),
QT_MOC_LITERAL(9, 112, 13),
QT_MOC_LITERAL(10, 126, 17),
QT_MOC_LITERAL(11, 144, 12),
QT_MOC_LITERAL(12, 157, 13),
QT_MOC_LITERAL(13, 171, 17)
    },
    "Threshold\0maxValueChanged\0\0thresholdChanged\0"
    "thresholdTypeChanged\0maxValue\0threshold\0"
    "thresholdType\0ThresholdType\0Thresh_Binary\0"
    "Thresh_Binary_Inv\0Thresh_Trunc\0"
    "Thresh_ToZero\0Thresh_ToZero_Inv\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Threshold[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       3,   32, // properties
       1,   44, // enums/sets
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
       5, QMetaType::Double, 0x00495103,
       6, QMetaType::Double, 0x00495103,
       7, 0x80000000 | 8, 0x0049510b,

 // properties: notify_signal_id
       0,
       1,
       2,

 // enums: name, flags, count, data
       8, 0x0,    5,   48,

 // enum data: key, value
       9, uint(Threshold::Thresh_Binary),
      10, uint(Threshold::Thresh_Binary_Inv),
      11, uint(Threshold::Thresh_Trunc),
      12, uint(Threshold::Thresh_ToZero),
      13, uint(Threshold::Thresh_ToZero_Inv),

       0        // eod
};

void Threshold::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Threshold *_t = static_cast<Threshold *>(_o);
        switch (_id) {
        case 0: _t->maxValueChanged(); break;
        case 1: _t->thresholdChanged(); break;
        case 2: _t->thresholdTypeChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Threshold::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Threshold::maxValueChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (Threshold::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Threshold::thresholdChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (Threshold::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Threshold::thresholdTypeChanged)) {
                *result = 2;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Threshold::staticMetaObject = {
    { &ProcessingComponent::staticMetaObject, qt_meta_stringdata_Threshold.data,
      qt_meta_data_Threshold,  qt_static_metacall, 0, 0}
};


const QMetaObject *Threshold::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Threshold::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Threshold.stringdata))
        return static_cast<void*>(const_cast< Threshold*>(this));
    return ProcessingComponent::qt_metacast(_clname);
}

int Threshold::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProcessingComponent::qt_metacall(_c, _id, _a);
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
        case 0: *reinterpret_cast< double*>(_v) = maxValue(); break;
        case 1: *reinterpret_cast< double*>(_v) = threshold(); break;
        case 2: *reinterpret_cast< ThresholdType*>(_v) = thresholdType(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setMaxValue(*reinterpret_cast< double*>(_v)); break;
        case 1: setThreshold(*reinterpret_cast< double*>(_v)); break;
        case 2: setThresholdType(*reinterpret_cast< ThresholdType*>(_v)); break;
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
void Threshold::maxValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Threshold::thresholdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Threshold::thresholdTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
