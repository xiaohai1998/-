#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QList>
#include<QLabel>
#include<QSerialPortInfo>
#include<QSerialPort>
#include<QIODevice>
#include<QMessageBox>
#include<QByteArray>
#include"myserial.h"
#include<winsock2.h>
#include<windows.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void InitConnect();
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_7_clicked();
    void set_close_port_label();
    void open_port_handle();

    void show_rsa_key(QString);
    void show_rsa_pub_encrypt(QByteArray);
    void show_rsa_pri_decrypt(QByteArray);
    void show_rsa_pri_encrypt(QByteArray);
    void show_rsa_pub_decrypt(QByteArray);
    void show_rsa_pri_sign(QByteArray);
    void show_rsa_pub_verify(QByteArray);
    void show_sm2_encrypt(QByteArray);
    void show_sha1_encrypt(QByteArray);
    void show_sha256_encrypt(QByteArray);
    void show_socket_connect(QByteArray);
    void show_socket_send(QByteArray);
    void show_socket_rec(QByteArray);
    void show_ota_http(QByteArray);
    void show_ota_trig_up(QByteArray);
    void show_ota_check_state(QByteArray);
    void show_ota_end_update(QByteArray);
    void show_sys_handle(QByteArray);

    void show_init_fail_com();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();



    void on_pushButton_9_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_26_clicked();


private:
    bool isOpenCom();

private:
    Ui::MainWindow *ui;
    QLabel *com_label_show;
    my_qserial *local_serial;
};

#endif // MAINWINDOW_H
