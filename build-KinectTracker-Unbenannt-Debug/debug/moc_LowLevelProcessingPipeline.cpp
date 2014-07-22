/****************************************************************************
** Meta object code from reading C++ file 'LowLevelProcessingPipeline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/ProcessingPipelines/inc/LowLevelProcessingPipeline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LowLevelProcessingPipeline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LowLevelProcessingPipeline_t {
    QByteArrayData data[1];
    char stringdata[28];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_LowLevelProcessingPipeline_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_LowLevelProcessingPipeline_t qt_meta_stringdata_LowLevelProcessingPipeline = {
    {
QT_MOC_LITERAL(0, 0, 26)
    },
    "LowLevelProcessingPipeline\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LowLevelProcessingPipeline[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void LowLevelProcessingPipeline::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject LowLevelProcessingPipeline::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LowLevelProcessingPipeline.data,
      qt_meta_data_LowLevelProcessingPipeline,  qt_static_metacall, 0, 0}
};


const QMetaObject *LowLevelProcessingPipeline::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LowLevelProcessingPipeline::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LowLevelProcessingPipeline.stringdata))
        return static_cast<void*>(const_cast< LowLevelProcessingPipeline*>(this));
    return QObject::qt_metacast(_clname);
}

int LowLevelProcessingPipeline::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_SkinColorHistogramDetectionPipeline_t {
    QByteArrayData data[8];
    char stringdata[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SkinColorHistogramDetectionPipeline_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SkinColorHistogramDetectionPipeline_t qt_meta_stringdata_SkinColorHistogramDetectionPipeline = {
    {
QT_MOC_LITERAL(0, 0, 35),
QT_MOC_LITERAL(1, 36, 16),
QT_MOC_LITERAL(2, 53, 0),
QT_MOC_LITERAL(3, 54, 20),
QT_MOC_LITERAL(4, 75, 31),
QT_MOC_LITERAL(5, 107, 9),
QT_MOC_LITERAL(6, 117, 13),
QT_MOC_LITERAL(7, 131, 24)
    },
    "SkinColorHistogramDetectionPipeline\0"
    "thresholdChanged\0\0nonZeroPixelsChanged\0"
    "nonZeroRelativeFrequencyChanged\0"
    "threshold\0nonZeroPixels\0"
    "nonZeroRelativeFrequency\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SkinColorHistogramDetectionPipeline[] = {

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
       5, QMetaType::Double, 0x00495103,
       6, QMetaType::Int, 0x00495001,
       7, QMetaType::Float, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void SkinColorHistogramDetectionPipeline::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SkinColorHistogramDetectionPipeline *_t = static_cast<SkinColorHistogramDetectionPipeline *>(_o);
        switch (_id) {
        case 0: _t->thresholdChanged(); break;
        case 1: _t->nonZeroPixelsChanged(); break;
        case 2: _t->nonZeroRelativeFrequencyChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SkinColorHistogramDetectionPipeline::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SkinColorHistogramDetectionPipeline::thresholdChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (SkinColorHistogramDetectionPipeline::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SkinColorHistogramDetectionPipeline::nonZeroPixelsChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (SkinColorHistogramDetectionPipeline::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SkinColorHistogramDetectionPipeline::nonZeroRelativeFrequencyChanged)) {
                *result = 2;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SkinColorHistogramDetectionPipeline::staticMetaObject = {
    { &LowLevelProcessingPipeline::staticMetaObject, qt_meta_stringdata_SkinColorHistogramDetectionPipeline.data,
      qt_meta_data_SkinColorHistogramDetectionPipeline,  qt_static_metacall, 0, 0}
};


const QMetaObject *SkinColorHistogramDetectionPipeline::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SkinColorHistogramDetectionPipeline::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkinColorHistogramDetectionPipeline.stringdata))
        return static_cast<void*>(const_cast< SkinColorHistogramDetectionPipeline*>(this));
    return LowLevelProcessingPipeline::qt_metacast(_clname);
}

int SkinColorHistogramDetectionPipeline::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = LowLevelProcessingPipeline::qt_metacall(_c, _id, _a);
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
        case 0: *reinterpret_cast< double*>(_v) = threshold(); break;
        case 1: *reinterpret_cast< int*>(_v) = nonZeroPixels(); break;
        case 2: *reinterpret_cast< float*>(_v) = nonZeroRelativeFrequency(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setThreshold(*reinterpret_cast< double*>(_v)); break;
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
void SkinColorHistogramDetectionPipeline::thresholdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SkinColorHistogramDetectionPipeline::nonZeroPixelsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SkinColorHistogramDetectionPipeline::nonZeroRelativeFrequencyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
