#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include<QDebug>
#include<QList>
#include<QLabel>
#include<QSerialPortInfo>
#include<QSerialPort>
#include<QIODevice>
#include<QMessageBox>
#include<QByteArray>
#include"cdownthread.h"
#include"getcomresult.h"
#include<QLatin1Char>
#include"ctool.h"
#include"myserial.h"
#include<iostream>
#include<QDateTime>
using namespace std;
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void InitConnect();
private slots:

    void on_buttonBox_accepted();
    void set_close_port_label();
    void show_sha_result(QByteArray);
    void show_hmac_result(QByteArray);
    void show_sm2_result(QByteArray);
    void show_rsa_result(QByteArray);
    void show_ota_result(QByteArray);
    void show_sys_result(QByteArray);
    void show_time_result(QByteArray);
    void show_task_result(QByteArray);
    void show_param_result(QByteArray);
    void show_network_result(QByteArray);
    void show_tts_result(QByteArray);
    void show_mqtt_result(QByteArray);
    void show_tool_result(QByteArray);
    void open_port_handle();
    void on_pushButton_clicked();
    void show_serial_result();



    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    QString sha_data();
    QString rsa_data();
    QString socket_data();
    QString sys_data();
    QString ota_data();
    QString sm2_data();
    QString mqtt_data();
    QString time_data();
    QString hmac_data();
    QString task_data();
    QString param_data();
    QString tts_data();
    QString tool_data();
private:
    Ui::Form *ui;
    QTimer *m_timer;
    QLabel *com_label_show;
    QString m_comBoxText;
};
QString create_crc(QString s1);
#endif // FORM_H
