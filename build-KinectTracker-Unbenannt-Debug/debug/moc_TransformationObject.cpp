/****************************************************************************
** Meta object code from reading C++ file 'TransformationObject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/OpenGL/inc/TransformationObject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TransformationObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TransformationObject_t {
    QByteArrayData data[22];
    char stringdata[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TransformationObject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TransformationObject_t qt_meta_stringdata_TransformationObject = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 8),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 8),
QT_MOC_LITERAL(4, 40, 8),
QT_MOC_LITERAL(5, 49, 11),
QT_MOC_LITERAL(6, 61, 12),
QT_MOC_LITERAL(7, 74, 10),
QT_MOC_LITERAL(8, 85, 13),
QT_MOC_LITERAL(9, 99, 13),
QT_MOC_LITERAL(10, 113, 13),
QT_MOC_LITERAL(11, 127, 14),
QT_MOC_LITERAL(12, 142, 1),
QT_MOC_LITERAL(13, 144, 1),
QT_MOC_LITERAL(14, 146, 1),
QT_MOC_LITERAL(15, 148, 4),
QT_MOC_LITERAL(16, 153, 3),
QT_MOC_LITERAL(17, 157, 5),
QT_MOC_LITERAL(18, 163, 6),
QT_MOC_LITERAL(19, 170, 6),
QT_MOC_LITERAL(20, 177, 6),
QT_MOC_LITERAL(21, 184, 7)
    },
    "TransformationObject\0xChanged\0\0yChanged\0"
    "zChanged\0rollChanged\0pitchChanged\0"
    "yawChanged\0xScaleChanged\0yScaleChanged\0"
    "zScaleChanged\0visibleChanged\0x\0y\0z\0"
    "roll\0yaw\0pitch\0xScale\0yScale\0zScale\0"
    "visible\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransformationObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
      10,   74, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06,
       3,    0,   65,    2, 0x06,
       4,    0,   66,    2, 0x06,
       5,    0,   67,    2, 0x06,
       6,    0,   68,    2, 0x06,
       7,    0,   69,    2, 0x06,
       8,    0,   70,    2, 0x06,
       9,    0,   71,    2, 0x06,
      10,    0,   72,    2, 0x06,
      11,    0,   73,    2, 0x06,

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
    QMetaType::Void,

 // properties: name, type, flags
      12, QMetaType::Float, 0x00495103,
      13, QMetaType::Float, 0x00495103,
      14, QMetaType::Float, 0x00495103,
      15, QMetaType::Float, 0x00495103,
      16, QMetaType::Float, 0x00495103,
      17, QMetaType::Float, 0x00495103,
      18, QMetaType::Float, 0x00495003,
      19, QMetaType::Float, 0x00495003,
      20, QMetaType::Float, 0x00495003,
      21, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       5,
       4,
       6,
       7,
       8,
       9,

       0        // eod
};

void TransformationObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TransformationObject *_t = static_cast<TransformationObject *>(_o);
        switch (_id) {
        case 0: _t->xChanged(); break;
        case 1: _t->yChanged(); break;
        case 2: _t->zChanged(); break;
        case 3: _t->rollChanged(); break;
        case 4: _t->pitchChanged(); break;
        case 5: _t->yawChanged(); break;
        case 6: _t->xScaleChanged(); break;
        case 7: _t->yScaleChanged(); break;
        case 8: _t->zScaleChanged(); break;
        case 9: _t->visibleChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TransformationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformationObject::xChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (TransformationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformationObject::yChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (TransformationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformationObject::zChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (TransformationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformationObject::rollChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (TransformationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformationObject::pitchChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (TransformationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformationObject::yawChanged)) {
                *result = 5;
            }
        }
        {
            typedef void (TransformationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformationObject::xScaleChanged)) {
                *result = 6;
            }
        }
        {
            typedef void (TransformationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformationObject::yScaleChanged)) {
                *result = 7;
            }
        }
        {
            typedef void (TransformationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformationObject::zScaleChanged)) {
                *result = 8;
            }
        }
        {
            typedef void (TransformationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformationObject::visibleChanged)) {
                *result = 9;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TransformationObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TransformationObject.data,
      qt_meta_data_TransformationObject,  qt_static_metacall, 0, 0}
};


const QMetaObject *TransformationObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransformationObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TransformationObject.stringdata))
        return static_cast<void*>(const_cast< TransformationObject*>(this));
    return QObject::qt_metacast(_clname);
}

int TransformationObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = x(); break;
        case 1: *reinterpret_cast< float*>(_v) = y(); break;
        case 2: *reinterpret_cast< float*>(_v) = z(); break;
        case 3: *reinterpret_cast< float*>(_v) = roll(); break;
        case 4: *reinterpret_cast< float*>(_v) = yaw(); break;
        case 5: *reinterpret_cast< float*>(_v) = pitch(); break;
        case 6: *reinterpret_cast< float*>(_v) = scaleX(); break;
        case 7: *reinterpret_cast< float*>(_v) = scaleY(); break;
        case 8: *reinterpret_cast< float*>(_v) = scaleZ(); break;
        case 9: *reinterpret_cast< bool*>(_v) = visible(); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setX(*reinterpret_cast< float*>(_v)); break;
        case 1: setY(*reinterpret_cast< float*>(_v)); break;
        case 2: setZ(*reinterpret_cast< float*>(_v)); break;
        case 3: setRoll(*reinterpret_cast< float*>(_v)); break;
        case 4: setYaw(*reinterpret_cast< float*>(_v)); break;
        case 5: setPitch(*reinterpret_cast< float*>(_v)); break;
        case 6: setScaleX(*reinterpret_cast< float*>(_v)); break;
        case 7: setScaleY(*reinterpret_cast< float*>(_v)); break;
        case 8: setScaleZ(*reinterpret_cast< float*>(_v)); break;
        case 9: setVisible(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void TransformationObject::xChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TransformationObject::yChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void TransformationObject::zChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void TransformationObject::rollChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void TransformationObject::pitchChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void TransformationObject::yawChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void TransformationObject::xScaleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void TransformationObject::yScaleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void TransformationObject::zScaleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void TransformationObject::visibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
