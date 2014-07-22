/****************************************************************************
** Meta object code from reading C++ file 'Erode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/ProcessingPipelines/inc/Erode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Erode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Erode_t {
    QByteArrayData data[12];
    char stringdata[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Erode_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Erode_t qt_meta_stringdata_Erode = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 19),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 19),
QT_MOC_LITERAL(4, 47, 17),
QT_MOC_LITERAL(5, 65, 21),
QT_MOC_LITERAL(6, 87, 24),
QT_MOC_LITERAL(7, 112, 12),
QT_MOC_LITERAL(8, 125, 12),
QT_MOC_LITERAL(9, 138, 10),
QT_MOC_LITERAL(10, 149, 14),
QT_MOC_LITERAL(11, 164, 17)
    },
    "Erode\0anchorPointXChanged\0\0"
    "anchorPointYChanged\0iterationsChanged\0"
    "kernelRowCountChanged\0kernelColumnCountChanged\0"
    "anchorPointX\0anchorPointY\0iterations\0"
    "kernelRowCount\0kernelColumnCount\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Erode[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       5,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06,
       3,    0,   40,    2, 0x06,
       4,    0,   41,    2, 0x06,
       5,    0,   42,    2, 0x06,
       6,    0,   43,    2, 0x06,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::Float, 0x00495103,
       8, QMetaType::Float, 0x00495103,
       9, QMetaType::Int, 0x00495103,
      10, QMetaType::Int, 0x00495103,
      11, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void Erode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Erode *_t = static_cast<Erode *>(_o);
        switch (_id) {
        case 0: _t->anchorPointXChanged(); break;
        case 1: _t->anchorPointYChanged(); break;
        case 2: _t->iterationsChanged(); break;
        case 3: _t->kernelRowCountChanged(); break;
        case 4: _t->kernelColumnCountChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Erode::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Erode::anchorPointXChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (Erode::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Erode::anchorPointYChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (Erode::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Erode::iterationsChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (Erode::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Erode::kernelRowCountChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (Erode::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Erode::kernelColumnCountChanged)) {
                *result = 4;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Erode::staticMetaObject = {
    { &ProcessingComponent::staticMetaObject, qt_meta_stringdata_Erode.data,
      qt_meta_data_Erode,  qt_static_metacall, 0, 0}
};


const QMetaObject *Erode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Erode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Erode.stringdata))
        return static_cast<void*>(const_cast< Erode*>(this));
    return ProcessingComponent::qt_metacast(_clname);
}

int Erode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProcessingComponent::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = anchorPointX(); break;
        case 1: *reinterpret_cast< float*>(_v) = anchorPointY(); break;
        case 2: *reinterpret_cast< int*>(_v) = iterations(); break;
        case 3: *reinterpret_cast< int*>(_v) = kernelRowCount(); break;
        case 4: *reinterpret_cast< int*>(_v) = kernelColumnCount(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setAnchorPointX(*reinterpret_cast< float*>(_v)); break;
        case 1: setAnchorPointY(*reinterpret_cast< float*>(_v)); break;
        case 2: setIterations(*reinterpret_cast< int*>(_v)); break;
        case 3: setKernelRowCount(*reinterpret_cast< int*>(_v)); break;
        case 4: setKernelColumnCount(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Erode::anchorPointXChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Erode::anchorPointYChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Erode::iterationsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Erode::kernelRowCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Erode::kernelColumnCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
