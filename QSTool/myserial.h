#ifndef MYSERIAL_H
#define MYSERIAL_H


#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include "structs.h"
#include<QTimer>
typedef int (*thread_fun)(void);
class my_qserial  : public QObject
{
    Q_OBJECT
public:
    explicit my_qserial (QObject *parent = nullptr);
    ~my_qserial();
    void show_func_id();
    void init_port(QString portname="COM11",int baud=115200);
    QSerialPort *port;
    void start(QString portname,int baud);
    bool isopenSerial();
    void setData(QString data);
    void set_show_slot(show_slots b);
    void set_show_slot2(show_slots b);
    void close_port();
    void open_port();
    void setFunction(thread_fun a);
    void set_portName_bit(QString,int);


signals:

public slots:
    void show_slots_id();
    void handle_data();
    void handle_data2();
    void write_data();
signals:
    void queue_delete(QByteArray);
    void API_COMM_GetLocalIp(QByteArray);
    void API_COMM_Sntp_Start(QByteArray);
    void API_COMM_WIFIGetAPInfo(QByteArray);
    void API_COMM_WIFIGetMac(QByteArray);
    void API_COMM_WIFIGetquality(QByteArray);
    void API_COMM_WIFIGetStatus(QByteArray);

    void API_COMM_WIFIGetVersion(QByteArray);
    void API_COMM_WIFISetMac(QByteArray);
    void API_COMM_WIFISetNetWork(QByteArray);







    void API_COMM_ModuleDisconnect(QByteArray);
    void API_COMM_ModuleGetHostByName(QByteArray);
    void API_COMM_ModuleGetquality(QByteArray);
    void API_COMM_ModuleGetStatus(QByteArray);
    void http_get(QByteArray);
    void http_post(QByteArray);
    void sys_btn_unreg(QByteArray);
    void sys_button(QByteArray);
    void time_stop(QByteArray);
    void param_delete_data(QByteArray);
    void C2ToInt (QByteArray);
    void BcdToUint64 (QByteArray);
    void UintToC4(QByteArray);
    void C4ToUint(QByteArray);
    void CStrlcpy(QByteArray);
    void Getrand(QByteArray);
    void GetTimestamp(QByteArray);
    void StrCaseCmp(QByteArray);
    void StrRemovechar(QByteArray);
    void tlv_build(QByteArray);
    void tlv_destory(QByteArray);
    void hex_to_dec(QByteArray);
    void asc_to_int(QByteArray);
    void bcd_to_int(QByteArray);
    void int_to_bcd(QByteArray);
    void hex_to_asc(QByteArray);
    void asc_to_hex(QByteArray);
    void asc_to_bcd(QByteArray);
    void bcd_to_asc(QByteArray);
    void gbk_to_utf(QByteArray);
    void utf_to_gbk(QByteArray);
    void hmac_sig(QByteArray);
    void url_encode(QByteArray);
    void url_decode(QByteArray);
    void close_port_sig();
    void open_port_sig();
    void thread_sig();
    void sha1_sig(QByteArray);
    void show_rsa_key(QString);
    void ras_public_encrypt(QByteArray);
    void rsa_pri_dec(QByteArray);
    void rsa_pri_enc(QByteArray);
    void rsa_pub_dec(QByteArray);
    void rsa_pri_sign(QByteArray);
    void rsa_pub_verify(QByteArray);
    void sm2_enc(QByteArray);
    void sha1_enc(QByteArray);
    void sha256_enc(QByteArray);
    void sock_con(QByteArray);
    void sock_rec(QByteArray);
    void sock_send(QByteArray);
    void ota_http_up(QByteArray);
    void ota_trig_up(QByteArray);
    void ota_check_sta(QByteArray);
    void ota_end_up(QByteArray);
    void sys_signal(QByteArray);
    void sys_reboot_sig(QByteArray);

    void get_time(QByteArray);
    void get_task_tick(QByteArray);
    void time_create(QByteArray);
    void time_open(QByteArray);
    void time_delete(QByteArray);
    void task_create(QByteArray);
    void task_delete(QByteArray);
    void queue_create(QByteArray);
    void msg_send(QByteArray);
    void msg_receive(QByteArray);
    void msg_delete(QByteArray);
    void msg_reset(QByteArray);
    void semaphore_create(QByteArray);
    void semaphore_take(QByteArray);
    void semaphore_free(QByteArray);
    void semaphore_delete(QByteArray);
    void param_int_read(QByteArray);
    void param_int_write(QByteArray);
    void param_str_read(QByteArray);
    void param_str_write(QByteArray);
    void sys_led_set(QByteArray);
    void sys_led_get(QByteArray);
    void sys_battery(QByteArray);
    void sys_speaker(QByteArray);
    void sys_libversion(QByteArray);
    void sys_sdkversion(QByteArray);
    void sys_memory_realloc(QByteArray);
    void sys_memory_calloc(QByteArray);
    void sys_memory_free(QByteArray);
    void initcomfail();
    void tts_set_speed(QByteArray);
    void tts_set_pitch(QByteArray);
    void tts_beep_player(QByteArray);
    void tts_play_audio(QByteArray);
    void tts_play_aduio_string(QByteArray);
    void tts_check_state(QByteArray);
    void mqtt_con(QByteArray);
    void mqtt_discon(QByteArray);
    void mqtt_publi(QByteArray);
    void mqtt_subs(QByteArray);
    void mqtt_unsubs(QByteArray);
    void mqtt_close(QByteArray);


private:

    QString m_name;
    int m_bit;
    thread_fun do_work;
    show_slots will_show;
    QString m_data;
    bool isOpenSucc;
    QThread *my_thread;
};
#endif // MYSERIAL_H
