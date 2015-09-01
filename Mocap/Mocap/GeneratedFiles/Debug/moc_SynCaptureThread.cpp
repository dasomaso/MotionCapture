/****************************************************************************
** Meta object code from reading C++ file 'SynCaptureThread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Threads/SynCaptureThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SynCaptureThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SynCaptureThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      60,   17,   17,   17, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SynCaptureThread[] = {
    "SynCaptureThread\0\0"
    "signalPOIsListReady(vector<vector<POI> >)\0"
    "signalCalibrationReady()\0"
};

void SynCaptureThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SynCaptureThread *_t = static_cast<SynCaptureThread *>(_o);
        switch (_id) {
        case 0: _t->signalPOIsListReady((*reinterpret_cast< vector<vector<POI> >(*)>(_a[1]))); break;
        case 1: _t->signalCalibrationReady(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SynCaptureThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SynCaptureThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SynCaptureThread,
      qt_meta_data_SynCaptureThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SynCaptureThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SynCaptureThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SynCaptureThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SynCaptureThread))
        return static_cast<void*>(const_cast< SynCaptureThread*>(this));
    return QThread::qt_metacast(_clname);
}

int SynCaptureThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SynCaptureThread::signalPOIsListReady(vector<vector<POI> > _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SynCaptureThread::signalCalibrationReady()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
