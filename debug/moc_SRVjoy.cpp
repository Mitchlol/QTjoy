/****************************************************************************
** Meta object code from reading C++ file 'SRVjoy.h'
**
** Created: Thu Aug 27 23:10:08 2009
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
      13,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      25,    7,    7,    7, 0x08,
      39,    7,    7,    7, 0x08,
      57,    7,    7,    7, 0x08,
      76,    7,    7,    7, 0x08,
      91,    7,    7,    7, 0x08,
     110,    7,    7,    7, 0x08,
     130,    7,    7,    7, 0x08,
     142,    7,    7,    7, 0x08,
     153,    7,    7,    7, 0x08,
     173,  166,    7,    7, 0x08,
     202,  193,    7,    7, 0x08,
     232,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SRVjoy[] = {
    "SRVjoy\0\0connectToRobot()\0moveForward()\0"
    "moveForwardLeft()\0moveForwardRight()\0"
    "moveBackward()\0moveBackwardLeft()\0"
    "moveBackwardRight()\0rotateCCW()\0"
    "rotateCW()\0stopMoving()\0nSpeed\0"
    "setLinearSpeed(int)\0dDegrees\0"
    "setAngularSpeedInDegrees(int)\0"
    "takePictureShot()\0"
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
        case 0: connectToRobot(); break;
        case 1: moveForward(); break;
        case 2: moveForwardLeft(); break;
        case 3: moveForwardRight(); break;
        case 4: moveBackward(); break;
        case 5: moveBackwardLeft(); break;
        case 6: moveBackwardRight(); break;
        case 7: rotateCCW(); break;
        case 8: rotateCW(); break;
        case 9: stopMoving(); break;
        case 10: setLinearSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: setAngularSpeedInDegrees((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: takePictureShot(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
