/****************************************************************************
** Meta object code from reading C++ file 'SimpleView.h'
**
** Created: Tue 25. Nov 14:20:31 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../Examples/GUI/Qt/SimpleView/SimpleView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimpleView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimpleView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      27,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SimpleView[] = {
    "SimpleView\0\0slotOpenFile()\0slotExit()\0"
};

void SimpleView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SimpleView *_t = static_cast<SimpleView *>(_o);
        switch (_id) {
        case 0: _t->slotOpenFile(); break;
        case 1: _t->slotExit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SimpleView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SimpleView::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SimpleView,
      qt_meta_data_SimpleView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimpleView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimpleView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimpleView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleView))
        return static_cast<void*>(const_cast< SimpleView*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SimpleView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE