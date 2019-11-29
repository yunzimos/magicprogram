/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created: Fri May 14 16:56:46 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Widget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      35,    7,    7,    7, 0x08,
      61,    7,    7,    7, 0x08,
      88,    7,    7,    7, 0x08,
     114,    7,    7,    7, 0x08,
     138,    7,    7,    7, 0x08,
     161,    7,    7,    7, 0x08,
     187,    7,    7,    7, 0x08,
     212,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Widget[] = {
    "Widget\0\0on_pb_matrix_off_clicked()\0"
    "on_pb_matrix_on_clicked()\0"
    "on_pb_buzzer_off_clicked()\0"
    "on_pb_buzzer_on_clicked()\0"
    "on_pb_led_off_clicked()\0on_pb_led_on_clicked()\0"
    "on_pb_motor_off_clicked()\0"
    "on_pb_motor_on_clicked()\0refreshStatus()\0"
};

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget,
      qt_meta_data_Widget, 0 }
};

const QMetaObject *Widget::metaObject() const
{
    return &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Widget))
	return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pb_matrix_off_clicked(); break;
        case 1: on_pb_matrix_on_clicked(); break;
        case 2: on_pb_buzzer_off_clicked(); break;
        case 3: on_pb_buzzer_on_clicked(); break;
        case 4: on_pb_led_off_clicked(); break;
        case 5: on_pb_led_on_clicked(); break;
        case 6: on_pb_motor_off_clicked(); break;
        case 7: on_pb_motor_on_clicked(); break;
        case 8: refreshStatus(); break;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
