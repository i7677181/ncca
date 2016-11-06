/****************************************************************************
** Meta object code from reading C++ file 'NGLScene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/NGLScene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NGLScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NGLScene_t {
    QByteArrayData data[15];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NGLScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NGLScene_t qt_meta_stringdata_NGLScene = {
    {
QT_MOC_LITERAL(0, 0, 8), // "NGLScene"
QT_MOC_LITERAL(1, 9, 10), // "removeBoid"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "setCohesion"
QT_MOC_LITERAL(4, 33, 9), // "_cohesion"
QT_MOC_LITERAL(5, 43, 13), // "setSeparation"
QT_MOC_LITERAL(6, 57, 11), // "_separation"
QT_MOC_LITERAL(7, 69, 12), // "setAlignment"
QT_MOC_LITERAL(8, 82, 6), // "_align"
QT_MOC_LITERAL(9, 89, 8), // "setSpeed"
QT_MOC_LITERAL(10, 98, 6), // "_speed"
QT_MOC_LITERAL(11, 105, 7), // "setMass"
QT_MOC_LITERAL(12, 113, 5), // "_mass"
QT_MOC_LITERAL(13, 119, 10), // "setSepDist"
QT_MOC_LITERAL(14, 130, 8) // "_sepDist"

    },
    "NGLScene\0removeBoid\0\0setCohesion\0"
    "_cohesion\0setSeparation\0_separation\0"
    "setAlignment\0_align\0setSpeed\0_speed\0"
    "setMass\0_mass\0setSepDist\0_sepDist"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NGLScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    1,   50,    2, 0x0a /* Public */,
       5,    1,   53,    2, 0x0a /* Public */,
       7,    1,   56,    2, 0x0a /* Public */,
       9,    1,   59,    2, 0x0a /* Public */,
      11,    1,   62,    2, 0x0a /* Public */,
      13,    1,   65,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void NGLScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NGLScene *_t = static_cast<NGLScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->removeBoid(); break;
        case 1: _t->setCohesion((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setSeparation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setAlignment((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setMass((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setSepDist((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject NGLScene::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_NGLScene.data,
      qt_meta_data_NGLScene,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NGLScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NGLScene::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NGLScene.stringdata0))
        return static_cast<void*>(const_cast< NGLScene*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int NGLScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
