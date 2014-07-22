/****************************************************************************
** Meta object code from reading C++ file 'RenderObject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/OpenGL/inc/RenderObject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RenderObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RenderObject_t {
    QByteArrayData data[6];
    char stringdata[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_RenderObject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_RenderObject_t qt_meta_stringdata_RenderObject = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 23),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 17),
QT_MOC_LITERAL(4, 56, 13),
QT_MOC_LITERAL(5, 70, 10)
    },
    "RenderObject\0useWireFrameModeChanged\0"
    "\0useTextureChanged\0wireFrameMode\0"
    "useTexture\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RenderObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       2,   26, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06,
       3,    0,   25,    2, 0x06,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       4, QMetaType::Bool, 0x00495103,
       5, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void RenderObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RenderObject *_t = static_cast<RenderObject *>(_o);
        switch (_id) {
        case 0: _t->useWireFrameModeChanged(); break;
        case 1: _t->useTextureChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RenderObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RenderObject::useWireFrameModeChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (RenderObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RenderObject::useTextureChanged)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject RenderObject::staticMetaObject = {
    { &RenderObjectInterface::staticMetaObject, qt_meta_stringdata_RenderObject.data,
      qt_meta_data_RenderObject,  qt_static_metacall, 0, 0}
};


const QMetaObject *RenderObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderObject.stringdata))
        return static_cast<void*>(const_cast< RenderObject*>(this));
    return RenderObjectInterface::qt_metacast(_clname);
}

int RenderObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RenderObjectInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = isWireFrameModeOn(); break;
        case 1: *reinterpret_cast< bool*>(_v) = useTexture(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setWireFrameMode(*reinterpret_cast< bool*>(_v)); break;
        case 1: setUseTexture(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void RenderObject::useWireFrameModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void RenderObject::useTextureChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
