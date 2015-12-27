/****************************************************************************
** Meta object code from reading C++ file 'inputbox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inputbox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_inputBox_t {
    QByteArrayData data[15];
    char stringdata[372];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_inputBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_inputBox_t qt_meta_stringdata_inputBox = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 21),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 33),
QT_MOC_LITERAL(4, 66, 5),
QT_MOC_LITERAL(5, 72, 32),
QT_MOC_LITERAL(6, 105, 31),
QT_MOC_LITERAL(7, 137, 35),
QT_MOC_LITERAL(8, 173, 35),
QT_MOC_LITERAL(9, 209, 32),
QT_MOC_LITERAL(10, 242, 31),
QT_MOC_LITERAL(11, 274, 19),
QT_MOC_LITERAL(12, 294, 7),
QT_MOC_LITERAL(13, 302, 34),
QT_MOC_LITERAL(14, 337, 33)
    },
    "inputBox\0on_buttonBox_accepted\0\0"
    "on_Resolution_currentIndexChanged\0"
    "index\0on_Audiorate_currentIndexChanged\0"
    "on_Channels_currentIndexChanged\0"
    "on_VideoBitRate_currentIndexChanged\0"
    "on_AudioBitRate_currentIndexChanged\0"
    "on_Framerate_currentIndexChanged\0"
    "on_VideoSRC_currentIndexChanged\0"
    "on_checkBox_clicked\0checked\0"
    "on_LocalCamera_currentIndexChanged\0"
    "on_soundCards_currentIndexChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_inputBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08,
       3,    1,   70,    2, 0x08,
       5,    1,   73,    2, 0x08,
       6,    1,   76,    2, 0x08,
       7,    1,   79,    2, 0x08,
       8,    1,   82,    2, 0x08,
       9,    1,   85,    2, 0x08,
      10,    1,   88,    2, 0x08,
      11,    1,   91,    2, 0x08,
      13,    1,   94,    2, 0x08,
      14,    1,   97,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void inputBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        inputBox *_t = static_cast<inputBox *>(_o);
        switch (_id) {
        case 0: _t->on_buttonBox_accepted(); break;
        case 1: _t->on_Resolution_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_Audiorate_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_Channels_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_VideoBitRate_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_AudioBitRate_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_Framerate_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_VideoSRC_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_checkBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_LocalCamera_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_soundCards_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject inputBox::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_inputBox.data,
      qt_meta_data_inputBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *inputBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *inputBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_inputBox.stringdata))
        return static_cast<void*>(const_cast< inputBox*>(this));
    return QDialog::qt_metacast(_clname);
}

int inputBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
