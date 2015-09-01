/****************************************************************************
** Meta object code from reading C++ file 'CameraParaWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CameraParaWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CameraParaWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CameraParaWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x0a,
      48,   18,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CameraParaWidget[] = {
    "CameraParaWidget\0\0value\0setThreshholdValue(int)\0"
    "setMarkerValue(int)\0"
};

void CameraParaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CameraParaWidget *_t = static_cast<CameraParaWidget *>(_o);
        switch (_id) {
        case 0: _t->setThreshholdValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setMarkerValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CameraParaWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CameraParaWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CameraParaWidget,
      qt_meta_data_CameraParaWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CameraParaWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CameraParaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CameraParaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CameraParaWidget))
        return static_cast<void*>(const_cast< CameraParaWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CameraParaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
