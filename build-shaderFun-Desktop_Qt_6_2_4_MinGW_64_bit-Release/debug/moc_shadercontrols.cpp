/****************************************************************************
** Meta object code from reading C++ file 'shadercontrols.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../assignment_package/src/shadercontrols.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shadercontrols.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ShaderControls_t {
    const uint offsetsAndSize[20];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ShaderControls_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ShaderControls_t qt_meta_stringdata_ShaderControls = {
    {
QT_MOC_LITERAL(0, 14), // "ShaderControls"
QT_MOC_LITERAL(15, 19), // "sig_setCurrentModel"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 34), // "sig_setCurrentSurfaceShaderPr..."
QT_MOC_LITERAL(71, 38), // "sig_setCurrentPostprocessShad..."
QT_MOC_LITERAL(110, 27), // "sig_setCurrentMatcapTexture"
QT_MOC_LITERAL(138, 20), // "slot_setCurrentModel"
QT_MOC_LITERAL(159, 35), // "slot_setCurrentSurfaceShaderP..."
QT_MOC_LITERAL(195, 39), // "slot_setCurrentPostprocessSha..."
QT_MOC_LITERAL(235, 28) // "slot_setCurrentMatcapTexture"

    },
    "ShaderControls\0sig_setCurrentModel\0\0"
    "sig_setCurrentSurfaceShaderProgram\0"
    "sig_setCurrentPostprocessShaderProgram\0"
    "sig_setCurrentMatcapTexture\0"
    "slot_setCurrentModel\0"
    "slot_setCurrentSurfaceShaderProgram\0"
    "slot_setCurrentPostprocessShaderProgram\0"
    "slot_setCurrentMatcapTexture"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShaderControls[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,
       3,    1,   65,    2, 0x06,    3 /* Public */,
       4,    1,   68,    2, 0x06,    5 /* Public */,
       5,    1,   71,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   74,    2, 0x0a,    9 /* Public */,
       7,    1,   77,    2, 0x0a,   11 /* Public */,
       8,    1,   80,    2, 0x0a,   13 /* Public */,
       9,    1,   83,    2, 0x0a,   15 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void ShaderControls::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ShaderControls *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sig_setCurrentModel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->sig_setCurrentSurfaceShaderProgram((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->sig_setCurrentPostprocessShaderProgram((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->sig_setCurrentMatcapTexture((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->slot_setCurrentModel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->slot_setCurrentSurfaceShaderProgram((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->slot_setCurrentPostprocessShaderProgram((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->slot_setCurrentMatcapTexture((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ShaderControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_setCurrentModel)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ShaderControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_setCurrentSurfaceShaderProgram)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ShaderControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_setCurrentPostprocessShaderProgram)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ShaderControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_setCurrentMatcapTexture)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ShaderControls::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ShaderControls.offsetsAndSize,
    qt_meta_data_ShaderControls,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ShaderControls_t
, QtPrivate::TypeAndForceComplete<ShaderControls, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *ShaderControls::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShaderControls::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ShaderControls.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ShaderControls::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ShaderControls::sig_setCurrentModel(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ShaderControls::sig_setCurrentSurfaceShaderProgram(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ShaderControls::sig_setCurrentPostprocessShaderProgram(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ShaderControls::sig_setCurrentMatcapTexture(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
