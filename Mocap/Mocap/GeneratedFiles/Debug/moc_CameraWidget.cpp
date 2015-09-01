/****************************************************************************
** Meta object code from reading C++ file 'CameraWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CameraWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CameraWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CameraWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   48,   13,   13, 0x0a,
     100,   13,   13,   13, 0x0a,
     126,  114,   13,   13, 0x0a,
     161,  152,   13,   13, 0x0a,
     199,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CameraWidget[] = {
    "CameraWidget\0\0signalDynamicCalibrationSuccess()\0"
    "POIs,cameraIndex\0GetPOIsFromCamera(vector<POI>,int)\0"
    "slotTimeout()\0cameraIndex\0"
    "slotCalibrationReady(int)\0POIsList\0"
    "GetPOIsListSync(vector<vector<POI> >)\0"
    "slotCalibrationReadySync()\0"
};

void CameraWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CameraWidget *_t = static_cast<CameraWidget *>(_o);
        switch (_id) {
        case 0: _t->signalDynamicCalibrationSuccess(); break;
        case 1: _t->GetPOIsFromCamera((*reinterpret_cast< vector<POI>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slotTimeout(); break;
        case 3: _t->slotCalibrationReady((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->GetPOIsListSync((*reinterpret_cast< vector<vector<POI> >(*)>(_a[1]))); break;
        case 5: _t->slotCalibrationReadySync(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CameraWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CameraWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CameraWidget,
      qt_meta_data_CameraWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CameraWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CameraWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CameraWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CameraWidget))
        return static_cast<void*>(const_cast< CameraWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CameraWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CameraWidget::signalDynamicCalibrationSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
