/****************************************************************************
** Meta object code from reading C++ file 'browser.h'
**
** Created: Mon Jan 17 10:53:05 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qdomutils/browser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'browser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SxDomUtils__NodeBrowser[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   24, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   25,   24,   24, 0x08,
      59,   25,   24,   24, 0x08,

 // properties: name, type, flags
     101,   93, 0x0a095001,

       0        // eod
};

static const char qt_meta_stringdata_SxDomUtils__NodeBrowser[] = {
    "SxDomUtils::NodeBrowser\0\0itm\0"
    "itemClicked(QTreeWidgetItem*)\0"
    "propertyClicked(QListWidgetItem*)\0"
    "QString\0currentPath\0"
};

const QMetaObject SxDomUtils::NodeBrowser::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SxDomUtils__NodeBrowser,
      qt_meta_data_SxDomUtils__NodeBrowser, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SxDomUtils::NodeBrowser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SxDomUtils::NodeBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SxDomUtils::NodeBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SxDomUtils__NodeBrowser))
        return static_cast<void*>(const_cast< NodeBrowser*>(this));
    return QDialog::qt_metacast(_clname);
}

int SxDomUtils::NodeBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 1: propertyClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = currentPath(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
