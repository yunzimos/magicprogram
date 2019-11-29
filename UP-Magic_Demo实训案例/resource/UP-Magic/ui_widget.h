/********************************************************************************
** Form generated from reading ui file 'widget.ui'
**
** Created: Fri May 14 13:47:37 2010
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGroupBox *groupBox_status;
    QLabel *label_temp;
    QLabel *label_Stemp;
    QLabel *label_humi;
    QLabel *label_Shumi;
    QLabel *label_irda;
    QLabel *label_Sirda;
    QLabel *label_smog;
    QLabel *label_Ssmog;
    QLabel *label_Smiph;
    QLabel *label_miph;
    QLabel *label;
    QGroupBox *groupBox_contrl;
    QPushButton *pb_motor_off;
    QLabel *label_motor;
    QLabel *label_led;
    QPushButton *pb_led_off;
    QPushButton *pb_led_on;
    QLabel *label_buzzer;
    QPushButton *pb_buzzer_off;
    QPushButton *pb_buzzer_on;
    QLabel *label_matrix;
    QPushButton *pb_matrix_off;
    QPushButton *pb_matrix_on;
    QPushButton *pb_motor_on;

    void setupUi(QWidget *Widget)
    {
    if (Widget->objectName().isEmpty())
        Widget->setObjectName(QString::fromUtf8("Widget"));
    Widget->resize(320, 240);
    groupBox_status = new QGroupBox(Widget);
    groupBox_status->setObjectName(QString::fromUtf8("groupBox_status"));
    groupBox_status->setGeometry(QRect(10, 10, 111, 171));
    QPalette palette;
    QBrush brush(QColor(0, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    QBrush brush1(QColor(118, 116, 108, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    groupBox_status->setPalette(palette);
    label_temp = new QLabel(groupBox_status);
    label_temp->setObjectName(QString::fromUtf8("label_temp"));
    label_temp->setGeometry(QRect(3, 20, 40, 20));
    label_Stemp = new QLabel(groupBox_status);
    label_Stemp->setObjectName(QString::fromUtf8("label_Stemp"));
    label_Stemp->setGeometry(QRect(50, 20, 50, 20));
    label_humi = new QLabel(groupBox_status);
    label_humi->setObjectName(QString::fromUtf8("label_humi"));
    label_humi->setGeometry(QRect(3, 50, 40, 20));
    QPalette palette1;
    QBrush brush2(QColor(255, 85, 0, 255));
    brush2.setStyle(Qt::SolidPattern);
    palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
    palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
    palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
    label_humi->setPalette(palette1);
    label_Shumi = new QLabel(groupBox_status);
    label_Shumi->setObjectName(QString::fromUtf8("label_Shumi"));
    label_Shumi->setGeometry(QRect(50, 50, 50, 20));
    label_irda = new QLabel(groupBox_status);
    label_irda->setObjectName(QString::fromUtf8("label_irda"));
    label_irda->setGeometry(QRect(3, 80, 40, 20));
    label_Sirda = new QLabel(groupBox_status);
    label_Sirda->setObjectName(QString::fromUtf8("label_Sirda"));
    label_Sirda->setGeometry(QRect(50, 80, 61, 20));
    label_smog = new QLabel(groupBox_status);
    label_smog->setObjectName(QString::fromUtf8("label_smog"));
    label_smog->setGeometry(QRect(3, 110, 40, 20));
    label_Ssmog = new QLabel(groupBox_status);
    label_Ssmog->setObjectName(QString::fromUtf8("label_Ssmog"));
    label_Ssmog->setGeometry(QRect(50, 110, 61, 20));
    label_Smiph = new QLabel(groupBox_status);
    label_Smiph->setObjectName(QString::fromUtf8("label_Smiph"));
    label_Smiph->setGeometry(QRect(50, 140, 61, 20));
    label_miph = new QLabel(groupBox_status);
    label_miph->setObjectName(QString::fromUtf8("label_miph"));
    label_miph->setGeometry(QRect(3, 140, 40, 20));
    label = new QLabel(Widget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(0, 200, 151, 31));
    QPalette palette2;
    QBrush brush3(QColor(0, 0, 255, 255));
    brush3.setStyle(Qt::SolidPattern);
    palette2.setBrush(QPalette::Active, QPalette::WindowText, brush3);
    palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
    palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    label->setPalette(palette2);
    QFont font;
    font.setPointSize(10);
    label->setFont(font);
    groupBox_contrl = new QGroupBox(Widget);
    groupBox_contrl->setObjectName(QString::fromUtf8("groupBox_contrl"));
    groupBox_contrl->setGeometry(QRect(160, 10, 151, 221));
    QPalette palette3;
    QBrush brush4(QColor(255, 0, 0, 255));
    brush4.setStyle(Qt::SolidPattern);
    palette3.setBrush(QPalette::Active, QPalette::WindowText, brush4);
    palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
    palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    groupBox_contrl->setPalette(palette3);
    pb_motor_off = new QPushButton(groupBox_contrl);
    pb_motor_off->setObjectName(QString::fromUtf8("pb_motor_off"));
    pb_motor_off->setGeometry(QRect(10, 40, 51, 21));
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/images/off.png")), QIcon::Normal, QIcon::Off);
    pb_motor_off->setIcon(icon);
    pb_motor_off->setAutoDefault(false);
    pb_motor_off->setDefault(false);
    label_motor = new QLabel(groupBox_contrl);
    label_motor->setObjectName(QString::fromUtf8("label_motor"));
    label_motor->setGeometry(QRect(90, 20, 51, 41));
    label_motor->setPixmap(QPixmap(QString::fromUtf8(":/images/motor.png")));
    label_led = new QLabel(groupBox_contrl);
    label_led->setObjectName(QString::fromUtf8("label_led"));
    label_led->setGeometry(QRect(90, 70, 51, 41));
    label_led->setPixmap(QPixmap(QString::fromUtf8(":/images/led.png")));
    pb_led_off = new QPushButton(groupBox_contrl);
    pb_led_off->setObjectName(QString::fromUtf8("pb_led_off"));
    pb_led_off->setGeometry(QRect(10, 90, 51, 21));
    pb_led_off->setIcon(icon);
    pb_led_on = new QPushButton(groupBox_contrl);
    pb_led_on->setObjectName(QString::fromUtf8("pb_led_on"));
    pb_led_on->setGeometry(QRect(10, 70, 51, 21));
    QIcon icon1;
    icon1.addPixmap(QPixmap(QString::fromUtf8(":/images/on.png")), QIcon::Normal, QIcon::Off);
    pb_led_on->setIcon(icon1);
    label_buzzer = new QLabel(groupBox_contrl);
    label_buzzer->setObjectName(QString::fromUtf8("label_buzzer"));
    label_buzzer->setGeometry(QRect(90, 120, 51, 41));
    label_buzzer->setPixmap(QPixmap(QString::fromUtf8(":/images/buzzer.png")));
    pb_buzzer_off = new QPushButton(groupBox_contrl);
    pb_buzzer_off->setObjectName(QString::fromUtf8("pb_buzzer_off"));
    pb_buzzer_off->setGeometry(QRect(10, 140, 51, 21));
    pb_buzzer_off->setIcon(icon);
    pb_buzzer_on = new QPushButton(groupBox_contrl);
    pb_buzzer_on->setObjectName(QString::fromUtf8("pb_buzzer_on"));
    pb_buzzer_on->setGeometry(QRect(10, 120, 51, 21));
    pb_buzzer_on->setIcon(icon1);
    label_matrix = new QLabel(groupBox_contrl);
    label_matrix->setObjectName(QString::fromUtf8("label_matrix"));
    label_matrix->setGeometry(QRect(90, 170, 51, 41));
    label_matrix->setPixmap(QPixmap(QString::fromUtf8(":/images/matrix.png")));
    pb_matrix_off = new QPushButton(groupBox_contrl);
    pb_matrix_off->setObjectName(QString::fromUtf8("pb_matrix_off"));
    pb_matrix_off->setGeometry(QRect(10, 190, 51, 21));
    pb_matrix_off->setIcon(icon);
    pb_matrix_on = new QPushButton(groupBox_contrl);
    pb_matrix_on->setObjectName(QString::fromUtf8("pb_matrix_on"));
    pb_matrix_on->setGeometry(QRect(10, 170, 51, 21));
    pb_matrix_on->setIcon(icon1);
    pb_motor_on = new QPushButton(groupBox_contrl);
    pb_motor_on->setObjectName(QString::fromUtf8("pb_motor_on"));
    pb_motor_on->setGeometry(QRect(10, 20, 51, 21));
    pb_motor_on->setIcon(icon1);

    retranslateUi(Widget);

    QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
    Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
    groupBox_status->setTitle(QApplication::translate("Widget", "\347\212\266\346\200\201\345\215\225\345\205\203", 0, QApplication::UnicodeUTF8));
    label_temp->setText(QApplication::translate("Widget", "\346\270\251\345\272\246:", 0, QApplication::UnicodeUTF8));
    label_Stemp->setText(QApplication::translate("Widget", "Null", 0, QApplication::UnicodeUTF8));
    label_humi->setText(QApplication::translate("Widget", "\346\271\277\345\272\246:", 0, QApplication::UnicodeUTF8));
    label_Shumi->setText(QApplication::translate("Widget", "Null", 0, QApplication::UnicodeUTF8));
    label_irda->setText(QApplication::translate("Widget", "\347\272\242\345\244\226:", 0, QApplication::UnicodeUTF8));
    label_Sirda->setText(QApplication::translate("Widget", "Null", 0, QApplication::UnicodeUTF8));
    label_smog->setText(QApplication::translate("Widget", "\347\203\237\351\233\276:", 0, QApplication::UnicodeUTF8));
    label_Ssmog->setText(QApplication::translate("Widget", "Null", 0, QApplication::UnicodeUTF8));
    label_Smiph->setText(QApplication::translate("Widget", "Null", 0, QApplication::UnicodeUTF8));
    label_miph->setText(QApplication::translate("Widget", "\351\272\246\345\205\213:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Widget", "  \345\215\232\345\210\233\347\247\221\346\212\200   \345\265\214\345\205\245\344\272\222\345\212\250", 0, QApplication::UnicodeUTF8));
    groupBox_contrl->setTitle(QApplication::translate("Widget", "\346\216\247\345\210\266\345\215\225\345\205\203", 0, QApplication::UnicodeUTF8));
    pb_motor_off->setText(QApplication::translate("Widget", "\345\205\263", 0, QApplication::UnicodeUTF8));
    label_motor->setText(QString());
    label_led->setText(QString());
    pb_led_off->setText(QApplication::translate("Widget", "\345\205\263", 0, QApplication::UnicodeUTF8));
    pb_led_on->setText(QApplication::translate("Widget", "\345\274\200", 0, QApplication::UnicodeUTF8));
    label_buzzer->setText(QString());
    pb_buzzer_off->setText(QApplication::translate("Widget", "\345\205\263", 0, QApplication::UnicodeUTF8));
    pb_buzzer_on->setText(QApplication::translate("Widget", "\345\274\200", 0, QApplication::UnicodeUTF8));
    label_matrix->setText(QString());
    pb_matrix_off->setText(QApplication::translate("Widget", "\345\205\263", 0, QApplication::UnicodeUTF8));
    pb_matrix_on->setText(QApplication::translate("Widget", "\345\274\200", 0, QApplication::UnicodeUTF8));
    pb_motor_on->setText(QApplication::translate("Widget", "\345\274\200", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Widget);
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
