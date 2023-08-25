/****************************************************************************
** Meta object code from reading C++ file 'mygl.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../assignment_package/src/mygl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mygl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyGL_t {
    const uint offsetsAndSize[12];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MyGL_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MyGL_t qt_meta_stringdata_MyGL = {
    {
QT_MOC_LITERAL(0, 4), // "MyGL"
QT_MOC_LITERAL(5, 35), // "slot_setCurrentSurfaceShaderP..."
QT_MOC_LITERAL(41, 0), // ""
QT_MOC_LITERAL(42, 39), // "slot_setCurrentPostprocessSha..."
QT_MOC_LITERAL(82, 20), // "slot_setCurrentModel"
QT_MOC_LITERAL(103, 28) // "slot_setCurrentMatcapTexture"

    },
    "MyGL\0slot_setCurrentSurfaceShaderProgram\0"
    "\0slot_setCurrentPostprocessShaderProgram\0"
    "slot_setCurrentModel\0slot_setCurrentMatcapTexture"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyGL[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x0a,    1 /* Public */,
       3,    1,   41,    2, 0x0a,    3 /* Public */,
       4,    1,   44,    2, 0x0a,    5 /* Public */,
       5,    1,   47,    2, 0x0a,    7 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void MyGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyGL *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_setCurrentSurfaceShaderProgram((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->slot_setCurrentPostprocessShaderProgram((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->slot_setCurrentModel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->slot_setCurrentMatcapTexture((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MyGL::staticMetaObject = { {
    QMetaObject::SuperData::link<OpenGLContext::staticMetaObject>(),
    qt_meta_stringdata_MyGL.offsetsAndSize,
    qt_meta_data_MyGL,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MyGL_t
, QtPrivate::TypeAndForceComplete<MyGL, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *MyGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyGL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyGL.stringdata0))
        return static_cast<void*>(this);
    return OpenGLContext::qt_metacast(_clname);
}

int MyGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OpenGLContext::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
