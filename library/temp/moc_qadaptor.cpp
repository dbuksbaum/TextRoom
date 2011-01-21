/****************************************************************************
** Meta object code from reading C++ file 'qadaptor.h'
**
** Created: Mon Jan 17 10:53:12 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qmodeladaptor/qadaptor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qadaptor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QModelAdaptor__QModelAdaptorBase[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       3,   59, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,   33,   33,   33, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   33,   33,   33, 0x0a,
      62,   33,   33,   33, 0x0a,
      97,   77,   33,   33, 0x0a,
     135,   33,   33,   33, 0x0a,
     143,   33,   33,   33, 0x0a,
     150,   33,   33,   33, 0x0a,
     157,   33,   33,   33, 0x0a,
     172,  168,   33,   33, 0x0a,

 // properties: name, type, flags
     186,  182, 0x02095103,
     168,  182, 0x02095103,
     204,  193, 0x0c095103,

       0        // eod
};

static const char qt_meta_stringdata_QModelAdaptor__QModelAdaptorBase[] = {
    "QModelAdaptor::QModelAdaptorBase\0\0"
    "dataChanged()\0updateModel()\0updateEditor()\0"
    "topLeft,bottomRight\0"
    "updateEditor(QModelIndex,QModelIndex)\0"
    "first()\0next()\0last()\0previous()\0row\0"
    "jump(int)\0int\0column\0QByteArray\0"
    "propertyName\0"
};

const QMetaObject QModelAdaptor::QModelAdaptorBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QModelAdaptor__QModelAdaptorBase,
      qt_meta_data_QModelAdaptor__QModelAdaptorBase, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QModelAdaptor::QModelAdaptorBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QModelAdaptor::QModelAdaptorBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QModelAdaptor::QModelAdaptorBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QModelAdaptor__QModelAdaptorBase))
        return static_cast<void*>(const_cast< QModelAdaptorBase*>(this));
    return QObject::qt_metacast(_clname);
}

int QModelAdaptor::QModelAdaptorBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dataChanged(); break;
        case 1: updateModel(); break;
        case 2: updateEditor(); break;
        case 3: updateEditor((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 4: first(); break;
        case 5: next(); break;
        case 6: last(); break;
        case 7: previous(); break;
        case 8: jump((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = column(); break;
        case 1: *reinterpret_cast< int*>(_v) = row(); break;
        case 2: *reinterpret_cast< QByteArray*>(_v) = propertyName(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setColumn(*reinterpret_cast< int*>(_v)); break;
        case 1: setRow(*reinterpret_cast< int*>(_v)); break;
        case 2: setPropertyName(*reinterpret_cast< QByteArray*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QModelAdaptor::QModelAdaptorBase::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_QModelAdaptor__QAbstractItemModelAdaptor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QModelAdaptor__QAbstractItemModelAdaptor[] = {
    "QModelAdaptor::QAbstractItemModelAdaptor\0"
};

const QMetaObject QModelAdaptor::QAbstractItemModelAdaptor::staticMetaObject = {
    { &QModelAdaptorBase::staticMetaObject, qt_meta_stringdata_QModelAdaptor__QAbstractItemModelAdaptor,
      qt_meta_data_QModelAdaptor__QAbstractItemModelAdaptor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QModelAdaptor::QAbstractItemModelAdaptor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QModelAdaptor::QAbstractItemModelAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QModelAdaptor::QAbstractItemModelAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QModelAdaptor__QAbstractItemModelAdaptor))
        return static_cast<void*>(const_cast< QAbstractItemModelAdaptor*>(this));
    return QModelAdaptorBase::qt_metacast(_clname);
}

int QModelAdaptor::QAbstractItemModelAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QModelAdaptorBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QModelAdaptor__QAbstractItemModelSelectionAdaptor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      51,   50,   50,   50, 0x0a,
      65,   50,   50,   50, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QModelAdaptor__QAbstractItemModelSelectionAdaptor[] = {
    "QModelAdaptor::QAbstractItemModelSelectionAdaptor\0"
    "\0updateModel()\0updateEditor()\0"
};

const QMetaObject QModelAdaptor::QAbstractItemModelSelectionAdaptor::staticMetaObject = {
    { &QModelAdaptorBase::staticMetaObject, qt_meta_stringdata_QModelAdaptor__QAbstractItemModelSelectionAdaptor,
      qt_meta_data_QModelAdaptor__QAbstractItemModelSelectionAdaptor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QModelAdaptor::QAbstractItemModelSelectionAdaptor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QModelAdaptor::QAbstractItemModelSelectionAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QModelAdaptor::QAbstractItemModelSelectionAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QModelAdaptor__QAbstractItemModelSelectionAdaptor))
        return static_cast<void*>(const_cast< QAbstractItemModelSelectionAdaptor*>(this));
    return QModelAdaptorBase::qt_metacast(_clname);
}

int QModelAdaptor::QAbstractItemModelSelectionAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QModelAdaptorBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateModel(); break;
        case 1: updateEditor(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
