/****************************************************************************
** Meta object code from reading C++ file 'samplingthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../Src/Apps/Oscilloscope/samplingthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'samplingthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SamplingThread_t {
    QByteArrayData data[4];
    char stringdata[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SamplingThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SamplingThread_t qt_meta_stringdata_SamplingThread = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 12),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 12)
    },
    "SamplingThread\0setAmplitude\0\0setFrequency"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SamplingThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       3,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

       0        // eod
};

void SamplingThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SamplingThread *_t = static_cast<SamplingThread *>(_o);
        switch (_id) {
        case 0: _t->setAmplitude((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setFrequency((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SamplingThread::staticMetaObject = {
    { &QwtSamplingThread::staticMetaObject, qt_meta_stringdata_SamplingThread.data,
      qt_meta_data_SamplingThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *SamplingThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SamplingThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SamplingThread.stringdata))
        return static_cast<void*>(const_cast< SamplingThread*>(this));
    return QwtSamplingThread::qt_metacast(_clname);
}

int SamplingThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtSamplingThread::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
