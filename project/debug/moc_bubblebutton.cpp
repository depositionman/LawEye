/****************************************************************************
** Meta object code from reading C++ file 'bubblebutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mywidget/bubblebutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bubblebutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Bubble_t {
    QByteArrayData data[2];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Bubble_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Bubble_t qt_meta_stringdata_Bubble = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Bubble"
QT_MOC_LITERAL(1, 7, 8) // "geometry"

    },
    "Bubble\0geometry"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Bubble[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       1,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QRect, 0x00095103,

       0        // eod
};

void Bubble::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        Bubble *_t = static_cast<Bubble *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QRect*>(_v) = _t->geometry(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Bubble *_t = static_cast<Bubble *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setGeometry(*reinterpret_cast< QRect*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Bubble::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Bubble.data,
      qt_meta_data_Bubble,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Bubble::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bubble::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Bubble.stringdata0))
        return static_cast<void*>(const_cast< Bubble*>(this));
    return QObject::qt_metacast(_clname);
}

int Bubble::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_BubbleButton_t {
    QByteArrayData data[3];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BubbleButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BubbleButton_t qt_meta_stringdata_BubbleButton = {
    {
QT_MOC_LITERAL(0, 0, 12), // "BubbleButton"
QT_MOC_LITERAL(1, 13, 20), // "startBubbleAnimation"
QT_MOC_LITERAL(2, 34, 0) // ""

    },
    "BubbleButton\0startBubbleAnimation\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BubbleButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void BubbleButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BubbleButton *_t = static_cast<BubbleButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startBubbleAnimation(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject BubbleButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_BubbleButton.data,
      qt_meta_data_BubbleButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BubbleButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BubbleButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BubbleButton.stringdata0))
        return static_cast<void*>(const_cast< BubbleButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int BubbleButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
