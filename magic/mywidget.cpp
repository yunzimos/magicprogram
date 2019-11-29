#include "mywidget.h"
#include "ui_mywidget.h"

#include <QProcess>
#include <QTimer>
#include <QFile>
#include <math.h>
#include <QIODevice>
#include <QTextStream>

#define MODULES_DRIVER "/root/modules_driver.sh" //加载模块命令目录

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //设置背景
    QPalette palette1=this->palette();
    palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/bg.png")));
    this->setPalette(palette1);
    //this->setAutoFillBackground(true);

    //设置定时器
    QTimer *timer =new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshStatus()) );

    Insmod_moudles();//加载模块
    sleep(3);
    timer->start(1000); // 1 seconds single-shot timer
    GetStatus();

}

MyWidget::~MyWidget()
{
    delete ui;
}



void MyWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void MyWidget:: Insmod_moudles()
{
    QProcess *process = new QProcess;
    QStringList str;
    str << "";
    process->start(MODULES_DRIVER,str);
    process->waitForStarted();
    sleep(3);

    fd_irda = open("/dev/irda", 0);
    if (fd_irda < 0) {
        printf("Can't open /dev/irda\n");
    }
    fd_smog = open("/dev/smog", 0);
    if (fd_smog < 0) {
        printf("Can't open /dev/smog\n");
    }
    fd_miph = open("/dev/miph", 0);
    if (fd_miph < 0) {
        printf("Can't open /dev/miph\n");
    }
    fd_sht11 = open("/dev/sht11", 0);
    if (fd_sht11 < 0) {
        printf("Can't open /dev/sht11\n");
    }
}

//槽函数

void MyWidget::on_pb_motor_on_clicked()
{
    QProcess *process=new QProcess;
    process->start("/root/motor/dcm_test");
    process->waitForStarted();
}

void MyWidget::on_pb_motor_off_clicked()
{
    QProcess *process = new QProcess;
    process->start("/root/motor/motor_stop.sh");
    process->waitForStarted();
}

void MyWidget::on_pb_led_on_clicked()
{
    QProcess *process = new QProcess;
    process->start("/root/leds/magicleds_test");
    qDebug()<<"Exec leds app...";
    process->waitForStarted();
}

void MyWidget::on_pb_led_off_clicked()
{
    QProcess *process = new QProcess;
    process->start("/root/leds/leds_stop.sh");
    process->waitForStarted();
}

void MyWidget::on_pb_buzzer_on_clicked()
{
    QProcess *process = new QProcess;
    QStringList str;

    str.clear();
    str << "1" << "1";
    process->start("/root/buzzer/gpio_test",str);
    process->waitForStarted();
}



void MyWidget::on_pb_buzzer_off_clicked()
{
    QProcess *process = new QProcess;
    QStringList str;
    str.clear();
    str << "0" << "0";
    process->start("/root/buzzer/gpio_test",str);
    process->waitForStarted();
}

void MyWidget::on_pb_matrix_on_clicked()
{
    QProcess *process = new QProcess;

    process->start("/root/lcd/s3c24xx_lcd_test");
    process->waitForStarted();
}

void MyWidget::on_pb_matrix_off_clicked()
{
    QProcess *process = new QProcess;
    process->start("/root/lcd/lcd_stop.sh");
    process->waitForStarted();
}

void MyWidget::refreshStatus()
{
    GetStatus();
}

void MyWidget::delay(int time)
{
    int i;
    for(i=0;i<time*1000;)
    i++;
}

void MyWidget::calc_sht11(float *p_humidity,float *p_temprature)
{
    const float C1=-0.40;
    const float C2=0.0405;
    const float C3=-0.0000028;
    const float T1=0.01;
    const float T2=0.00008;

    float rh=*p_humidity;
    float t=*p_temprature;
    float rh_lin;
    float rh_true;
    float t_C;

    t_C=t*0.01-40;
    rh_lin=C3*rh*rh+C2*rh+C1;
    rh_true=(t_C-25)*(T1+T2*rh)+rh_lin;
    if(rh_true>100)rh_true=100;
    if(rh_true<0.1)rh_true=0.1;

    *p_temprature=t_C;
    *p_humidity=rh_true;
}
float MyWidget::calc_dewpoint(float h,float t)
{
    float k,dew_point;
    k=(log10(h)-2)/0.4343+(17.62*t)/(243.12+t);
    dew_point=243.12*k/(17.62-k);
    return dew_point;
}

void MyWidget::Show_sht11()
{
    int ret;
    unsigned int value_t=0;
    unsigned int value_h=0;
    float fvalue_t,fvalue_h;
    float dew_point;

    fvalue_t=0.0,fvalue_h=0.0;value_t=0;value_h=0;

    ioctl(fd_sht11,0);
    ret=read(fd_sht11,&value_t,sizeof(value_t));
    if(ret<0)
    {
            printf("read value_t err!\n");

    }

    value_t=value_t&0x3fff;
    fvalue_t=(float)value_t;

    ioctl(fd_sht11,1);
    ret=read(fd_sht11,&value_h,sizeof(value_h));

    if(ret<0)
    {
            printf("read value_h err!\n");
    }
    value_h=value_h&0xfff;
    fvalue_h=(float)value_h;
    calc_sht11(&fvalue_h,&fvalue_t);
    dew_point=calc_dewpoint(fvalue_h,fvalue_t);
    //printf("temp:%fc humi:%f dew point:%fc\n",fvalue_t,fvalue_h,dew_point);
    ui->label_Stemp->setText(QString("%1").arg(fvalue_t).mid(0,5));
    ui->label_Shumi->setText(QString("%1").arg(fvalue_h).mid(0,5));
    //sleep(1);
}



void MyWidget::Show_irda()
{
    int ret;
    int irda_cnt;

    ui->label_Sirda->setText("normal");
    ret = read(fd_irda,&irda_cnt, sizeof(irda_cnt));
    if (ret < 0) {
        printf("read err!\n");

    }

    if (irda_cnt){
        ui->label_Sirda->setText("someone");
    }
    else if(!irda_cnt){
        ui->label_Sirda->setText("normal");
    }

}
void MyWidget::Show_smog()
{
    int ret;
    int smog_cnt;

    ui->label_Ssmog->setText("normal");
    ret = read(fd_smog,&smog_cnt, sizeof(smog_cnt));
    if (ret < 0) {
        printf("read err!\n");
    }

    if (smog_cnt){
        ui->label_Ssmog->setText("firing");
    }
    else if(!smog_cnt){
        ui->label_Ssmog->setText("normal");
    }

}
void MyWidget::Show_miph()
{
    int ret;
    int miph_cnt;

    ui->label_Smiph->setText("normal");
    ret = read(fd_miph,&miph_cnt, sizeof(miph_cnt));
    if (ret < 0) {
        printf("read fd_miph err!\n");

    }
    if (miph_cnt){
        ui->label_Smiph->setText("normal");

    }
    else if(!miph_cnt){
        ui->label_Smiph->setText("noise");
    }
}

void MyWidget::GetStatus()
{
    Show_sht11();
    Show_irda();
    Show_smog();
    Show_miph();
}

