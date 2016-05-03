/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[362];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "on_actionTest_triggered"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 13), // "change_select"
QT_MOC_LITERAL(4, 50, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(5, 67, 18), // "skel_change_select"
QT_MOC_LITERAL(6, 86, 23), // "on_actionTube_triggered"
QT_MOC_LITERAL(7, 110, 20), // "on_limitxmax_changed"
QT_MOC_LITERAL(8, 131, 20), // "on_limitymax_changed"
QT_MOC_LITERAL(9, 152, 20), // "on_limitzmax_changed"
QT_MOC_LITERAL(10, 173, 20), // "on_limitxmin_changed"
QT_MOC_LITERAL(11, 194, 20), // "on_limitymin_changed"
QT_MOC_LITERAL(12, 215, 20), // "on_limitzmin_changed"
QT_MOC_LITERAL(13, 236, 20), // "on_positionx_changed"
QT_MOC_LITERAL(14, 257, 20), // "on_positiony_changed"
QT_MOC_LITERAL(15, 278, 20), // "on_positionz_changed"
QT_MOC_LITERAL(16, 299, 20), // "on_rotationx_changed"
QT_MOC_LITERAL(17, 320, 20), // "on_rotationy_changed"
QT_MOC_LITERAL(18, 341, 20) // "on_rotationz_changed"

    },
    "MainWindow\0on_actionTest_triggered\0\0"
    "change_select\0QTreeWidgetItem*\0"
    "skel_change_select\0on_actionTube_triggered\0"
    "on_limitxmax_changed\0on_limitymax_changed\0"
    "on_limitzmax_changed\0on_limitxmin_changed\0"
    "on_limitymin_changed\0on_limitzmin_changed\0"
    "on_positionx_changed\0on_positiony_changed\0"
    "on_positionz_changed\0on_rotationx_changed\0"
    "on_rotationy_changed\0on_rotationz_changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    2,   95,    2, 0x08 /* Private */,
       5,    2,  100,    2, 0x08 /* Private */,
       6,    0,  105,    2, 0x08 /* Private */,
       7,    1,  106,    2, 0x08 /* Private */,
       8,    1,  109,    2, 0x08 /* Private */,
       9,    1,  112,    2, 0x08 /* Private */,
      10,    1,  115,    2, 0x08 /* Private */,
      11,    1,  118,    2, 0x08 /* Private */,
      12,    1,  121,    2, 0x08 /* Private */,
      13,    1,  124,    2, 0x08 /* Private */,
      14,    1,  127,    2, 0x08 /* Private */,
      15,    1,  130,    2, 0x08 /* Private */,
      16,    1,  133,    2, 0x08 /* Private */,
      17,    1,  136,    2, 0x08 /* Private */,
      18,    1,  139,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionTest_triggered(); break;
        case 1: _t->change_select((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 2: _t->skel_change_select((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 3: _t->on_actionTube_triggered(); break;
        case 4: _t->on_limitxmax_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->on_limitymax_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->on_limitzmax_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->on_limitxmin_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->on_limitymin_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->on_limitzmin_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->on_positionx_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->on_positiony_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->on_positionz_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->on_rotationx_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->on_rotationy_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->on_rotationz_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
