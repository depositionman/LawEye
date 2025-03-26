/****************************************************************************
** Meta object code from reading C++ file 'lookphotowin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/lookphotowin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lookphotowin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LookPhotoWin_t {
    QByteArrayData data[8];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LookPhotoWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LookPhotoWin_t qt_meta_stringdata_LookPhotoWin = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LookPhotoWin"
QT_MOC_LITERAL(1, 13, 11), // "backMainWin"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "loadMorePhoto"
QT_MOC_LITERAL(4, 40, 9), // "playPhoto"
QT_MOC_LITERAL(5, 50, 5), // "index"
QT_MOC_LITERAL(6, 56, 17), // "changePhotoByTime"
QT_MOC_LITERAL(7, 74, 8) // "datetime"

    },
    "LookPhotoWin\0backMainWin\0\0loadMorePhoto\0"
    "playPhoto\0index\0changePhotoByTime\0"
    "datetime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LookPhotoWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       6,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    5,
    QMetaType::Void, QMetaType::QDateTime,    7,

       0        // eod
};

void LookPhotoWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LookPhotoWin *_t = static_cast<LookPhotoWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backMainWin(); break;
        case 1: _t->loadMorePhoto(); break;
        case 2: _t->playPhoto((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->changePhotoByTime((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (LookPhotoWin::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LookPhotoWin::backMainWin)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject LookPhotoWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LookPhotoWin.data,
      qt_meta_data_LookPhotoWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LookPhotoWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LookPhotoWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LookPhotoWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LookPhotoWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void LookPhotoWin::backMainWin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
