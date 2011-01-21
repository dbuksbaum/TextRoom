/****************************************************************************
** Meta object code from reading C++ file 'sxfile.h'
**
** Created: Mon Jan 17 10:53:03 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sxfile/sxfile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sxfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SxFile[] = {

 // content:
       5,       // revision
       0,       // classname
       1,   14, // classinfo
      14,   16, // methods
      12,   86, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
      12,    7,

 // signals: signature, parameters, type, tag, flags
      30,   21,   20,   20, 0x05,
      50,   21,   20,   20, 0x05,
      79,   69,   20,   20, 0x05,
     101,   95,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     120,   20,   20,   20, 0x0a,
     135,   21,   20,   20, 0x0a,
     163,   20,   20,   20, 0x0a,
     178,   20,   20,   20, 0x0a,
     195,   20,   20,   20, 0x0a,
     209,   20,   20,   20, 0x0a,
     226,   20,   20,   20, 0x0a,
     249,  240,   20,   20, 0x0a,
     267,   20,   20,   20, 0x08,
     288,   20,   20,   20, 0x08,

 // properties: name, type, flags
     311,  303, 0x0a095001,
     323,  303, 0x0a095001,
     335,  303, 0x0a095001,
     351,  303, 0x0a095001,
     366,  303, 0x0a095001,
     383,  303, 0x0a095001,
     400,  395, 0x01095103,
     417,  413, 0x02095103,
     433,  303, 0x0a095103,
     452,  303, 0x0a095103,
     473,  303, 0x0a095103,
     240,  395, 0x01095103,

       0        // eod
};

static const char qt_meta_stringdata_SxFile[] = {
    "SxFile\0LGPL\0license\0\0fileName\0"
    "fileLoaded(QString)\0fileSaved(QString)\0"
    "statusMsg\0status(QString)\0state\0"
    "fileModified(bool)\0slotOpenFile()\0"
    "slotOpenFileByName(QString)\0slotSaveFile()\0"
    "slotSaveAsFile()\0slotNewFile()\0"
    "slotReloadFile()\0dataChanged()\0modified\0"
    "setModified(bool)\0slotOpenRecentFile()\0"
    "slotAutoSave()\0QString\0currentFile\0"
    "currentPath\0currentBaseName\0backupFileName\0"
    "autosaveFileName\0defaultPath\0bool\0"
    "backupOnSave\0int\0autoSaveTimeout\0"
    "backupFileTemplate\0autosaveFileTemplate\0"
    "defaultPathTemplate\0"
};

const QMetaObject SxFile::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SxFile,
      qt_meta_data_SxFile, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SxFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SxFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SxFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SxFile))
        return static_cast<void*>(const_cast< SxFile*>(this));
    return QObject::qt_metacast(_clname);
}

int SxFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: fileLoaded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: fileSaved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: status((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: fileModified((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: slotOpenFile(); break;
        case 5: slotOpenFileByName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: slotSaveFile(); break;
        case 7: slotSaveAsFile(); break;
        case 8: slotNewFile(); break;
        case 9: slotReloadFile(); break;
        case 10: dataChanged(); break;
        case 11: setModified((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: slotOpenRecentFile(); break;
        case 13: slotAutoSave(); break;
        default: ;
        }
        _id -= 14;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = currentFile(); break;
        case 1: *reinterpret_cast< QString*>(_v) = currentPath(); break;
        case 2: *reinterpret_cast< QString*>(_v) = currentBaseName(); break;
        case 3: *reinterpret_cast< QString*>(_v) = backupFileName(); break;
        case 4: *reinterpret_cast< QString*>(_v) = autosaveFileName(); break;
        case 5: *reinterpret_cast< QString*>(_v) = defaultPath(); break;
        case 6: *reinterpret_cast< bool*>(_v) = backupOnSave(); break;
        case 7: *reinterpret_cast< int*>(_v) = autoSaveTimeout(); break;
        case 8: *reinterpret_cast< QString*>(_v) = backupFileTemplate(); break;
        case 9: *reinterpret_cast< QString*>(_v) = autosaveFileTemplate(); break;
        case 10: *reinterpret_cast< QString*>(_v) = defaultPathTemplate(); break;
        case 11: *reinterpret_cast< bool*>(_v) = modified(); break;
        }
        _id -= 12;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 6: setBackupOnSave(*reinterpret_cast< bool*>(_v)); break;
        case 7: setAutoSaveTimeout(*reinterpret_cast< int*>(_v)); break;
        case 8: setBackupFileTemplate(*reinterpret_cast< QString*>(_v)); break;
        case 9: setAutosaveFileTemplate(*reinterpret_cast< QString*>(_v)); break;
        case 10: setDefaultPathTemplate(*reinterpret_cast< QString*>(_v)); break;
        case 11: setModified(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 12;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 12;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SxFile::fileLoaded(const QString & _t1)const
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< SxFile *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SxFile::fileSaved(const QString & _t1)const
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< SxFile *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SxFile::status(const QString & _t1)const
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< SxFile *>(this), &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SxFile::fileModified(bool _t1)const
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< SxFile *>(this), &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
