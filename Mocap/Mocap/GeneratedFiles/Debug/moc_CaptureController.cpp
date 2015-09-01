/****************************************************************************
** Meta object code from reading C++ file 'CaptureController.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Threads/CaptureController.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CaptureController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CaptureController[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      55,   44,   18,   18, 0x05,
      85,   18,   18,   18, 0x05,
     116,   18,   18,   18, 0x05,
     146,   18,   18,   18, 0x05,
     165,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     196,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CaptureController[] = {
    "CaptureController\0\0signalRefreshTime(QTime)\0"
    "pointCloud\0signalPointCloud(vector<POI>)\0"
    "signalStaticCalibrationReady()\0"
    "signalFloorCalibrationReady()\0"
    "signalMarkerLoss()\0signalCameraCenters(Vector3f*)\0"
    "CaptureRun()\0"
};

void CaptureController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CaptureController *_t = static_cast<CaptureController *>(_o);
        switch (_id) {
        case 0: _t->signalRefreshTime((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        case 1: _t->signalPointCloud((*reinterpret_cast< vector<POI>(*)>(_a[1]))); break;
        case 2: _t->signalStaticCalibrationReady(); break;
        case 3: _t->signalFloorCalibrationReady(); break;
        case 4: _t->signalMarkerLoss(); break;
        case 5: _t->signalCameraCenters((*reinterpret_cast< Vector3f*(*)>(_a[1]))); break;
        case 6: _t->CaptureRun(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CaptureController::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CaptureController::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CaptureController,
      qt_meta_data_CaptureController, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CaptureController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CaptureController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CaptureController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CaptureController))
        return static_cast<void*>(const_cast< CaptureController*>(this));
    return QThread::qt_metacast(_clname);
}

int CaptureController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CaptureController::signalRefreshTime(QTime _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CaptureController::signalPointCloud(vector<POI> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CaptureController::signalStaticCalibrationReady()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CaptureController::signalFloorCalibrationReady()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void CaptureController::signalMarkerLoss()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void CaptureController::signalCameraCenters(Vector3f * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
