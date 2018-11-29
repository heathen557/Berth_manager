/****************************************************************************
** Meta object code from reading C++ file 'add_detetion.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../add_detetion.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'add_detetion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_add_detetion_t {
    QByteArrayData data[7];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_add_detetion_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_add_detetion_t qt_meta_stringdata_add_detetion = {
    {
QT_MOC_LITERAL(0, 0, 12), // "add_detetion"
QT_MOC_LITERAL(1, 13, 24), // "addDetectionPlane_signal"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 13), // "cancel_signal"
QT_MOC_LITERAL(4, 53, 24), // "on_ok_pushButton_clicked"
QT_MOC_LITERAL(5, 78, 28), // "on_cancel_pushButton_clicked"
QT_MOC_LITERAL(6, 107, 16) // "updateModel_slot"

    },
    "add_detetion\0addDetectionPlane_signal\0"
    "\0cancel_signal\0on_ok_pushButton_clicked\0"
    "on_cancel_pushButton_clicked\0"
    "updateModel_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_add_detetion[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    9,   39,    2, 0x06 /* Public */,
       3,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   59,    2, 0x08 /* Private */,
       5,    0,   60,    2, 0x08 /* Private */,
       6,    1,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    2,

       0        // eod
};

void add_detetion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        add_detetion *_t = static_cast<add_detetion *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addDetectionPlane_signal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8])),(*reinterpret_cast< QString(*)>(_a[9]))); break;
        case 1: _t->cancel_signal(); break;
        case 2: _t->on_ok_pushButton_clicked(); break;
        case 3: _t->on_cancel_pushButton_clicked(); break;
        case 4: _t->updateModel_slot((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (add_detetion::*_t)(QString , QString , QString , QString , QString , QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&add_detetion::addDetectionPlane_signal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (add_detetion::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&add_detetion::cancel_signal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject add_detetion::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_add_detetion.data,
      qt_meta_data_add_detetion,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *add_detetion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *add_detetion::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_add_detetion.stringdata0))
        return static_cast<void*>(const_cast< add_detetion*>(this));
    return QDialog::qt_metacast(_clname);
}

int add_detetion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void add_detetion::addDetectionPlane_signal(QString _t1, QString _t2, QString _t3, QString _t4, QString _t5, QString _t6, QString _t7, QString _t8, QString _t9)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void add_detetion::cancel_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
