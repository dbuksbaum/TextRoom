/****************************************************************************
** Meta object code from reading C++ file 'mindmapview.h'
**
** Created: Mon Jan 17 10:52:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mindmapview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mindmapview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MindMapView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   13,   12,   12, 0x05,
      59,   12,   12,   12, 0x05,
      87,   78,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     118,  109,   12,   12, 0x0a,
     135,  109,   12,   12, 0x0a,
     165,   12,  156,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MindMapView[] = {
    "MindMapView\0\0newParent,child\0"
    "reparentBlocks(Block*,Block*)\0"
    "selectionChanged()\0newValue\0"
    "zoomLevelChanged(int)\0theValue\0"
    "setZoomView(int)\0setMindmap(MindMap*)\0"
    "MindMap*\0mindmap()\0"
};

const QMetaObject MindMapView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_MindMapView,
      qt_meta_data_MindMapView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MindMapView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MindMapView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MindMapView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MindMapView))
        return static_cast<void*>(const_cast< MindMapView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int MindMapView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: reparentBlocks((*reinterpret_cast< Block*(*)>(_a[1])),(*reinterpret_cast< Block*(*)>(_a[2]))); break;
        case 1: selectionChanged(); break;
        case 2: zoomLevelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setZoomView((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: setMindmap((*reinterpret_cast< MindMap*(*)>(_a[1]))); break;
        case 5: { MindMap* _r = mindmap();
            if (_a[0]) *reinterpret_cast< MindMap**>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MindMapView::reparentBlocks(Block * _t1, Block * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MindMapView::selectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MindMapView::zoomLevelChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
