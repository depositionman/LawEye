/****************************************************************************
** Meta object code from reading C++ file 'transcodingwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/transcodingwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transcodingwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TranscodingWin_t {
    QByteArrayData data[11];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TranscodingWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TranscodingWin_t qt_meta_stringdata_TranscodingWin = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TranscodingWin"
QT_MOC_LITERAL(1, 15, 11), // "backMainWin"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "changeVideoByTime"
QT_MOC_LITERAL(4, 46, 8), // "datetime"
QT_MOC_LITERAL(5, 55, 16), // "getVideoFilePath"
QT_MOC_LITERAL(6, 72, 11), // "transCoding"
QT_MOC_LITERAL(7, 84, 12), // "getVideoPath"
QT_MOC_LITERAL(8, 97, 5), // "index"
QT_MOC_LITERAL(9, 103, 17), // "updateProgressBar"
QT_MOC_LITERAL(10, 121, 15) // "fillProgressBar"

    },
    "TranscodingWin\0backMainWin\0\0"
    "changeVideoByTime\0datetime\0getVideoFilePath\0"
    "transCoding\0getVideoPath\0index\0"
    "updateProgressBar\0fillProgressBar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TranscodingWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   50,    2, 0x0a /* Public */,
       5,    0,   53,    2, 0x0a /* Public */,
       6,    0,   54,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x0a /* Public */,
       9,    0,   58,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QDateTime,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TranscodingWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TranscodingWin *_t = static_cast<TranscodingWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backMainWin(); break;
        case 1: _t->changeVideoByTime((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 2: _t->getVideoFilePath(); break;
        case 3: _t->transCoding(); break;
        case 4: _t->getVideoPath((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->updateProgressBar(); break;
        case 6: _t->fillProgressBar(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TranscodingWin::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TranscodingWin::backMainWin)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TranscodingWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TranscodingWin.data,
      qt_meta_data_TranscodingWin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TranscodingWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TranscodingWin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TranscodingWin.stringdata0))
        return static_cast<void*>(const_cast< TranscodingWin*>(this));
    return QWidget::qt_metacast(_clname);
}

int TranscodingWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TranscodingWin::backMainWin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
