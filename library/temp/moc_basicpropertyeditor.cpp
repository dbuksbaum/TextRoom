/****************************************************************************
** Meta object code from reading C++ file 'basicpropertyeditor.h'
**
** Created: Mon Jan 17 10:52:54 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../basicpropertyeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basicpropertyeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BasicPropertyEditor[] = {

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
      27,   21,   20,   20, 0x0a,
      57,   51,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BasicPropertyEditor[] = {
    "BasicPropertyEditor\0\0index\0"
    "updateMaximumIndex(int)\0model\0"
    "setupModel(BlockPropertyModel*)\0"
};

const QMetaObject BasicPropertyEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BasicPropertyEditor,
      qt_meta_data_BasicPropertyEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BasicPropertyEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BasicPropertyEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BasicPropertyEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BasicPropertyEditor))
        return static_cast<void*>(const_cast< BasicPropertyEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int BasicPropertyEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateMaximumIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setupModel((*reinterpret_cast< BlockPropertyModel*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
