/****************************************************************************
** Meta object code from reading C++ file 'block.h'
**
** Created: Mon Jan 17 10:52:33 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../block.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'block.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Block[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,    7,    6,    6, 0x05,
      42,    6,    6,    6, 0x05,
      67,   61,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      86,    6,    6,    6, 0x0a,
     103,    6,    6,    6, 0x0a,
     143,  123,    6,    6, 0x0a,
     180,  170,    6,    6, 0x0a,
     208,    6,    6,    6, 0x0a,
     227,  218,    6,    6, 0x0a,
     290,    6,  266,    6, 0x0a,
     303,  218,    6,    6, 0x0a,
     329,    6,  323,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Block[] = {
    "Block\0\0parent,pos\0newNode(Block*,QPointF)\0"
    "selectionChanged()\0delta\0itemMoved(QPointF)\0"
    "updateContents()\0updateConnections()\0"
    "startAngle,endAngle\0placeChildren(qreal,qreal)\0"
    "pos,right\0placeChildren(QPointF,bool)\0"
    "detatch()\0theValue\0"
    "setProperties(QHash<QString,QVariant>)\0"
    "QHash<QString,QVariant>\0properties()\0"
    "setShapeType(Shape)\0Shape\0shapeType()\0"
};

const QMetaObject Block::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Block,
      qt_meta_data_Block, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Block::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Block::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Block::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Block))
        return static_cast<void*>(const_cast< Block*>(this));
    if (!strcmp(_clname, "QGraphicsItemGroup"))
        return static_cast< QGraphicsItemGroup*>(const_cast< Block*>(this));
    return QObject::qt_metacast(_clname);
}

int Block::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newNode((*reinterpret_cast< Block*(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 1: selectionChanged(); break;
        case 2: itemMoved((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 3: updateContents(); break;
        case 4: updateConnections(); break;
        case 5: placeChildren((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 6: placeChildren((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: detatch(); break;
        case 8: setProperties((*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[1]))); break;
        case 9: { QHash<QString,QVariant> _r = properties();
            if (_a[0]) *reinterpret_cast< QHash<QString,QVariant>*>(_a[0]) = _r; }  break;
        case 10: setShapeType((*reinterpret_cast< const Shape(*)>(_a[1]))); break;
        case 11: { Shape _r = shapeType();
            if (_a[0]) *reinterpret_cast< Shape*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Block::newNode(Block * _t1, const QPointF & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Block::selectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Block::itemMoved(const QPointF & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
