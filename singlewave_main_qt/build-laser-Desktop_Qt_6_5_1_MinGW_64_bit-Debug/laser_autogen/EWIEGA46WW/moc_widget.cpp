/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../laser/widget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSWidgetENDCLASS = QtMocHelpers::stringData(
    "Widget",
    "clickedStartBlock",
    "",
    "clickedGenerateBlock",
    "slice",
    "char*",
    "s",
    "from",
    "to",
    "setFrequency",
    "setVoltage",
    "setCurrent",
    "readSerialData",
    "t",
    "setTime",
    "QString&"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSWidgetENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[7];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[6];
    char stringdata5[6];
    char stringdata6[2];
    char stringdata7[5];
    char stringdata8[3];
    char stringdata9[13];
    char stringdata10[11];
    char stringdata11[11];
    char stringdata12[15];
    char stringdata13[2];
    char stringdata14[8];
    char stringdata15[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSWidgetENDCLASS_t qt_meta_stringdata_CLASSWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Widget"
        QT_MOC_LITERAL(7, 17),  // "clickedStartBlock"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 20),  // "clickedGenerateBlock"
        QT_MOC_LITERAL(47, 5),  // "slice"
        QT_MOC_LITERAL(53, 5),  // "char*"
        QT_MOC_LITERAL(59, 1),  // "s"
        QT_MOC_LITERAL(61, 4),  // "from"
        QT_MOC_LITERAL(66, 2),  // "to"
        QT_MOC_LITERAL(69, 12),  // "setFrequency"
        QT_MOC_LITERAL(82, 10),  // "setVoltage"
        QT_MOC_LITERAL(93, 10),  // "setCurrent"
        QT_MOC_LITERAL(104, 14),  // "readSerialData"
        QT_MOC_LITERAL(119, 1),  // "t"
        QT_MOC_LITERAL(121, 7),  // "setTime"
        QT_MOC_LITERAL(129, 8)   // "QString&"
    },
    "Widget",
    "clickedStartBlock",
    "",
    "clickedGenerateBlock",
    "slice",
    "char*",
    "s",
    "from",
    "to",
    "setFrequency",
    "setVoltage",
    "setCurrent",
    "readSerialData",
    "t",
    "setTime",
    "QString&"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x08,    1 /* Private */,
       3,    0,   63,    2, 0x08,    2 /* Private */,
       4,    3,   64,    2, 0x08,    3 /* Private */,
       9,    0,   71,    2, 0x08,    7 /* Private */,
      10,    0,   72,    2, 0x08,    8 /* Private */,
      11,    0,   73,    2, 0x08,    9 /* Private */,
      12,    1,   74,    2, 0x08,   10 /* Private */,
      14,    1,   77,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 5, 0x80000000 | 5, QMetaType::Int, QMetaType::Int,    6,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, 0x80000000 | 15,   13,

       0        // eod
};

Q_CONSTINIT const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Widget, std::true_type>,
        // method 'clickedStartBlock'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clickedGenerateBlock'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slice'
        QtPrivate::TypeAndForceComplete<char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setFrequency'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setVoltage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setCurrent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readSerialData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setTime'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>
    >,
    nullptr
} };

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clickedStartBlock(); break;
        case 1: _t->clickedGenerateBlock(); break;
        case 2: { char* _r = _t->slice((*reinterpret_cast< std::add_pointer_t<char*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast< char**>(_a[0]) = std::move(_r); }  break;
        case 3: _t->setFrequency(); break;
        case 4: _t->setVoltage(); break;
        case 5: _t->setCurrent(); break;
        case 6: _t->readSerialData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->setTime((*reinterpret_cast< std::add_pointer_t<QString&>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
