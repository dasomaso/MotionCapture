/****************************************************************************
** Meta object code from reading C++ file 'mocap.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mocap.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mocap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Mocap[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      23,    6,    6,    6, 0x09,
      42,    6,    6,    6, 0x09,
      72,    6,    6,    6, 0x09,
      89,    6,    6,    6, 0x09,
     121,    6,    6,    6, 0x09,
     152,    6,    6,    6, 0x09,
     182,    6,    6,    6, 0x09,
     200,    6,    6,    6, 0x09,
     219,    6,    6,    6, 0x09,
     235,    6,    6,    6, 0x09,
     251,    6,    6,    6, 0x09,
     270,    6,    6,    6, 0x09,
     288,    6,    6,    6, 0x09,
     305,    6,    6,    6, 0x09,
     324,    6,    6,    6, 0x09,
     342,    6,    6,    6, 0x09,
     373,    6,    6,    6, 0x09,
     403,    6,    6,    6, 0x09,
     431,    6,    6,    6, 0x09,
     457,    6,    6,    6, 0x09,
     483,    6,    6,    6, 0x09,
     510,    6,    6,    6, 0x09,
     536,    6,    6,    6, 0x09,
     556,    6,    6,    6, 0x09,
     576,    6,    6,    6, 0x09,
     598,    6,    6,    6, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Mocap[] = {
    "Mocap\0\0signalInfo(int)\0RefreshTime(QTime)\0"
    "GetInfo(vector<vector<POI> >)\0"
    "slotMarkerLoss()\0slotDynamicCalibrationSuccess()\0"
    "slotStaticCalibrationSuccess()\0"
    "slotFloorCalibrationSuccess()\0"
    "slotCameraClick()\0slotDenoiseClick()\0"
    "slotPlayClick()\0slotStopClick()\0"
    "slotDynamicClick()\0slotStaticClick()\0"
    "slotFloorClick()\0slotLoadResClick()\0"
    "slotMatlabClick()\0slotStartReconstructionClick()\0"
    "slotStopReconstructionClick()\0"
    "slotExportPointCloudClick()\0"
    "slotImportSkeletonClick()\0"
    "slotDefineSkeletonClick()\0"
    "slotExportMocapDataClick()\0"
    "slotCalculateJointClick()\0slotRetargetClick()\0"
    "slotAccuracyClick()\0slotMarkerLossClick()\0"
    "slotAboutClick()\0"
};

void Mocap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Mocap *_t = static_cast<Mocap *>(_o);
        switch (_id) {
        case 0: _t->signalInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->RefreshTime((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        case 2: _t->GetInfo((*reinterpret_cast< vector<vector<POI> >(*)>(_a[1]))); break;
        case 3: _t->slotMarkerLoss(); break;
        case 4: _t->slotDynamicCalibrationSuccess(); break;
        case 5: _t->slotStaticCalibrationSuccess(); break;
        case 6: _t->slotFloorCalibrationSuccess(); break;
        case 7: _t->slotCameraClick(); break;
        case 8: _t->slotDenoiseClick(); break;
        case 9: _t->slotPlayClick(); break;
        case 10: _t->slotStopClick(); break;
        case 11: _t->slotDynamicClick(); break;
        case 12: _t->slotStaticClick(); break;
        case 13: _t->slotFloorClick(); break;
        case 14: _t->slotLoadResClick(); break;
        case 15: _t->slotMatlabClick(); break;
        case 16: _t->slotStartReconstructionClick(); break;
        case 17: _t->slotStopReconstructionClick(); break;
        case 18: _t->slotExportPointCloudClick(); break;
        case 19: _t->slotImportSkeletonClick(); break;
        case 20: _t->slotDefineSkeletonClick(); break;
        case 21: _t->slotExportMocapDataClick(); break;
        case 22: _t->slotCalculateJointClick(); break;
        case 23: _t->slotRetargetClick(); break;
        case 24: _t->slotAccuracyClick(); break;
        case 25: _t->slotMarkerLossClick(); break;
        case 26: _t->slotAboutClick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Mocap::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Mocap::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Mocap,
      qt_meta_data_Mocap, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Mocap::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Mocap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Mocap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Mocap))
        return static_cast<void*>(const_cast< Mocap*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Mocap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void Mocap::signalInfo(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
