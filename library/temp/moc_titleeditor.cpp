/****************************************************************************
** Meta object code from reading C++ file 'titleeditor.h'
**
** Created: Mon Jan 17 10:52:59 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../titleeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'titleeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TitleEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      32,   12,   12,   12, 0x0a,
      56,   47,   12,   12, 0x0a,
      80,   12,   75,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TitleEditor[] = {
    "TitleEditor\0\0setNewBlockTitle()\0"
    "startEditing()\0theValue\0setIsEditing(bool)\0"
    "bool\0isEditing()\0"
};

const QMetaObject TitleEditor::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_TitleEditor,
      qt_meta_data_TitleEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TitleEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TitleEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TitleEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TitleEditor))
        return static_cast<void*>(const_cast< TitleEditor*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int TitleEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setNewBlockTitle(); break;
        case 1: startEditing(); break;
        case 2: setIsEditing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: { bool _r = isEditing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
