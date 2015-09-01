/****************************************************************************
** Meta object code from reading C++ file 'ThreeDWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI/ThreeDWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ThreeDWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ThreeDWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      39,   13,   13,   13, 0x05,
      72,   13,   13,   13, 0x05,
     104,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     123,   13,   13,   13, 0x09,
     153,  142,   13,   13, 0x09,
     189,  180,   13,   13, 0x09,
     233,   13,   13,   13, 0x09,
     264,   13,   13,   13, 0x09,
     294,   13,   13,   13, 0x09,
     325,  311,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ThreeDWidget[] = {
    "ThreeDWidget\0\0signalRefreshTime(QTime)\0"
    "signalStaticCalibrationSuccess()\0"
    "signalFloorCalibrationSuccess()\0"
    "signalMarkerLoss()\0RefreshTime(QTime)\0"
    "pointCloud\0SetPointCloud(vector<POI>)\0"
    "POIsList\0ReconstructionGetPOIs(vector<vector<POI> >)\0"
    "slotStaticCalibrationSuccess()\0"
    "slotFloorCalibrationSuccess()\0"
    "slotMarkerLoss()\0cameraCenters\0"
    "slotCameraCenters(Vector3f*)\0"
};

void ThreeDWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ThreeDWidget *_t = static_cast<ThreeDWidget *>(_o);
        switch (_id) {
        case 0: _t->signalRefreshTime((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        case 1: _t->signalStaticCalibrationSuccess(); break;
        case 2: _t->signalFloorCalibrationSuccess(); break;
        case 3: _t->signalMarkerLoss(); break;
        case 4: _t->RefreshTime((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        case 5: _t->SetPointCloud((*reinterpret_cast< vector<POI>(*)>(_a[1]))); break;
        case 6: _t->ReconstructionGetPOIs((*reinterpret_cast< vector<vector<POI> >(*)>(_a[1]))); break;
        case 7: _t->slotStaticCalibrationSuccess(); break;
        case 8: _t->slotFloorCalibrationSuccess(); break;
        case 9: _t->slotMarkerLoss(); break;
        case 10: _t->slotCameraCenters((*reinterpret_cast< Vector3f*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ThreeDWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ThreeDWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_ThreeDWidget,
      qt_meta_data_ThreeDWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ThreeDWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ThreeDWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ThreeDWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ThreeDWidget))
        return static_cast<void*>(const_cast< ThreeDWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int ThreeDWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ThreeDWidget::signalRefreshTime(QTime _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ThreeDWidget::signalStaticCalibrationSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ThreeDWidget::signalFloorCalibrationSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ThreeDWidget::signalMarkerLoss()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
