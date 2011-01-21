/****************************************************************************
** Meta object code from reading C++ file 'qdommodel.h'
**
** Created: Mon Jan 17 10:53:08 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qdomutils/qdommodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdommodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SxDomUtils__QDomModel[] = {

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

static const char qt_meta_stringdata_SxDomUtils__QDomModel[] = {
    "SxDomUtils::QDomModel\0"
};

const QMetaObject SxDomUtils::QDomModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_SxDomUtils__QDomModel,
      qt_meta_data_SxDomUtils__QDomModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SxDomUtils::QDomModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SxDomUtils::QDomModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SxDomUtils::QDomModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SxDomUtils__QDomModel))
        return static_cast<void*>(const_cast< QDomModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int SxDomUtils::QDomModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SxDomUtils__QDomPropertyModel[] = {

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

static const char qt_meta_stringdata_SxDomUtils__QDomPropertyModel[] = {
    "SxDomUtils::QDomPropertyModel\0"
};

const QMetaObject SxDomUtils::QDomPropertyModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_SxDomUtils__QDomPropertyModel,
      qt_meta_data_SxDomUtils__QDomPropertyModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SxDomUtils::QDomPropertyModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SxDomUtils::QDomPropertyModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SxDomUtils::QDomPropertyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SxDomUtils__QDomPropertyModel))
        return static_cast<void*>(const_cast< QDomPropertyModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int SxDomUtils::QDomPropertyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
