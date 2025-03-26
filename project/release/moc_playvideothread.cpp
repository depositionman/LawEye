/****************************************************************************
** Meta object code from reading C++ file 'playvideothread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../thread/playvideothread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playvideothread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayVideoThread_t {
    QByteArrayData data[4];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayVideoThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayVideoThread_t qt_meta_stringdata_PlayVideoThread = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PlayVideoThread"
QT_MOC_LITERAL(1, 16, 7), // "sendImg"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8) // "videoEnd"

    },
    "PlayVideoThread\0sendImg\0\0videoEnd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayVideoThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       3,    0,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void,

       0        // eod
};

void PlayVideoThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayVideoThread *_t = static_cast<PlayVideoThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendImg((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->videoEnd(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PlayVideoThread::*_t)(QImage );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayVideoThread::sendImg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PlayVideoThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayVideoThread::videoEnd)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PlayVideoThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_PlayVideoThread.data,
      qt_meta_data_PlayVideoThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlayVideoThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayVideoThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlayVideoThread.stringdata0))
        return static_cast<void*>(const_cast< PlayVideoThread*>(this));
    return QThread::qt_metacast(_clname);
}

int PlayVideoThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void PlayVideoThread::sendImg(QImage _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayVideoThread::videoEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
