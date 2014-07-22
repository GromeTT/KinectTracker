/****************************************************************************
** Meta object code from reading C++ file 'SkeletonData.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectTracker/inc/Kinect/inc/SkeletonData.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SkeletonData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SkeletonData_t {
    QByteArrayData data[22];
    char stringdata[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SkeletonData_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SkeletonData_t qt_meta_stringdata_SkeletonData = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 6),
QT_MOC_LITERAL(2, 20, 3),
QT_MOC_LITERAL(3, 24, 5),
QT_MOC_LITERAL(4, 30, 14),
QT_MOC_LITERAL(5, 45, 4),
QT_MOC_LITERAL(6, 50, 12),
QT_MOC_LITERAL(7, 63, 9),
QT_MOC_LITERAL(8, 73, 9),
QT_MOC_LITERAL(9, 83, 8),
QT_MOC_LITERAL(10, 92, 13),
QT_MOC_LITERAL(11, 106, 10),
QT_MOC_LITERAL(12, 117, 10),
QT_MOC_LITERAL(13, 128, 9),
QT_MOC_LITERAL(14, 138, 7),
QT_MOC_LITERAL(15, 146, 8),
QT_MOC_LITERAL(16, 155, 9),
QT_MOC_LITERAL(17, 165, 8),
QT_MOC_LITERAL(18, 174, 8),
QT_MOC_LITERAL(19, 183, 9),
QT_MOC_LITERAL(20, 193, 10),
QT_MOC_LITERAL(21, 204, 9)
    },
    "SkeletonData\0Joints\0Hip\0Spine\0"
    "ShoulderCenter\0Head\0ShoulderLeft\0"
    "ElbowLeft\0WristLeft\0HandLeft\0ShoulderRight\0"
    "ElbowRight\0WristRight\0HandRight\0HipLeft\0"
    "KneeLeft\0AnkleLeft\0FootLeft\0HipRight\0"
    "KneeRight\0AnkleRight\0FootRight\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SkeletonData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,   20,   18,

 // enum data: key, value
       2, uint(SkeletonData::Joints::Hip),
       3, uint(SkeletonData::Joints::Spine),
       4, uint(SkeletonData::Joints::ShoulderCenter),
       5, uint(SkeletonData::Joints::Head),
       6, uint(SkeletonData::Joints::ShoulderLeft),
       7, uint(SkeletonData::Joints::ElbowLeft),
       8, uint(SkeletonData::Joints::WristLeft),
       9, uint(SkeletonData::Joints::HandLeft),
      10, uint(SkeletonData::Joints::ShoulderRight),
      11, uint(SkeletonData::Joints::ElbowRight),
      12, uint(SkeletonData::Joints::WristRight),
      13, uint(SkeletonData::Joints::HandRight),
      14, uint(SkeletonData::Joints::HipLeft),
      15, uint(SkeletonData::Joints::KneeLeft),
      16, uint(SkeletonData::Joints::AnkleLeft),
      17, uint(SkeletonData::Joints::FootLeft),
      18, uint(SkeletonData::Joints::HipRight),
      19, uint(SkeletonData::Joints::KneeRight),
      20, uint(SkeletonData::Joints::AnkleRight),
      21, uint(SkeletonData::Joints::FootRight),

       0        // eod
};

void SkeletonData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject SkeletonData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SkeletonData.data,
      qt_meta_data_SkeletonData,  qt_static_metacall, 0, 0}
};


const QMetaObject *SkeletonData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SkeletonData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkeletonData.stringdata))
        return static_cast<void*>(const_cast< SkeletonData*>(this));
    return QObject::qt_metacast(_clname);
}

int SkeletonData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
