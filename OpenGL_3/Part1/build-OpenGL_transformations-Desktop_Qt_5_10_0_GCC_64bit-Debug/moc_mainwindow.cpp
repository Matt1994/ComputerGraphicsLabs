/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Code/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[507];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 30), // "on_ResetRotationButton_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 7), // "checked"
QT_MOC_LITERAL(4, 51, 28), // "on_RotationDialX_sliderMoved"
QT_MOC_LITERAL(5, 80, 5), // "value"
QT_MOC_LITERAL(6, 86, 28), // "on_RotationDialY_sliderMoved"
QT_MOC_LITERAL(7, 115, 28), // "on_RotationDialZ_sliderMoved"
QT_MOC_LITERAL(8, 144, 26), // "on_ResetZoomButton_clicked"
QT_MOC_LITERAL(9, 171, 25), // "on_ZoomSlider_sliderMoved"
QT_MOC_LITERAL(10, 197, 29), // "on_rotationSpeed_valueChanged"
QT_MOC_LITERAL(11, 227, 8), // "rotation"
QT_MOC_LITERAL(12, 236, 22), // "on_PhongButton_toggled"
QT_MOC_LITERAL(13, 259, 23), // "on_NormalButton_toggled"
QT_MOC_LITERAL(14, 283, 24), // "on_GouraudButton_toggled"
QT_MOC_LITERAL(15, 308, 34), // "on_materialIntensity1_valueCh..."
QT_MOC_LITERAL(16, 343, 1), // "d"
QT_MOC_LITERAL(17, 345, 34), // "on_materialIntensity2_valueCh..."
QT_MOC_LITERAL(18, 380, 34), // "on_materialIntensity3_valueCh..."
QT_MOC_LITERAL(19, 415, 19), // "on_lp1_valueChanged"
QT_MOC_LITERAL(20, 435, 19), // "on_lp2_valueChanged"
QT_MOC_LITERAL(21, 455, 19), // "on_lp3_valueChanged"
QT_MOC_LITERAL(22, 475, 29), // "on_phongExponent_valueChanged"
QT_MOC_LITERAL(23, 505, 1) // "i"

    },
    "MainWindow\0on_ResetRotationButton_clicked\0"
    "\0checked\0on_RotationDialX_sliderMoved\0"
    "value\0on_RotationDialY_sliderMoved\0"
    "on_RotationDialZ_sliderMoved\0"
    "on_ResetZoomButton_clicked\0"
    "on_ZoomSlider_sliderMoved\0"
    "on_rotationSpeed_valueChanged\0rotation\0"
    "on_PhongButton_toggled\0on_NormalButton_toggled\0"
    "on_GouraudButton_toggled\0"
    "on_materialIntensity1_valueChanged\0d\0"
    "on_materialIntensity2_valueChanged\0"
    "on_materialIntensity3_valueChanged\0"
    "on_lp1_valueChanged\0on_lp2_valueChanged\0"
    "on_lp3_valueChanged\0on_phongExponent_valueChanged\0"
    "i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x08 /* Private */,
       4,    1,  102,    2, 0x08 /* Private */,
       6,    1,  105,    2, 0x08 /* Private */,
       7,    1,  108,    2, 0x08 /* Private */,
       8,    1,  111,    2, 0x08 /* Private */,
       9,    1,  114,    2, 0x08 /* Private */,
      10,    1,  117,    2, 0x08 /* Private */,
      12,    1,  120,    2, 0x08 /* Private */,
      13,    1,  123,    2, 0x08 /* Private */,
      14,    1,  126,    2, 0x08 /* Private */,
      15,    1,  129,    2, 0x08 /* Private */,
      17,    1,  132,    2, 0x08 /* Private */,
      18,    1,  135,    2, 0x08 /* Private */,
      19,    1,  138,    2, 0x08 /* Private */,
      20,    1,  141,    2, 0x08 /* Private */,
      21,    1,  144,    2, 0x08 /* Private */,
      22,    1,  147,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void, QMetaType::Int,   23,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_ResetRotationButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_RotationDialX_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_RotationDialY_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_RotationDialZ_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_ResetZoomButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_ZoomSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_rotationSpeed_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_PhongButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_NormalButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_GouraudButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_materialIntensity1_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->on_materialIntensity2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->on_materialIntensity3_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->on_lp1_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->on_lp2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->on_lp3_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->on_phongExponent_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
