/****************************************************************************
** Meta object code from reading C++ file 'Camera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/OpenGL/inc/Camera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Camera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Camera_t {
    QByteArrayData data[14];
    char stringdata[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Camera_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Camera_t qt_meta_stringdata_Camera = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 8),
QT_MOC_LITERAL(2, 16, 0),
QT_MOC_LITERAL(3, 17, 8),
QT_MOC_LITERAL(4, 26, 8),
QT_MOC_LITERAL(5, 35, 11),
QT_MOC_LITERAL(6, 47, 12),
QT_MOC_LITERAL(7, 60, 10),
QT_MOC_LITERAL(8, 71, 1),
QT_MOC_LITERAL(9, 73, 1),
QT_MOC_LITERAL(10, 75, 1),
QT_MOC_LITERAL(11, 77, 4),
QT_MOC_LITERAL(12, 82, 5),
QT_MOC_LITERAL(13, 88, 3)
    },
    "Camera\0xChanged\0\0yChanged\0zChanged\0"
    "rollChanged\0pitchChanged\0yawChanged\0"
    "x\0y\0z\0roll\0pitch\0yaw\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Camera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       6,   50, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06,
       3,    0,   45,    2, 0x06,
       4,    0,   46,    2, 0x06,
       5,    0,   47,    2, 0x06,
       6,    0,   48,    2, 0x06,
       7,    0,   49,    2, 0x06,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::Float, 0x00495103,
       9, QMetaType::Float, 0x00495103,
      10, QMetaType::Float, 0x00495103,
      11, QMetaType::Float, 0x00495103,
      12, QMetaType::Float, 0x00495103,
      13, QMetaType::Float, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

void Camera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Camera *_t = static_cast<Camera *>(_o);
        switch (_id) {
        case 0: _t->xChanged(); break;
        case 1: _t->yChanged(); break;
        case 2: _t->zChanged(); break;
        case 3: _t->rollChanged(); break;
        case 4: _t->pitchChanged(); break;
        case 5: _t->yawChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Camera::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Camera::xChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (Camera::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Camera::yChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (Camera::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Camera::zChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (Camera::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Camera::rollChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (Camera::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Camera::pitchChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (Camera::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Camera::yawChanged)) {
                *result = 5;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Camera::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Camera.data,
      qt_meta_data_Camera,  qt_static_metacall, 0, 0}
};


const QMetaObject *Camera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Camera::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Camera.stringdata))
        return static_cast<void*>(const_cast< Camera*>(this));
    return QObject::qt_metacast(_clname);
}

int Camera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = x(); break;
        case 1: *reinterpret_cast< float*>(_v) = y(); break;
        case 2: *reinterpret_cast< float*>(_v) = z(); break;
        case 3: *reinterpret_cast< float*>(_v) = roll(); break;
        case 4: *reinterpret_cast< float*>(_v) = pitch(); break;
        case 5: *reinterpret_cast< float*>(_v) = yaw(); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setX(*reinterpret_cast< float*>(_v)); break;
        case 1: setY(*reinterpret_cast< float*>(_v)); break;
        case 2: setZ(*reinterpret_cast< float*>(_v)); break;
        case 3: setRoll(*reinterpret_cast< float*>(_v)); break;
        case 4: setPitch(*reinterpret_cast< float*>(_v)); break;
        case 5: setYaw(*reinterpret_cast< float*>(_v)); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Camera::xChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Camera::yChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Camera::zChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Camera::rollChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Camera::pitchChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Camera::yawChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
