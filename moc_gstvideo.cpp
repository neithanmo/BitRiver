/****************************************************************************
** Meta object code from reading C++ file 'gstvideo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gstvideo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gstvideo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_gstvideo_t {
    QByteArrayData data[11];
    char stringdata[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gstvideo_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gstvideo_t qt_meta_stringdata_gstvideo = {
    {
QT_MOC_LITERAL(0, 0, 8), // "gstvideo"
QT_MOC_LITERAL(1, 9, 5), // "start"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 4), // "stop"
QT_MOC_LITERAL(4, 21, 8), // "contrast"
QT_MOC_LITERAL(5, 30, 10), // "brightness"
QT_MOC_LITERAL(6, 41, 3), // "hue"
QT_MOC_LITERAL(7, 45, 10), // "saturation"
QT_MOC_LITERAL(8, 56, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(9, 88, 5), // "index"
QT_MOC_LITERAL(10, 94, 7) // "avolume"

    },
    "gstvideo\0start\0\0stop\0contrast\0brightness\0"
    "hue\0saturation\0on_comboBox_currentIndexChanged\0"
    "index\0avolume"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gstvideo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    1,   56,    2, 0x08 /* Private */,
       5,    1,   59,    2, 0x08 /* Private */,
       6,    1,   62,    2, 0x08 /* Private */,
       7,    1,   65,    2, 0x08 /* Private */,
       8,    1,   68,    2, 0x08 /* Private */,
      10,    1,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void gstvideo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        gstvideo *_t = static_cast<gstvideo *>(_o);
        switch (_id) {
        case 0: _t->start(); break;
        case 1: _t->stop(); break;
        case 2: _t->contrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->brightness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->hue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->saturation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->avolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject gstvideo::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gstvideo.data,
      qt_meta_data_gstvideo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *gstvideo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gstvideo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_gstvideo.stringdata))
        return static_cast<void*>(const_cast< gstvideo*>(this));
    return QWidget::qt_metacast(_clname);
}

int gstvideo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
