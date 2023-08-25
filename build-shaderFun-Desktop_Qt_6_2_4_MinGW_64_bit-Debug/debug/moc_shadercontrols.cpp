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
    const uint offsetsAndSize[44];
    char stringdata0[594];
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
QT_MOC_LITERAL(110, 38), // "sig_setCurrentPostSurfaceShad..."
QT_MOC_LITERAL(149, 27), // "sig_setCurrentMatcapTexture"
QT_MOC_LITERAL(177, 23), // "sig_setInstancedGridRes"
QT_MOC_LITERAL(201, 27), // "sig_setInstancedGridSpacing"
QT_MOC_LITERAL(229, 23), // "sig_makeIGridSeethrough"
QT_MOC_LITERAL(253, 21), // "sig_shadeIGridLambert"
QT_MOC_LITERAL(275, 24), // "sig_setModelRotationFLag"
QT_MOC_LITERAL(300, 20), // "slot_setCurrentModel"
QT_MOC_LITERAL(321, 35), // "slot_setCurrentSurfaceShaderP..."
QT_MOC_LITERAL(357, 39), // "slot_setCurrentPostprocessSha..."
QT_MOC_LITERAL(397, 39), // "slot_setCurrentPostSurfaceSha..."
QT_MOC_LITERAL(437, 28), // "slot_setCurrentMatcapTexture"
QT_MOC_LITERAL(466, 24), // "slot_setInstancedGridRes"
QT_MOC_LITERAL(491, 28), // "slot_setInstancedGridSpacing"
QT_MOC_LITERAL(520, 24), // "slot_makeIGridSeethrough"
QT_MOC_LITERAL(545, 22), // "slot_shadeIGridLambert"
QT_MOC_LITERAL(568, 25) // "slot_setModelRotationFLag"

    },
    "ShaderControls\0sig_setCurrentModel\0\0"
    "sig_setCurrentSurfaceShaderProgram\0"
    "sig_setCurrentPostprocessShaderProgram\0"
    "sig_setCurrentPostSurfaceShaderProgram\0"
    "sig_setCurrentMatcapTexture\0"
    "sig_setInstancedGridRes\0"
    "sig_setInstancedGridSpacing\0"
    "sig_makeIGridSeethrough\0sig_shadeIGridLambert\0"
    "sig_setModelRotationFLag\0slot_setCurrentModel\0"
    "slot_setCurrentSurfaceShaderProgram\0"
    "slot_setCurrentPostprocessShaderProgram\0"
    "slot_setCurrentPostSurfaceShaderProgram\0"
    "slot_setCurrentMatcapTexture\0"
    "slot_setInstancedGridRes\0"
    "slot_setInstancedGridSpacing\0"
    "slot_makeIGridSeethrough\0"
    "slot_shadeIGridLambert\0slot_setModelRotationFLag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShaderControls[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  134,    2, 0x06,    1 /* Public */,
       3,    1,  137,    2, 0x06,    3 /* Public */,
       4,    1,  140,    2, 0x06,    5 /* Public */,
       5,    1,  143,    2, 0x06,    7 /* Public */,
       6,    1,  146,    2, 0x06,    9 /* Public */,
       7,    1,  149,    2, 0x06,   11 /* Public */,
       8,    1,  152,    2, 0x06,   13 /* Public */,
       9,    1,  155,    2, 0x06,   15 /* Public */,
      10,    1,  158,    2, 0x06,   17 /* Public */,
      11,    1,  161,    2, 0x06,   19 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      12,    1,  164,    2, 0x0a,   21 /* Public */,
      13,    1,  167,    2, 0x0a,   23 /* Public */,
      14,    1,  170,    2, 0x0a,   25 /* Public */,
      15,    1,  173,    2, 0x0a,   27 /* Public */,
      16,    1,  176,    2, 0x0a,   29 /* Public */,
      17,    1,  179,    2, 0x0a,   31 /* Public */,
      18,    1,  182,    2, 0x0a,   33 /* Public */,
      19,    1,  185,    2, 0x0a,   35 /* Public */,
      20,    1,  188,    2, 0x0a,   37 /* Public */,
      21,    1,  191,    2, 0x0a,   39 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
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
        case 3: _t->sig_setCurrentPostSurfaceShaderProgram((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->sig_setCurrentMatcapTexture((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->sig_setInstancedGridRes((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 6: _t->sig_setInstancedGridSpacing((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->sig_makeIGridSeethrough((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->sig_shadeIGridLambert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->sig_setModelRotationFLag((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->slot_setCurrentModel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->slot_setCurrentSurfaceShaderProgram((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->slot_setCurrentPostprocessShaderProgram((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->slot_setCurrentPostSurfaceShaderProgram((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->slot_setCurrentMatcapTexture((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->slot_setInstancedGridRes((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 16: _t->slot_setInstancedGridSpacing((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->slot_makeIGridSeethrough((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 18: _t->slot_shadeIGridLambert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 19: _t->slot_setModelRotationFLag((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_setCurrentPostSurfaceShaderProgram)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ShaderControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_setCurrentMatcapTexture)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ShaderControls::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_setInstancedGridRes)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ShaderControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_setInstancedGridSpacing)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ShaderControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_makeIGridSeethrough)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ShaderControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_shadeIGridLambert)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ShaderControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShaderControls::sig_setModelRotationFLag)) {
                *result = 9;
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
, QtPrivate::TypeAndForceComplete<ShaderControls, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


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
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 20;
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
void ShaderControls::sig_setCurrentPostSurfaceShaderProgram(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ShaderControls::sig_setCurrentMatcapTexture(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ShaderControls::sig_setInstancedGridRes(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ShaderControls::sig_setInstancedGridSpacing(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ShaderControls::sig_makeIGridSeethrough(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ShaderControls::sig_shadeIGridLambert(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ShaderControls::sig_setModelRotationFLag(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
