/****************************************************************************
** Meta object code from reading C++ file 'HOGFeatureDetector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/ProcessingPipelines/inc/HOGFeatureDetector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HOGFeatureDetector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HOGFeatureDetector_t {
    QByteArrayData data[21];
    char stringdata[307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_HOGFeatureDetector_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_HOGFeatureDetector_t qt_meta_stringdata_HOGFeatureDetector = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 14),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 16),
QT_MOC_LITERAL(4, 52, 18),
QT_MOC_LITERAL(5, 71, 15),
QT_MOC_LITERAL(6, 87, 19),
QT_MOC_LITERAL(7, 107, 15),
QT_MOC_LITERAL(8, 123, 21),
QT_MOC_LITERAL(9, 145, 22),
QT_MOC_LITERAL(10, 168, 21),
QT_MOC_LITERAL(11, 190, 7),
QT_MOC_LITERAL(12, 198, 8),
QT_MOC_LITERAL(13, 207, 9),
QT_MOC_LITERAL(14, 217, 11),
QT_MOC_LITERAL(15, 229, 8),
QT_MOC_LITERAL(16, 238, 12),
QT_MOC_LITERAL(17, 251, 8),
QT_MOC_LITERAL(18, 260, 14),
QT_MOC_LITERAL(19, 275, 15),
QT_MOC_LITERAL(20, 291, 14)
    },
    "HOGFeatureDetector\0winSizeChanged\0\0"
    "blockSizeChanged\0blockStrideChanged\0"
    "cellSizeChanged\0numberOfBinsChanged\0"
    "winSigmaChanged\0thresholdL2HysChanged\0"
    "gammaCorrectionChanged\0numberOfLevelsChanged\0"
    "winSize\0cv::Size\0blockSize\0blockStride\0"
    "cellSize\0numberOfBins\0winSigma\0"
    "thresholdL2Hys\0gammaCorrection\0"
    "numberOfLevels\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HOGFeatureDetector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       9,   68, // properties
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
      11, 0x80000000 | 12, 0x00095009,
      13, 0x80000000 | 12, 0x0049510b,
      14, 0x80000000 | 12, 0x0049510b,
      15, 0x80000000 | 12, 0x0049510b,
      16, QMetaType::Int, 0x00495103,
      17, QMetaType::Double, 0x00495103,
      18, QMetaType::Double, 0x00495103,
      19, QMetaType::Bool, 0x00495103,
      20, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,

       0        // eod
};

void HOGFeatureDetector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HOGFeatureDetector *_t = static_cast<HOGFeatureDetector *>(_o);
        switch (_id) {
        case 0: _t->winSizeChanged(); break;
        case 1: _t->blockSizeChanged(); break;
        case 2: _t->blockStrideChanged(); break;
        case 3: _t->cellSizeChanged(); break;
        case 4: _t->numberOfBinsChanged(); break;
        case 5: _t->winSigmaChanged(); break;
        case 6: _t->thresholdL2HysChanged(); break;
        case 7: _t->gammaCorrectionChanged(); break;
        case 8: _t->numberOfLevelsChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HOGFeatureDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HOGFeatureDetector::winSizeChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (HOGFeatureDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HOGFeatureDetector::blockSizeChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (HOGFeatureDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HOGFeatureDetector::blockStrideChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (HOGFeatureDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HOGFeatureDetector::cellSizeChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (HOGFeatureDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HOGFeatureDetector::numberOfBinsChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (HOGFeatureDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HOGFeatureDetector::winSigmaChanged)) {
                *result = 5;
            }
        }
        {
            typedef void (HOGFeatureDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HOGFeatureDetector::thresholdL2HysChanged)) {
                *result = 6;
            }
        }
        {
            typedef void (HOGFeatureDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HOGFeatureDetector::gammaCorrectionChanged)) {
                *result = 7;
            }
        }
        {
            typedef void (HOGFeatureDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HOGFeatureDetector::numberOfLevelsChanged)) {
                *result = 8;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
        case 2:
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< cv::Size >(); break;
        }
    }

}

const QMetaObject HOGFeatureDetector::staticMetaObject = {
    { &ProcessingComponent::staticMetaObject, qt_meta_stringdata_HOGFeatureDetector.data,
      qt_meta_data_HOGFeatureDetector,  qt_static_metacall, 0, 0}
};


const QMetaObject *HOGFeatureDetector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HOGFeatureDetector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HOGFeatureDetector.stringdata))
        return static_cast<void*>(const_cast< HOGFeatureDetector*>(this));
    return ProcessingComponent::qt_metacast(_clname);
}

int HOGFeatureDetector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProcessingComponent::qt_metacall(_c, _id, _a);
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
        case 0: *reinterpret_cast< cv::Size*>(_v) = winSize(); break;
        case 1: *reinterpret_cast< cv::Size*>(_v) = blockSize(); break;
        case 2: *reinterpret_cast< cv::Size*>(_v) = blockStride(); break;
        case 3: *reinterpret_cast< cv::Size*>(_v) = cellSize(); break;
        case 4: *reinterpret_cast< int*>(_v) = numberOfBins(); break;
        case 5: *reinterpret_cast< double*>(_v) = winSigma(); break;
        case 6: *reinterpret_cast< double*>(_v) = thresholdL2Hys(); break;
        case 7: *reinterpret_cast< bool*>(_v) = gammaCorrection(); break;
        case 8: *reinterpret_cast< int*>(_v) = numberOfLevels(); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: setBlockSize(*reinterpret_cast< cv::Size*>(_v)); break;
        case 2: setBlockStride(*reinterpret_cast< cv::Size*>(_v)); break;
        case 3: setCellSize(*reinterpret_cast< cv::Size*>(_v)); break;
        case 4: setNumberOfBins(*reinterpret_cast< int*>(_v)); break;
        case 5: setWinSigma(*reinterpret_cast< double*>(_v)); break;
        case 6: setThresholdL2Hys(*reinterpret_cast< double*>(_v)); break;
        case 7: setGammaCorrection(*reinterpret_cast< bool*>(_v)); break;
        case 8: setNumberOfLevels(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void HOGFeatureDetector::winSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void HOGFeatureDetector::blockSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void HOGFeatureDetector::blockStrideChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void HOGFeatureDetector::cellSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void HOGFeatureDetector::numberOfBinsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void HOGFeatureDetector::winSigmaChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void HOGFeatureDetector::thresholdL2HysChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void HOGFeatureDetector::gammaCorrectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void HOGFeatureDetector::numberOfLevelsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE