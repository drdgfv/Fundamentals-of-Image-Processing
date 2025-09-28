/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[54];
    char stringdata0[322];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 6), // "onOpen"
QT_MOC_LITERAL(18, 0), // ""
QT_MOC_LITERAL(19, 14), // "onSelectTarget"
QT_MOC_LITERAL(34, 6), // "onSave"
QT_MOC_LITERAL(41, 7), // "onReset"
QT_MOC_LITERAL(49, 12), // "mirrorImageX"
QT_MOC_LITERAL(62, 12), // "mirrorImagey"
QT_MOC_LITERAL(75, 14), // "grayScaleImage"
QT_MOC_LITERAL(90, 26), // "tuple<vector<int>,int,int>"
QT_MOC_LITERAL(117, 7), // "QImage&"
QT_MOC_LITERAL(125, 7), // "img_src"
QT_MOC_LITERAL(133, 7), // "img_dst"
QT_MOC_LITERAL(141, 7), // "QLabel*"
QT_MOC_LITERAL(149, 11), // "image_label"
QT_MOC_LITERAL(161, 17), // "quantizationImage"
QT_MOC_LITERAL(179, 6), // "levels"
QT_MOC_LITERAL(186, 14), // "histogramImage"
QT_MOC_LITERAL(201, 15), // "brightnessImage"
QT_MOC_LITERAL(217, 10), // "brightness"
QT_MOC_LITERAL(228, 13), // "contrastImage"
QT_MOC_LITERAL(242, 8), // "contrast"
QT_MOC_LITERAL(251, 13), // "negativeImage"
QT_MOC_LITERAL(265, 17), // "equalizationImage"
QT_MOC_LITERAL(283, 13), // "matchingImage"
QT_MOC_LITERAL(297, 11), // "zoomInImage"
QT_MOC_LITERAL(309, 12) // "zoomOutImage"

    },
    "MainWindow\0onOpen\0\0onSelectTarget\0"
    "onSave\0onReset\0mirrorImageX\0mirrorImagey\0"
    "grayScaleImage\0tuple<vector<int>,int,int>\0"
    "QImage&\0img_src\0img_dst\0QLabel*\0"
    "image_label\0quantizationImage\0levels\0"
    "histogramImage\0brightnessImage\0"
    "brightness\0contrastImage\0contrast\0"
    "negativeImage\0equalizationImage\0"
    "matchingImage\0zoomInImage\0zoomOutImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x08,    1 /* Private */,
       3,    0,  111,    2, 0x08,    2 /* Private */,
       4,    0,  112,    2, 0x08,    3 /* Private */,
       5,    0,  113,    2, 0x08,    4 /* Private */,
       6,    0,  114,    2, 0x08,    5 /* Private */,
       7,    0,  115,    2, 0x08,    6 /* Private */,
       8,    3,  116,    2, 0x08,    7 /* Private */,
      15,    1,  123,    2, 0x08,   11 /* Private */,
      17,    3,  126,    2, 0x08,   13 /* Private */,
      18,    1,  133,    2, 0x08,   17 /* Private */,
      20,    1,  136,    2, 0x08,   19 /* Private */,
      22,    0,  139,    2, 0x08,   21 /* Private */,
      23,    0,  140,    2, 0x08,   22 /* Private */,
      24,    0,  141,    2, 0x08,   23 /* Private */,
      25,    0,  142,    2, 0x08,   24 /* Private */,
      26,    0,  143,    2, 0x08,   25 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 9, 0x80000000 | 10, 0x80000000 | 10, 0x80000000 | 13,   11,   12,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10, 0x80000000 | 13,   11,   12,   14,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Double,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onOpen(); break;
        case 1: _t->onSelectTarget(); break;
        case 2: _t->onSave(); break;
        case 3: _t->onReset(); break;
        case 4: _t->mirrorImageX(); break;
        case 5: _t->mirrorImagey(); break;
        case 6: { tuple<vector<int>,int,int> _r = _t->grayScaleImage((*reinterpret_cast< std::add_pointer_t<QImage&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QImage&>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[3])));
            if (_a[0]) *reinterpret_cast< tuple<vector<int>,int,int>*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->quantizationImage((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->histogramImage((*reinterpret_cast< std::add_pointer_t<QImage&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QImage&>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[3]))); break;
        case 9: _t->brightnessImage((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->contrastImage((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 11: _t->negativeImage(); break;
        case 12: _t->equalizationImage(); break;
        case 13: _t->matchingImage(); break;
        case 14: _t->zoomInImage(); break;
        case 15: _t->zoomOutImage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<tuple<vector<int>,int,int>, std::false_type>, QtPrivate::TypeAndForceComplete<QImage &, std::false_type>, QtPrivate::TypeAndForceComplete<QImage &, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QImage &, std::false_type>, QtPrivate::TypeAndForceComplete<QImage &, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
