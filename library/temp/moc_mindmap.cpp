/****************************************************************************
** Meta object code from reading C++ file 'mindmap.h'
**
** Created: Mon Jan 17 10:52:37 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mindmap.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mindmap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MindMap[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,    9,    8,    8, 0x05,
      33,   27,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      83,   67,    8,    8, 0x0a,
     132,  117,    8,    8, 0x0a,
     159,    8,    8,    8, 0x0a,
     176,    8,    8,    8, 0x0a,
     199,    8,    8,    8, 0x0a,
     227,  216,    8,    8, 0x0a,
     258,  252,    8,    8, 0x0a,
     281,    8,    8,    8, 0x0a,
     299,    8,    8,    8, 0x0a,
     315,    8,    8,    8, 0x0a,
     330,    8,    8,    8, 0x0a,
     347,    8,    8,    8, 0x0a,
     369,    8,    8,    8, 0x0a,
     392,    8,    8,    8, 0x0a,
     408,    8,    8,    8, 0x0a,
     426,    8,    8,    8, 0x0a,
     457,  451,    8,    8, 0x0a,
     492,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MindMap[] = {
    "MindMap\0\0idx\0maxIndex(int)\0model\0"
    "modelChanged(BlockPropertyModel*)\0"
    "newParent,child\0slotReparentBlocks(Block*,Block*)\0"
    "parentNode,pos\0createNode(Block*,QPointF)\0"
    "selectRootNode()\0itemSelectionChanged()\0"
    "clearSelection()\0node,delta\0"
    "moveItem(Block*,QPointF)\0delta\0"
    "moveSelection(QPointF)\0deleteSelection()\0"
    "copySelection()\0cutSelection()\0"
    "colorSelection()\0changeFontSelection()\0"
    "changeShapeSelection()\0arrangeBlocks()\0"
    "selectAllBlocks()\0createChildOnSelection()\0"
    "state\0slotCommandStackCleanChanged(bool)\0"
    "configureDocument()\0"
};

const QMetaObject MindMap::staticMetaObject = {
    { &SxFile::staticMetaObject, qt_meta_stringdata_MindMap,
      qt_meta_data_MindMap, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MindMap::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MindMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MindMap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MindMap))
        return static_cast<void*>(const_cast< MindMap*>(this));
    return SxFile::qt_metacast(_clname);
}

int MindMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SxFile::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: maxIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: modelChanged((*reinterpret_cast< BlockPropertyModel*(*)>(_a[1]))); break;
        case 2: slotReparentBlocks((*reinterpret_cast< Block*(*)>(_a[1])),(*reinterpret_cast< Block*(*)>(_a[2]))); break;
        case 3: createNode((*reinterpret_cast< Block*(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 4: selectRootNode(); break;
        case 5: itemSelectionChanged(); break;
        case 6: clearSelection(); break;
        case 7: moveItem((*reinterpret_cast< Block*(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 8: moveSelection((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 9: deleteSelection(); break;
        case 10: copySelection(); break;
        case 11: cutSelection(); break;
        case 12: colorSelection(); break;
        case 13: changeFontSelection(); break;
        case 14: changeShapeSelection(); break;
        case 15: arrangeBlocks(); break;
        case 16: selectAllBlocks(); break;
        case 17: createChildOnSelection(); break;
        case 18: slotCommandStackCleanChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: configureDocument(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void MindMap::maxIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MindMap::modelChanged(BlockPropertyModel * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
