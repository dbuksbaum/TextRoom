/****************************************************************************
** Meta object code from reading C++ file 'qadaptormanager.h'
**
** Created: Mon Jan 17 10:53:10 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qmodeladaptor/qadaptormanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qadaptormanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QModelAdaptor__QAdaptorManager[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x05,
      40,   31,   31,   31, 0x05,
      47,   31,   31,   31, 0x05,
      54,   31,   31,   31, 0x05,
      69,   65,   31,   31, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   31,   31,   31, 0x0a,
      90,   31,   31,   31, 0x0a,
     100,   31,   31,   31, 0x0a,
     110,   31,   31,   31, 0x0a,
     124,   65,   31,   31, 0x0a,
     143,  137,   31,   31, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QModelAdaptor__QAdaptorManager[] = {
    "QModelAdaptor::QAdaptorManager\0\0first()\0"
    "next()\0last()\0previous()\0idx\0jump(int)\0"
    "firstRow()\0nextRow()\0lastRow()\0"
    "previousRow()\0jumpRow(int)\0index\0"
    "setRowFromIndex(QModelIndex)\0"
};

const QMetaObject QModelAdaptor::QAdaptorManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QModelAdaptor__QAdaptorManager,
      qt_meta_data_QModelAdaptor__QAdaptorManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QModelAdaptor::QAdaptorManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QModelAdaptor::QAdaptorManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QModelAdaptor::QAdaptorManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QModelAdaptor__QAdaptorManager))
        return static_cast<void*>(const_cast< QAdaptorManager*>(this));
    return QObject::qt_metacast(_clname);
}

int QModelAdaptor::QAdaptorManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: first(); break;
        case 1: next(); break;
        case 2: last(); break;
        case 3: previous(); break;
        case 4: jump((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: firstRow(); break;
        case 6: nextRow(); break;
        case 7: lastRow(); break;
        case 8: previousRow(); break;
        case 9: jumpRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: setRowFromIndex((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QModelAdaptor::QAdaptorManager::first()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QModelAdaptor::QAdaptorManager::next()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QModelAdaptor::QAdaptorManager::last()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QModelAdaptor::QAdaptorManager::previous()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QModelAdaptor::QAdaptorManager::jump(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
