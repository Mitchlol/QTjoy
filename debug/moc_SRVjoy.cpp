/****************************************************************************
** Meta object code from reading C++ file 'SRVjoy.h'
**
** Created: Wed Aug 19 15:10:51 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SRVjoy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SRVjoy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SRVjoy[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      22,    7,    7,    7, 0x08,
      37,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SRVjoy[] = {
    "SRVjoy\0\0moveForward()\0moveBackward()\0"
    "stopMoving()\0"
};

const QMetaObject SRVjoy::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SRVjoy,
      qt_meta_data_SRVjoy, 0 }
};

const QMetaObject *SRVjoy::metaObject() const
{
    return &staticMetaObject;
}

void *SRVjoy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SRVjoy))
        return static_cast<void*>(const_cast< SRVjoy*>(this));
    return QWidget::qt_metacast(_clname);
}

int SRVjoy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: moveForward(); break;
        case 1: moveBackward(); break;
        case 2: stopMoving(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
