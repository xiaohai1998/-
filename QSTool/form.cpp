#include "form.h"
#include "ui_form.h"
QList<QSerialPortInfo> serial_list2;
my_qserial myserial2;
#define MAX_DATA_LEN 1024*4
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setWindowTitle("QS100测试工具");
  //  setFixedSize(816,655);
    serial_list2 = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &info, serial_list2) {
        ui->serial_num_comboBox->addItem(info.portName());
    }
    for(QList<QSerialPortInfo>::iterator it=serial_list2.begin();it!=serial_list2.end();++it){
        if(it->portName()=="COM11"){
            ui->serial_num_comboBox->setCurrentText("COM11");
            break;
        }
    }
    com_label_show=new QLabel(this);
    com_label_show->resize(200,30);
    com_label_show->move(this->width()-150,this->height()-60);
    InitConnect();
    m_comBoxText="sha1";
}

Form::~Form()
{
    delete ui;
}

void Form::InitConnect()
{
    connect(ui->pushButton,&QPushButton::clicked,&myserial2,&my_qserial::write_data);
    connect(ui->buttonBox,&QDialogButtonBox::rejected,&myserial2,&my_qserial::close_port);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,&myserial2,&my_qserial::open_port);
    connect(&myserial2,SIGNAL(close_port_sig()),this,SLOT(set_close_port_label()));
    connect(&myserial2,SIGNAL(open_port_sig()),this,SLOT(open_port_handle()));
    connect(&myserial2,SIGNAL(http_get(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(http_post(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_ModuleGetHostByName(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_ModuleGetquality(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_ModuleGetStatus(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_ModuleDisconnect(QByteArray)),this,SLOT(show_network_result(QByteArray)));

    connect(&myserial2,SIGNAL(API_COMM_Sntp_Start(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_WIFIGetAPInfo(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_WIFIGetMac(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_WIFIGetquality(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_WIFIGetStatus(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_WIFIGetVersion(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_WIFISetMac(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_WIFISetNetWork(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(API_COMM_GetLocalIp(QByteArray)),this,SLOT(show_network_result(QByteArray)));




    connect(&myserial2,SIGNAL(sha1_enc(QByteArray)),this,SLOT(show_sha_result(QByteArray)));
    connect(&myserial2,SIGNAL(hmac_sig(QByteArray)),this,SLOT(show_hmac_result(QByteArray)));
    connect(&myserial2,SIGNAL(ras_public_encrypt(QByteArray)),this,SLOT(show_rsa_result(QByteArray)));
    connect(&myserial2,SIGNAL(rsa_pri_dec(QByteArray)),this,SLOT(show_rsa_result(QByteArray)));
    connect(&myserial2,SIGNAL(rsa_pri_enc(QByteArray)),this,SLOT(show_rsa_result(QByteArray)));
    connect(&myserial2,SIGNAL(rsa_pub_dec(QByteArray)),this,SLOT(show_rsa_result(QByteArray)));
    connect(&myserial2,SIGNAL(rsa_pri_sign(QByteArray)),this,SLOT(show_rsa_result(QByteArray)));
    connect(&myserial2,SIGNAL(rsa_pub_verify(QByteArray)),this,SLOT(show_rsa_result(QByteArray)));
    connect(&myserial2,SIGNAL(ota_http_up(QByteArray)),this,SLOT(show_ota_result(QByteArray)));
    connect(&myserial2,SIGNAL(ota_trig_up(QByteArray)),this,SLOT(show_ota_result(QByteArray)));
    connect(&myserial2,SIGNAL(ota_check_sta(QByteArray)),this,SLOT(show_ota_result(QByteArray)));
    connect(&myserial2,SIGNAL(ota_end_up(QByteArray)),this,SLOT(show_ota_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_reboot_sig(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sm2_enc(QByteArray)),this,SLOT(show_sm2_result(QByteArray)));
    connect(&myserial2,SIGNAL(get_time(QByteArray)),this,SLOT(show_time_result(QByteArray)));
    connect(&myserial2,SIGNAL(get_task_tick(QByteArray)),this,SLOT(show_time_result(QByteArray)));
    connect(&myserial2,SIGNAL(task_create(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(task_delete(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(queue_create(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(queue_delete(QByteArray)),this,SLOT(show_task_result(QByteArray)));


    connect(&myserial2,SIGNAL(msg_send(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(msg_receive(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(msg_delete(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(msg_reset(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(semaphore_create(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(semaphore_take(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(semaphore_free(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(semaphore_delete(QByteArray)),this,SLOT(show_task_result(QByteArray)));
    connect(&myserial2,SIGNAL(param_int_read(QByteArray)),this,SLOT(show_param_result(QByteArray)));
    connect(&myserial2,SIGNAL(param_int_write(QByteArray)),this,SLOT(show_param_result(QByteArray)));
    connect(&myserial2,SIGNAL(param_str_read(QByteArray)),this,SLOT(show_param_result(QByteArray)));
    connect(&myserial2,SIGNAL(param_str_write(QByteArray)),this,SLOT(show_param_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_led_set(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_led_get(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_battery(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_speaker(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_libversion(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_sdkversion(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_memory_calloc(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_memory_realloc(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_memory_free(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sock_con(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(time_open(QByteArray)),this,SLOT(show_time_result(QByteArray)));
    connect(&myserial2,SIGNAL(time_delete(QByteArray)),this,SLOT(show_time_result(QByteArray)));
    connect(&myserial2,SIGNAL(time_create(QByteArray)),this,SLOT(show_time_result(QByteArray)));
    connect(&myserial2,SIGNAL(sock_send(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(sock_rec(QByteArray)),this,SLOT(show_network_result(QByteArray)));
    connect(&myserial2,SIGNAL(tts_set_speed(QByteArray)),this,SLOT(show_tts_result(QByteArray)));
    connect(&myserial2,SIGNAL(tts_set_pitch(QByteArray)),this,SLOT(show_tts_result(QByteArray)));
    connect(&myserial2,SIGNAL(tts_beep_player(QByteArray)),this,SLOT(show_tts_result(QByteArray)));
    connect(&myserial2,SIGNAL(tts_play_audio(QByteArray)),this,SLOT(show_tts_result(QByteArray)));
    connect(&myserial2,SIGNAL(tts_play_aduio_string(QByteArray)),this,SLOT(show_tts_result(QByteArray)));
    connect(&myserial2,SIGNAL(tts_check_state(QByteArray)),this,SLOT(show_tts_result(QByteArray)));
    connect(&myserial2,SIGNAL(mqtt_con(QByteArray)),this,SLOT(show_mqtt_result(QByteArray)));
    connect(&myserial2,SIGNAL(mqtt_discon(QByteArray)),this,SLOT(show_mqtt_result(QByteArray)));
    connect(&myserial2,SIGNAL(mqtt_publi(QByteArray)),this,SLOT(show_mqtt_result(QByteArray)));
    connect(&myserial2,SIGNAL(mqtt_subs(QByteArray)),this,SLOT(show_mqtt_result(QByteArray)));
    connect(&myserial2,SIGNAL(mqtt_unsubs(QByteArray)),this,SLOT(show_mqtt_result(QByteArray)));
    connect(&myserial2,SIGNAL(mqtt_close(QByteArray)),this,SLOT(show_mqtt_result(QByteArray)));
    connect(&myserial2,SIGNAL(hex_to_asc(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(asc_to_hex(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(asc_to_bcd(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(bcd_to_asc(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(gbk_to_utf(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(utf_to_gbk(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(url_encode(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(url_decode(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(hex_to_dec(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(asc_to_int(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(bcd_to_int(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(int_to_bcd(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(tlv_build(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(tlv_destory(QByteArray)),this,SLOT(show_tool_result(QByteArray)));


    connect(&myserial2,SIGNAL(BcdToUint64(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(UintToC4(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(C4ToUint(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(C2ToInt(QByteArray)),this,SLOT(show_tool_result(QByteArray)));


    connect(&myserial2,SIGNAL(CStrlcpy(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(Getrand(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(GetTimestamp(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(StrCaseCmp(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(StrRemovechar(QByteArray)),this,SLOT(show_tool_result(QByteArray)));
    connect(&myserial2,SIGNAL(param_delete_data(QByteArray)),this,SLOT(show_param_result(QByteArray)));
    connect(&myserial2,SIGNAL(time_stop(QByteArray)),this,SLOT(show_time_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_button(QByteArray)),this,SLOT(show_sys_result(QByteArray)));
    connect(&myserial2,SIGNAL(sys_btn_unreg(QByteArray)),this,SLOT(show_sys_result(QByteArray)));



}


void Form::on_buttonBox_accepted()
{
    myserial2.set_portName_bit(ui->serial_num_comboBox->currentText(),ui->rate_comboBox->currentText().toInt());

}
void Form::set_close_port_label()
{
    com_label_show->setText(ui->serial_num_comboBox->currentText()+" closed");
    ui->serial_num_comboBox->setEnabled(true);
    ui->rate_comboBox->setEnabled(true);
}
void Form::show_sha_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="sha1")
        ui->textEdit_2->append("sha1 encrypt results are:");
    else if(ui->comboBox->currentText()=="sha256")
        ui->textEdit_2->append("sha256 encrypt results are:");


    //   ui->textEdit_2->append(QString::fromLocal8Bit( data ));
    char dist[2048]={0};
    unsigned char * p = (unsigned char *)data.data();
    HexToStr(dist,p,data.length());
    ui->textEdit_2->append(QString(dist));
}
void Form::show_hmac_result(QByteArray data)
{
    if(QString(data).toUpper().left(4)=="0000")
        ui->textEdit_2->append("success\n");
    else if(QString(data).toUpper().left(4)=="1111"){
        ui->textEdit_2->append("failed\n");
        return;
    }
    if(ui->comboBox->currentText()=="hmac-sha1")
        ui->textEdit_2->append("hmac-sha1 encrypt results are:");
    else if(ui->comboBox->currentText()=="hmac-sha256")
        ui->textEdit_2->append("hmac-sha1 encrypt results are:");
    ui->textEdit_2->append(QString(data).toUpper());
}
/**获取sm2公钥加密结果
 * @brief Form::show_sm2_result
 * @param data
 */
void Form::show_sm2_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="sm2-encrypt")
        ui->textEdit_2->append("sm2 encrypt results are:");
    char dist[2048]={0};
    unsigned char * p = (unsigned char *)data.data();


    HexToStr(dist,p,data.length());
    ui->textEdit_2->append(QString(dist).right(QString(dist).length()-2));

}
void Form::show_rsa_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="rsa-public-encrypt")
        ui->textEdit_2->append("rsa public encrypt results are:");
    else if(ui->comboBox->currentText()=="rsa-private-decrypt"){
        ui->textEdit_2->append("rsa private decrypt results are:");
        ui->textEdit_2->append(data);
    }
    else if(ui->comboBox->currentText()=="rsa-private-encrypt")
        ui->textEdit_2->append("rsa private encrypt results are:");
    else if(ui->comboBox->currentText()=="rsa-public-decrypt"){
        ui->textEdit_2->append("rsa public decrypt results are:");
        ui->textEdit_2->append(data);
    }
    else if(ui->comboBox->currentText()=="rsa-private-sign")
        ui->textEdit_2->append("rsa private sign results are:");
    else if(ui->comboBox->currentText()=="rsa-public-verify")
        ui->textEdit_2->append("rsa public verify results are:");
    if(QString(data)=="1111")
        ui->textEdit_2->append("get result none");
    else if(QString(data)=="0000"){
        ui->textEdit_2->append("verify successful！");
    }
    else{
        char dist[2048]={0};
        unsigned char * p = (unsigned char *)data.data();
        HexToStr(dist,p,data.length());
        ui->textEdit_2->append(QString(dist));
    }
}
void Form::show_ota_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="ota-http-update"){
        ui->textEdit_2->append("ota http update results are:");
    }
    else if(ui->comboBox->currentText()=="ota-triggle-update"){
        ui->textEdit_2->append("ota triggle update results are:");
    }
    else if(ui->comboBox->currentText()=="ota-state-check"){
        ui->textEdit_2->append("ota state check results are:");
    }
    else if(ui->comboBox->currentText()=="ota-end-update")
    {
        ui->textEdit_2->append("ota end update results are:");
    }
    if(QString(data)=="0000")
        ui->textEdit_2->append("success");
    else if(QString(data)=="1111"){
        ui->textEdit_2->append("failed");
    }
}
void Form::show_sys_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="sys-reboot"){
        ui->textEdit_2->append("sys reboot results are:");
        if(QString(data)=="0000")
            ui->textEdit_2->append("system reboot success");
    }
    else if(ui->comboBox->currentText()=="sys-memory-calloc"){
        ui->textEdit_2->append("sys memory calloc results are:");
    }
    else if(ui->comboBox->currentText()=="sys-memory-realloc"){
        ui->textEdit_2->append("sys memory realloc results are:");

    }
    else if(ui->comboBox->currentText()=="sys-memory-free"){
        ui->textEdit_2->append("sys memory free results are:");
    }
    else if(ui->comboBox->currentText()=="sys-led-set"){
        ui->textEdit_2->append("sys-led-set results are:");
    }
    else if(ui->comboBox->currentText()=="sys-led-get"){
        ui->textEdit_2->append("sys-led-get results are:");
    }
    else if(ui->comboBox->currentText()=="sys-battery"){
        ui->textEdit_2->append("sys-battery results are:");
        ui->textEdit_2->append("电压:"+data);
    }
    else if(ui->comboBox->currentText()=="sys-speaker"){
        ui->textEdit_2->append("sys-speaker results are:");
        ui->textEdit_2->append("音量:"+data);
    }
    else if(ui->comboBox->currentText()=="sys-libversion"){
        ui->textEdit_2->append("sys-libversion results are:");
        ui->textEdit_2->append("系统版本:"+data);
    }
    else if(ui->comboBox->currentText()=="sys-sdkversion"){
        ui->textEdit_2->append("sys-sdkversion results are:");
        ui->textEdit_2->append("SDK版本:"+data);
    }
    if(QString(data)=="0000")
        ui->textEdit_2->append("success");
    else if(QString(data)=="1111"){
        ui->textEdit_2->append("failed");
    }

}
void Form::show_time_result(QByteArray data)
{

    if(ui->comboBox->currentText()=="get-sys-time"){
        ui->textEdit_2->append("get time results are:");
        ui->textEdit_2->append(data);
    }
    else if(ui->comboBox->currentText()=="set-sys-time"){
        ui->textEdit_2->append("set-sys-time results are:");
    }
    else if(ui->comboBox->currentText()=="get-task--tick"){
        ui->textEdit_2->append("get-task-tick results are:");
        ui->textEdit_2->append(data);
    }
    else if(ui->comboBox->currentText()=="time-open"){
        ui->textEdit_2->append("time-open results are:");
    }
    else if(ui->comboBox->currentText()=="time-create"){
        ui->textEdit_2->append("time-create results are:");
    }
    else if(ui->comboBox->currentText()=="time-delete"){
        ui->textEdit_2->append("time-delete results are:");
    }
    if(QString(data)=="0000")
        ui->textEdit_2->append("success");
    else if(QString(data)=="1111"){
        ui->textEdit_2->append("failed");
    }
}
void Form::show_task_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="task-create"){
        ui->textEdit_2->append("task-create results are:");
    }
    else if(ui->comboBox->currentText()=="task-delete"){
        ui->textEdit_2->append("task-delete results are:");
    }
    else if(ui->comboBox->currentText()=="queue-create"){
        ui->textEdit_2->append("queue-create results are:");
    }
    else if(ui->comboBox->currentText()=="msg-send"){
        ui->textEdit_2->append("msg-send results are:");
    }
    else if(ui->comboBox->currentText()=="msg-receive"){
        ui->textEdit_2->append("msg-receive results are:");
    }
    else if(ui->comboBox->currentText()=="msg-reset"){
        ui->textEdit_2->append("msg-reset results are:");
    }
    else if(ui->comboBox->currentText()=="msg-delete"){
        ui->textEdit_2->append("msg-delete results are:");
    }

    else if(ui->comboBox->currentText()=="semaphore-create"){
        ui->textEdit_2->append("semaphore-create results are:");
    }
    else if(ui->comboBox->currentText()=="semaphore-take"){
        ui->textEdit_2->append("semaphore-take results are:");
    }
    else if(ui->comboBox->currentText()=="semaphore-free"){
        ui->textEdit_2->append("semaphore-free results are:");
    }
    else if(ui->comboBox->currentText()=="semaphore-delete"){
        ui->textEdit_2->append("semaphore-delete results are:");
    }

    if(QString(data)=="0000")
        ui->textEdit_2->append("success");
    else if(QString(data)=="1111"){
        ui->textEdit_2->append("failed");
    }
}
void Form::show_network_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="socket-connect"){
        ui->textEdit_2->append("socket-connect results are:");
    }
    if(ui->comboBox->currentText()=="socket-send"){
        ui->textEdit_2->append("socket-send results are:");
    }
    if(ui->comboBox->currentText()=="socket-receive"){
        ui->textEdit_2->append("socket-receive results are:");
    }
    if(ui->comboBox->currentText()=="http-get"){
        ui->textEdit_2->append("http-get results are:");
    }
    if(QString(data)=="0000")
        ui->textEdit_2->append("success");
    else if(QString(data)=="1111"){
        ui->textEdit_2->append("failed");
    }
}
void Form::show_tts_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="tts-set-speed"){
        ui->textEdit_2->append("tts-set-speed results are:");
    }
    else if(ui->comboBox->currentText()=="tts-set-pitch"){
        ui->textEdit_2->append("tts-set-pitch results are:");
    }
    else if(ui->comboBox->currentText()=="tts-beep-player"){
        ui->textEdit_2->append("tts-beep-player results are:");
    }
    else if(ui->comboBox->currentText()=="tts-play-audios"){
        ui->textEdit_2->append("tts-play-audios results are:");
    }
    else if(ui->comboBox->currentText()=="tts-play-audios-string"){
        ui->textEdit_2->append("tts-play-audios-string results are:");
    }
    else if(ui->comboBox->currentText()=="tts-check-state"){
        ui->textEdit_2->append("tts-check-state results are:");
    }
    if(QString(data)=="0000")
        ui->textEdit_2->append("success");
    else if(QString(data)=="1111"){
        ui->textEdit_2->append("failed");
    }
}
void Form::show_mqtt_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="mqtt-connect"){
        ui->textEdit_2->append("mqtt-connect results are:");
    }
    else if(ui->comboBox->currentText()=="mqtt-disconnect"){
        ui->textEdit_2->append("mqtt-disconnect results are:");
    }
    else if(ui->comboBox->currentText()=="mqtt-publish"){
        ui->textEdit_2->append("mqtt-publish results are:");
    }
    else if(ui->comboBox->currentText()=="mqtt-subscribe"){
        ui->textEdit_2->append("mqtt-subscribe results are:");
    }
    else if(ui->comboBox->currentText()=="mqtt-unsubscribe"){
        ui->textEdit_2->append("mqtt-unsubscribe results are:");
    }
    else if(ui->comboBox->currentText()=="mqtt-close"){
        ui->textEdit_2->append("mqtt-close results are:");
    }
    if(QString(data)=="0000")
        ui->textEdit_2->append("success");
    else if(QString(data)=="1111"){
        ui->textEdit_2->append("failed");
    }
}
void Form::show_tool_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="hex_to_asc"){
        ui->textEdit_2->append("hex_to_asc results are:");
    }
    else if(ui->comboBox->currentText()=="asc_to_hex"){
        ui->textEdit_2->append("asc_to_hex results are:");
    }
    else if(ui->comboBox->currentText()=="asc_to_bcd"){
        ui->textEdit_2->append("asc_to_bcd results are:");
    }
    else if(ui->comboBox->currentText()=="bcd_to_hex"){
        ui->textEdit_2->append("bcd_to_hex results are:");
    }
    else if(ui->comboBox->currentText()=="gbk-to-utf"){
        ui->textEdit_2->append("gbk-to-utf results are:");
    }
    else if(ui->comboBox->currentText()=="utf-to-gbk"){
        ui->textEdit_2->append("utf-to-gbk results are:");
    }
    else if(ui->comboBox->currentText()=="url_encode"){
        ui->textEdit_2->append("url_encode results are:");
    }
    else if(ui->comboBox->currentText()=="url_decode"){
        ui->textEdit_2->append("url_decode results are:");
    }
    else if(ui->comboBox->currentText()=="hex_to_dec"){
        ui->textEdit_2->append("hex_to_deck results are:");
    }
    else if(ui->comboBox->currentText()=="asc_to_int"){
        ui->textEdit_2->append("asc_to_int results are:");
    }
    else if(ui->comboBox->currentText()=="bcd_to_int"){
        ui->textEdit_2->append("bcd_to_int results are:");
    }
    else if(ui->comboBox->currentText()=="int_to_bcd"){
        ui->textEdit_2->append("int_to_bcd results are:");
    }
    else if(ui->comboBox->currentText()=="tlv_build"){
        ui->textEdit_2->append("tlv_build results are:");
    }
    else if(ui->comboBox->currentText()=="tlv_destory"){
        ui->textEdit_2->append("tlv_destory results are:");
    }
    if(QString(data)=="0000")
        ui->textEdit_2->append("success");
    else if(QString(data)=="1111"){
        ui->textEdit_2->append("failed");
    }
}
void Form::show_param_result(QByteArray data)
{
    if(ui->comboBox->currentText()=="param-int-read"){
        ui->textEdit_2->append("param-int-read results are:");
    }
    else if(ui->comboBox->currentText()=="param-int-write"){
        ui->textEdit_2->append("param-int-write results are:");
    }
    else if(ui->comboBox->currentText()=="param-str-read"){
        ui->textEdit_2->append("param-str-read results are:");
    }
    else if(ui->comboBox->currentText()=="param-str-write"){
        ui->textEdit_2->append("param-str-write results are:");
    }
    if(QString(data)=="0000")
        ui->textEdit_2->append("success");
    else if(QString(data)=="1111"){
        ui->textEdit_2->append("failed");
    }
}
void Form::open_port_handle()
{
    if(myserial2.isopenSerial())
    {
        com_label_show->setText(ui->serial_num_comboBox->currentText()+" is open");
        ui->serial_num_comboBox->setEnabled(false);
        ui->rate_comboBox->setEnabled(false);
    }
    else
        com_label_show->setText(ui->serial_num_comboBox->currentText()+" open fail");
}
char s_data[MAX_DATA_LEN];
void Form::on_pushButton_clicked()
{
    if(!myserial2.isopenSerial()){
        com_label_show->setText(ui->serial_num_comboBox->currentText()+" init fail");
        return;
    }

    ui->textEdit_2->clear();
    if(ui->comboBox->currentText()=="hmac-sha1"){
        myserial2.set_show_slot2(hmac1);
        myserial2.setData(hmac_data());
    }
    else if(ui->comboBox->currentText()=="hmac-sha256"){
        myserial2.set_show_slot2(hmac1);
        myserial2.setData(hmac_data());
    }
    else if(ui->comboBox->currentText()=="sm2-encrypt"){
        myserial2.set_show_slot2(sm2_public_encrypt);
        myserial2.setData(sm2_data());
    }
    else if(ui->comboBox->currentText()=="sha1"||ui->comboBox->currentText()=="sha256"){

        myserial2.set_show_slot2(sha1);
        myserial2.setData(sha_data());
    }
    else if(ui->comboBox->currentText()=="rsa-public-encrypt"){
        myserial2.set_show_slot2(rsa_public_encrypt);
        myserial2.setData(rsa_data());
    }
    else if(ui->comboBox->currentText()=="time-stop")
    {
        myserial2.set_show_slot2(TIME_STOP);
        myserial2.setData(time_data());
    }
    else if(ui->comboBox->currentText()=="rsa-private-decrypt"){
        myserial2.set_show_slot2(rsa_private_decrypt);
        myserial2.setData(rsa_data());
    }
    else if(ui->comboBox->currentText()=="rsa-private-encrypt"){
        myserial2.set_show_slot2(rsa_private_encrypt);
        myserial2.setData(rsa_data());
    }
    else if(ui->comboBox->currentText()=="rsa-public-decrypt"){
        myserial2.set_show_slot2(rsa_public_decrypt);
        myserial2.setData(rsa_data());
    }
    else if(ui->comboBox->currentText()=="rsa-private-sign"){
        myserial2.set_show_slot2(rsa_private_sign);
        myserial2.setData(rsa_data());
    }
    else if(ui->comboBox->currentText()=="rsa-public-verify"){
        myserial2.set_show_slot2(rsa_public_verify);
        myserial2.setData(rsa_data());
    }
    else if(ui->comboBox->currentText()=="socket-connect"){
        myserial2.set_show_slot2(socket_connect);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="socket-send"){
        myserial2.set_show_slot2(socket_send);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="socket"){
        myserial2.set_show_slot2(socket_connect);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="socket-receive"){
        myserial2.set_show_slot2(socket_rec);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="ota-http-update"){
        myserial2.set_show_slot2(ota_http_update);
        myserial2.setData(ota_data());
    }
    else if(ui->comboBox->currentText()=="ota-triggle-update"){
        myserial2.set_show_slot2(ota_triggle_update);
        myserial2.setData(ota_data());
    }
    else if(ui->comboBox->currentText()=="ota-state-check"){
        myserial2.set_show_slot2(ota_state_check);
        myserial2.setData(ota_data());
    }
    else if(ui->comboBox->currentText()=="ota-end-update"){
        myserial2.set_show_slot2(ota_end_update);
        myserial2.setData(ota_data());
    }
    else if(ui->comboBox->currentText()=="sys-reboot"){
        myserial2.set_show_slot2(sys_reboot);
        myserial2.setData(sys_data());
    }
    else if(ui->comboBox->currentText()=="sys-memory-realloc"){
        myserial2.set_show_slot2(SYS_MEMORY_RELLOC);
        myserial2.setData(sys_data());
    }
    else if(ui->comboBox->currentText()=="sys-btn-reg")
    {
        myserial2.set_show_slot2(SYS_BUTTON);
        myserial2.setData(sys_data());
    }
    else if(ui->comboBox->currentText()=="sys-btn-unreg")
    {
        myserial2.set_show_slot2(SYS_BUTTON_UNREG);
        myserial2.setData(sys_data());
    }
    else if(ui->comboBox->currentText()=="sys-memory-calloc"){
        myserial2.set_show_slot2(SYS_MEMORY_CALLOC);
        myserial2.setData(sys_data());
    }
    else if(ui->comboBox->currentText()=="sys-memory-free"){
        myserial2.set_show_slot2(SYS_MEMORY_FREE);
        myserial2.setData(sys_data());
    }
    else if(ui->comboBox->currentText()=="sys-led-set"){
        myserial2.set_show_slot2(SYS_LED_SET);
        myserial2.setData(sys_data());
    }
    else if(ui->comboBox->currentText()=="sys-led-get"){
        myserial2.set_show_slot2(SYS_LED_GET);
        myserial2.setData(sys_data());
    }
    else if(ui->comboBox->currentText()=="sys-speaker"){
        myserial2.set_show_slot2(SYS_SPEAKER);
        myserial2.setData(sys_data());

    }
    else if(ui->comboBox->currentText()=="sys-battery"){
        myserial2.set_show_slot2(SYS_BATTERY);
        myserial2.setData(sys_data());

    }
    else if(ui->comboBox->currentText()=="sys-libversion"){
        myserial2.set_show_slot2(SYS_LIBVERSION);
        myserial2.setData(sys_data());
    }
    else if(ui->comboBox->currentText()=="sys-sdkversion"){
        myserial2.set_show_slot2(SYS_SDKVERSION);
        myserial2.setData(sys_data());
    }

    else if(ui->comboBox->currentText()=="get-sys-time"){
        myserial2.set_show_slot2(time_gets);
        myserial2.setData(time_data());
    }
    else if(ui->comboBox->currentText()=="http-get")
    {
        myserial2.set_show_slot2(HTTP_GET);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="http-post")
    {
        myserial2.set_show_slot2(HTTP_POST);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="set-sys-time"){
        myserial2.set_show_slot2(time_gets);
        myserial2.setData(time_data());
    }
    else if(ui->comboBox->currentText()=="get-task--tick"){
        myserial2.set_show_slot2(time_gets);
        myserial2.setData(time_data());
    }
    else if(ui->comboBox->currentText()=="task-create"){
        myserial2.set_show_slot2(TASK_CREATE);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="task-delete"){
        myserial2.set_show_slot2(TASK_DELETE);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="queue-create"){
        myserial2.set_show_slot2(QUEUE_CREATE);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="queue-delete"){
        myserial2.set_show_slot2(QUEUE_CREATE);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="msg-send"){
        myserial2.set_show_slot2(MSG_SEND);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="msg-receive"){
        myserial2.set_show_slot2(MSG_RECEIVE);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="msg-reset"){
        myserial2.set_show_slot2(MSG_RECEIVE);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="msg-delete"){
        myserial2.set_show_slot2(MSG_DELETE);
        myserial2.setData(task_data());
    }

    else if(ui->comboBox->currentText()=="semaphore-create"){
        myserial2.set_show_slot2(SEMAPHORE_CREATE);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="semaphore-take"){
        myserial2.set_show_slot2(SEMAPHORE_TAKE);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="semaphore-free"){
        myserial2.set_show_slot2(SEMAPHORE_FREE);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="semaphore-delete"){
        myserial2.set_show_slot2(SEMAPHORE_DELETE);
        myserial2.setData(task_data());
    }
    else if(ui->comboBox->currentText()=="param-int-read"){
        myserial2.set_show_slot2(PARAM_INT_READ);
        myserial2.setData(param_data());
    }
    else if(ui->comboBox->currentText()=="param-int-write"){
        myserial2.set_show_slot2(PARAM_INT_WRITE);
        myserial2.setData(param_data());
    }
    else if(ui->comboBox->currentText()=="param-str-read"){
        myserial2.set_show_slot2(PARAM_STR_READ);
        myserial2.setData(param_data());
    }
    else if(ui->comboBox->currentText()=="param-str-write"){
        myserial2.set_show_slot2(PARAM_STR_WRITE);
        myserial2.setData(param_data());
    }
    else if(ui->comboBox->currentText()=="time-open"){
        myserial2.set_show_slot2(TIME_OPEN);
        myserial2.setData(time_data());
    }
    else if(ui->comboBox->currentText()=="time-delete"){
        myserial2.set_show_slot2(TIME_DELETE);
        myserial2.setData(time_data());
    }
    else if(ui->comboBox->currentText()=="time-create"){
        myserial2.set_show_slot2(TIME_CREATE);
        myserial2.setData(time_data());
    }

    if(ui->comboBox->currentText()=="tts-set-speed"){
        myserial2.set_show_slot2(TTS_SET_SPEED);
        myserial2.setData(tts_data());
    }
    else if(ui->comboBox->currentText()=="tts-set-pitch"){
        myserial2.set_show_slot2(TTS_SET_PITCH);
        myserial2.setData(tts_data());
    }
    else if(ui->comboBox->currentText()=="tts-beep-player"){
        myserial2.set_show_slot2(TTS_BEEP_PLAYER);
        myserial2.setData(tts_data());
    }
    else if(ui->comboBox->currentText()=="tts-play-audios"){
        myserial2.set_show_slot2(TTS_PLAY_AUDIOS);
        myserial2.setData(tts_data());
    }
    else if(ui->comboBox->currentText()=="tts-play-audios-string"){
        myserial2.set_show_slot2(TTS_PLAY_AUDIOS_STRING);
        myserial2.setData(tts_data());
    }
    else if(ui->comboBox->currentText()=="tts-check-state"){
        myserial2.set_show_slot2(TTS_CHECK_STATE);
        myserial2.setData(tts_data());
    }
    else if(ui->comboBox->currentText()=="mqtt-connect"){
        myserial2.set_show_slot2(mqtt_connect);
        myserial2.setData(mqtt_data());
    }
    else if(ui->comboBox->currentText()=="mqtt-disconnect"){
        myserial2.set_show_slot2(mqtt_disconnect);
        myserial2.setData(mqtt_data());
    }
    else if(ui->comboBox->currentText()=="mqtt-close"){
        myserial2.set_show_slot2(MQTT_CLoSE);
        myserial2.setData(mqtt_data());
    }
    else if(ui->comboBox->currentText()=="mqtt-publish"){
        myserial2.set_show_slot2(mqtt_publish);
        myserial2.setData(mqtt_data());
    }
    else if(ui->comboBox->currentText()=="mqtt-subscribe"){
        myserial2.set_show_slot2(mqtt_subscribe);
        myserial2.setData(mqtt_data());
    }
    else if(ui->comboBox->currentText()=="mqtt-unsubscribe"){
        myserial2.set_show_slot2(mqtt_unsubscribe);
        myserial2.setData(mqtt_data());
    }
    else if(ui->comboBox->currentText()=="hex_to_asc"){
        myserial2.set_show_slot2(HEX_TO_ASC);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="asc_to_hex"){
        myserial2.set_show_slot2(ASC_TO_HEX);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="asc_to_bcd"){
        myserial2.set_show_slot2(ASC_TO_BCD);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="bcd_to_hex"){
        myserial2.set_show_slot2(BCD_TO_ASC);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="gbk-to-utf"){
        myserial2.set_show_slot2(GBK_TO_UTF);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="utf-to-gbk"){
        myserial2.set_show_slot2(UTF_TO_GBK);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="url_encode"){
        myserial2.set_show_slot2(URL_ENCODE);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="url_decode"){
        myserial2.set_show_slot2(URL_DECODE);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="hex_to_dec"){
        myserial2.set_show_slot2(HEX_TO_DEC);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="asc_to_int"){
        myserial2.set_show_slot2(ASC_TO_INT);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="bcd_to_int"){
        myserial2.set_show_slot2(BCD_TO_INT);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="int_to_bcd"){
        myserial2.set_show_slot2(INT_TO_BCD);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="tlv_build"){
        myserial2.set_show_slot2(TLV_BUILD);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="tlv_destory"){
        myserial2.set_show_slot2(TLV_DESTORY);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="BcdToUint64"){
        myserial2.set_show_slot2(BCDTOUINT64);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="C2ToInt"){
        myserial2.set_show_slot2(C2TOINT);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="UintToC4"){
        myserial2.set_show_slot2(UINTTOC4);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="C4ToUint"){
        myserial2.set_show_slot2(C4TOUINT);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="CStrlcpy"){
        myserial2.set_show_slot2(CSTRLCPY);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="Getrand"){
        myserial2.set_show_slot2(GETRAND);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="GetTimestamp"){
        myserial2.set_show_slot2(GETTIMERSTAMP);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="StrCaseCmp"){
        myserial2.set_show_slot2(STRCASECMP);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="StrRemovechar"){
        myserial2.set_show_slot2(STRREMOVECHAR);
        myserial2.setData(tool_data());
    }
    else if(ui->comboBox->currentText()=="param-delete-data"){
        myserial2.set_show_slot2(PARAM_DELETE_DATA);
        myserial2.setData(param_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_ModuleGetHostByName"){
        myserial2.set_show_slot2(MODULEGETPOSTNAME);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_ModuleGetquality"){
        myserial2.set_show_slot2(MODULEGETQUALITY);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_ModuleGetStatus"){
        myserial2.set_show_slot2(MODULEGETSTATUS);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_ModuleDisconnect"){
        myserial2.set_show_slot2(MODULEDISCONNECT);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_Sntp_Start"){
        myserial2.set_show_slot2(SNTPSTART);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFIGetAPInfo"){
        myserial2.set_show_slot2(WIFIGETAPINFO);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFIGetMac"){
        myserial2.set_show_slot2(WIFIGETMAC);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFIGetquality"){
        myserial2.set_show_slot2(WIFIGETQUALITY);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFIGetStatus"){
        myserial2.set_show_slot2(WIFIGETSTATUS);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFIGetVersion"){
        myserial2.set_show_slot2(WIFIGETVERSION);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFISetMac"){
        myserial2.set_show_slot2(WIFISETMAC);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFISetNetWork"){
        myserial2.set_show_slot2(WIFISETNETWORK);
        myserial2.setData(socket_data());
    }
    else if(ui->comboBox->currentText()=="API_COMM_GetLocalIp"){
        myserial2.set_show_slot2(GETLOCALIP);
        myserial2.setData(socket_data());
    }
}

void Form::show_serial_result()
{
    ui->textEdit_2->append(m_comBoxText+" results are:");

}
QString Form::sha_data()
{
    int a=ui->textEdit->toPlainText().length()/2;//输入数据长度
    QString s2=ui->textEdit->toPlainText();//数据内容
    if(ui->textEdit->toPlainText().length()%2){
        a=ui->textEdit->toPlainText().length()/2+1;
        s2+="0";
    }
    QString data_len=QString("%1").arg(a+2, 4, 16, QLatin1Char('0')); //数据包长度
    QString len=QString("%1").arg(a, 4, 16, QLatin1Char('0')); //数据长度
    //CRC校验
    unsigned char CRC[2]={0};
    if(ui->comboBox->currentText()=="sha1")
    {
        QString temp="000a"+data_len+len+s2;
        crc16_CCITT(CRC,(unsigned char*)temp.toStdString().c_str(),temp.length()/2,0);
        char buf1[5]={0};
        HexToStr(buf1,CRC,2);
        QString buf="02000a"+data_len+len+s2+QString(buf1);
        return buf;
    }
    else if(ui->comboBox->currentText()=="sha256")
    {
        QString temp="000B"+data_len+len+s2;
        crc16_CCITT(CRC,(unsigned char*)temp.toStdString().c_str(),temp.length()/2,0);
        char buf1[5]={0};
        HexToStr(buf1,CRC,2);
        QString buf="02000B"+data_len+len+s2+QString(buf1);
        return buf;
    }
    return "";

}
QString Form::hmac_data()
{
    QString key="17E6D95AAAFAECEA";//密钥
    int a=key.length()/2;
    QString key_len=QString("%1").arg(a, 4, 16, QLatin1Char('0')); //密钥长度
    int b=ui->textEdit->toPlainText().length()/2;
    if(ui->textEdit->toPlainText().length()%2)
        b=ui->textEdit->toPlainText().length()/2+1;
    QString data_len=QString("%1").arg(b, 4, 16, QLatin1Char('0')); //数据长度
    QString data;
    if(ui->comboBox->currentText()=="hmac-sha1")
        data="01"+key_len+key+data_len+ui->textEdit->toPlainText();
    else if(ui->comboBox->currentText()=="hmac-sha256")
        data="02"+key_len+key+data_len+ui->textEdit->toPlainText();
    //数据长度
    int c=a+b+5;
    QString datas_len=QString("%1").arg(c, 4, 16, QLatin1Char('0'));
    QString datas;
    if(ui->comboBox->currentText()=="hmac-sha1"){
        datas="020001"+datas_len+data;
        if(datas.length()%2!=0)
            datas+="0";

        //CRC校验
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)datas.right(datas.length()-2).toStdString().c_str(),(datas.length()-2)/2,0);
        char buf1[5]={0};
        HexToStr(buf1,CRC,2);
        datas=datas+QString(buf1);
    }
    else if(ui->comboBox->currentText()=="hmac-sha256")
    {
        datas="020002"+datas_len+data;
        if(datas.length()%2!=0)
            datas+="0";
        //CRC校验
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)datas.right(datas.length()-2).toStdString().c_str(),(datas.length()-2)/2,0);
        char buf1[5]={0};
        HexToStr(buf1,CRC,2);
        datas=datas+QString(buf1);
    }
    return datas;
}
QString Form::rsa_data()
{
    if(!ui->textEdit->toPlainText().length()){
        QMessageBox::information(this,"提示","数据不能为空",QMessageBox::Ok);
        return "";
    }
    int a=ui->textEdit->toPlainText().length()/2;
    QString s2=ui->textEdit->toPlainText();//数据内容
    if(ui->textEdit->toPlainText().length()%2){
        a=ui->textEdit->toPlainText().length()/2+1;
        s2+="0";
    }
    QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
    QString len=QString("%1").arg(3+a, 4, 16, QLatin1Char('0'));//数据长度
    QString buf;
    if(ui->comboBox->currentText()=="rsa-public-encrypt")
        buf="020003"+len+"01"+s3+s2;
    else if(ui->comboBox->currentText()=="rsa-private-decrypt")
        buf="020004"+len+"02"+s3+s2;
    else if(ui->comboBox->currentText()=="rsa-private-encrypt")
        buf="020005"+len+"01"+s3+s2;
    else if(ui->comboBox->currentText()=="rsa-public-decrypt")
        buf="020006"+len+"02"+s3+s2;
    else if(ui->comboBox->currentText()=="rsa-private-sign")
        buf="020007"+len+"00"+s3+s2;
    else if(ui->comboBox->currentText()=="rsa-public-verify")
        buf="020008"+len+"00"+s3+s2;

    //CRC校验
    unsigned char CRC[2]={0};
    crc16_CCITT(CRC,(unsigned char*)buf.right(buf.length()-2).toStdString().c_str(),(buf.length()-2)/2,0);
    char buf1[4]={0};
    HexToStr(buf1,CRC,2);
    buf=buf+QString(buf1);
    return buf;
}
QString Form::sm2_data()
{
    int a=ui->textEdit->toPlainText().length()/2;//输入数据长度
    QString s2=ui->textEdit->toPlainText();//数据内容
    if(ui->textEdit->toPlainText().length()%2){
        a=ui->textEdit->toPlainText().length()/2+1;
        s2+="0";
    }
    QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
    QString len=QString("%1").arg(67+a, 4, 16, QLatin1Char('0'));//数据长度
    QString key="6569C22743BC4A83D9978CF34B7A1B3D9003A73B85F793C7820F948D1531916F2ED05DF403B908E10AFE382FBD64133C4DA60366904CDA5DA1AE5794502F5793";
    QString buf="020009"+len+"40"+key+s3+s2;


    unsigned char CRC[2]={0};
    crc16_CCITT(CRC,(unsigned char*)buf.right(buf.length()-2).toStdString().c_str(),(buf.length()-2)/2,0);
    char buf1[5]={0};
    HexToStr(buf1,CRC,2);
    buf=buf+QString(buf1);

    return buf;
}
QString Form::socket_data()
{
    if(ui->comboBox->currentText()=="socket-connect")
        return "020101000000"+create_crc(QString("020101000000").mid(2,-1));
    else if(ui->comboBox->currentText()=="socket")
        return "020101000000"+create_crc(QString("020101000000").mid(2,-1));
    else if(ui->comboBox->currentText()=="socket-send"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度
        return "020102"+len+"01"+s3+s2;
    }
    else if(ui->comboBox->currentText()=="socket-receive"){
        return "020103000000"+create_crc(QString("020103000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="http-get"){
        return "020104000000"+create_crc(QString("020104000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="http-post"){
        return "020105000000"+create_crc(QString("020105000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_ModuleGetHostByName"){
        return "020106000000"+create_crc(QString("020106000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_ModuleGetquality"){
        return "020107000000"+create_crc(QString("020107000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_ModuleGetStatus"){
        return "020108000000"+create_crc(QString("020108000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_ModuleDisconnect"){
        return "020109000000"+create_crc(QString("020109000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_Sntp_Start"){
        return "02010A000000"+create_crc(QString("02010A000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFIGetAPInfo"){
        return "02010B000000"+create_crc(QString("02010B000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFIGetMac"){
        return "02010C000000"+create_crc(QString("02010C000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFIGetquality"){
        return "02010D000000"+create_crc(QString("02010D000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFIGetStatus"){
        return "02010E000000"+create_crc(QString("02010E000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFIGetVersion"){
        return "02010F000000"+create_crc(QString("02010F000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFISetMac"){
        return "020110000000"+create_crc(QString("020110000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_WIFISetNetWork"){
        return "020111000000"+create_crc(QString("020111000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="API_COMM_GetLocalIp"){
        return "020112000000"+create_crc(QString("020112000000").mid(2,-1));
    }



    return "";
}
QString Form::sys_data()
{
    if(ui->comboBox->currentText()=="sys-reboot"){
        return "020301000000"+create_crc(QString("020301000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-memory-calloc"){
        return "020302000000"+create_crc(QString("020302000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-memory-realloc"){
        return "020303000000"+create_crc(QString("020303000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-memory-free"){

        return "020304000000"+create_crc(QString("020304000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-led-set"){
        return "020307000000"+create_crc(QString("020307000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-led-get"){

        return "020308000000"+create_crc(QString("020308000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-btn-reg"){

        return "020305000000"+create_crc(QString("020305000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-btn-unreg"){

        return "020306000000"+create_crc(QString("020306000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-battery"){

        return "020309000000"+create_crc(QString("020309000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-speaker"){

        return "02030A000000"+create_crc(QString("02030A000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-libversion"){

        return "02030B000000"+create_crc(QString("02030B000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="sys-sdkversion"){

        return "02030C000000"+create_crc(QString("02030C000000").mid(2,-1));
    }
    return "";
}
QString Form::ota_data()
{
    if(ui->comboBox->currentText()=="ota-http-update"){
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)"0201000000",5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return "020201000000"+QString(buf);
    }
    else if(ui->comboBox->currentText()=="ota-triggle-update"){
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)"0202000000",5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return QString("020202000000")+QString(buf);
    }
    else if(ui->comboBox->currentText()=="ota-state-check"){
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)"0203000000",5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return "020203000000"+QString(buf);
    }
    else if(ui->comboBox->currentText()=="ota-end-update")
    {
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)"0204000000",5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return "020204000000"+QString(buf);
    }
    return "";
}
QString Form::mqtt_data()
{
    if(ui->comboBox->currentText()=="mqtt-connect"){
        return "020401000000"+create_crc(QString("020401000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="mqtt-disconnect"){
        return "020402000000"+create_crc(QString("020402000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="mqtt-publish"){
        return "020403000000"+create_crc(QString("020403000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="mqtt-subscribe"){
        return "020404000000"+create_crc(QString("020404000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="mqtt-unsubscribe"){
        return "020405000000"+create_crc(QString("020405000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="mqtt-close"){
        return "020406000000"+create_crc(QString("020406000000").mid(2,-1));
    }
    return "";
}
QString Form::time_data()
{
    if(ui->comboBox->currentText()=="get-sys-time"){
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)"0702000000",5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return "020702000000"+QString(buf);
    }
    else if(ui->comboBox->currentText()=="set-sys-time"){

        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
        //QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
        QString str = time.toString("yyyyMMddhhmmss"); //设置显示格式
        qDebug()<<str;
        int a=str.length()/2;

        QString data_len=QString("%1").arg(a, 4, 16, QLatin1Char('0')); //数据包长度
        unsigned char CRC[2]={0};
        QString tp="020701"+data_len+str;
        crc16_CCITT(CRC,(unsigned char*)tp.toStdString().c_str(),5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return "020701"+data_len+str+QString(buf);
    }
    else if(ui->comboBox->currentText()=="get-task--tick"){
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)"0703000000",5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return "020703000000"+QString(buf);
    }
    else if(ui->comboBox->currentText()=="time-create"){
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)"0705000000",5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return "020705000000"+QString(buf);
    }
    else if(ui->comboBox->currentText()=="time-open"){
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)"0704000000",5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return "020704000000"+QString(buf);
    }
    else if(ui->comboBox->currentText()=="time-delete"){
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)"0706000000",5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return "020706000000"+QString(buf);
    }
    else if(ui->comboBox->currentText()=="time-stop"){
        unsigned char CRC[2]={0};
        crc16_CCITT(CRC,(unsigned char*)"0707000000",5,0);
        char buf[5]={0};
        HexToStr(buf,CRC,2);
        return "020707000000"+QString(buf);
    }
    return "";
}
QString Form::task_data()
{
    if(ui->comboBox->currentText()=="task-create"){
        return "020501000000"+create_crc(QString("020501000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="task-delete"){
        return "020502000000"+create_crc(QString("020502000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="queue-create"){
        return "020503000000"+create_crc(QString("020503000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="queue-delete"){
        return "020507000000"+create_crc(QString("020507000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="msg-send"){
        return "020504000000"+create_crc(QString("020504000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="msg-receive"){
        return "020505000000"+create_crc(QString("020505000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="msg-reset"){
        return "020506000000"+create_crc(QString("020506000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="semaphore-create"){
        return "020508000000"+create_crc(QString("020508000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="semaphore-take"){
        return "020509000000"+create_crc(QString("020509000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="semaphore-free"){
        return "02050A000000"+create_crc(QString("02050A000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="semaphore-delete"){
        return "02050B000000"+create_crc(QString("02050B000000").mid(2,-1));
    }
    return "";
}
QString Form::param_data()
{
    if(ui->comboBox->currentText()=="param-int-read"){
        return "020601000000"+create_crc(QString("020601000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="param-int-write"){
        return "020602000000"+create_crc(QString("020602000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="param-str-read"){
        return "020603000000"+create_crc(QString("020603000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="param-str-write"){
        return "020604000000"+create_crc(QString("020604000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="param-delete-data"){
        return "020605000000"+create_crc(QString("020605000000").mid(2,-1));
    }
    return "";
}
QString Form::tts_data()
{
    if(ui->comboBox->currentText()=="tts-set-speed"){
        return "020801000000"+create_crc(QString("020801000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="tts-set-pitch"){
        return "020802000000"+create_crc(QString("020802000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="tts-beep-player"){
        return "020803000000"+create_crc(QString("020803000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="tts-play-audios"){
        return "020804000000"+create_crc(QString("020804000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="tts-play-audios-string"){
        return "020805000000"+create_crc(QString("020805000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="tts-check-state"){
        return "020806000000"+create_crc(QString("020806000000").mid(2,-1));
    }
    return "";

}
QString Form::tool_data()
{
    if(ui->comboBox->currentText()=="tlv_build"){
        return "02090D000000"+create_crc(QString("02090D000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="tlv_destory"){
        return "02090E000000"+create_crc(QString("02090E000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="BcdToUint64"){
        return "02090F000000"+create_crc(QString("02090F000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="UintToC4"){
        return "020910000000"+create_crc(QString("020910000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="C4ToUint"){
        return "020911000000"+create_crc(QString("020911000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="CStrlcpy"){
        return "020912000000"+create_crc(QString("020912000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="Getrand"){
        return "020913000000"+create_crc(QString("020913000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="GetTimestamp"){
        return "020914000000"+create_crc(QString("020914000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="StrCaseCmp"){
        return "020915000000"+create_crc(QString("020915000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="StrRemovechar"){
        return "020916000000"+create_crc(QString("020916000000").mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="C2ToInt"){
        return "020917000000"+create_crc(QString("020917000000").mid(2,-1));
    }

    if(!ui->textEdit->toPlainText().length()){
        QMessageBox::information(this,"提示","数据不能为空",QMessageBox::Ok);
        return "";
    }
    if(ui->comboBox->currentText()=="hex_to_asc"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度

        QString t="020901"+len+s3+s2;
        return "020901"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="asc_to_hex"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度

        QString t="020902"+len+s3+s2;
        return "020902"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="asc_to_bcd"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度
        QString t="020903"+len+s3+s2;
        return "020903"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="bcd_to_hex"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度
        QString t="020904"+len+s3+s2;
        return "020904"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="gbk-to-utf"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度

        QString t="020905"+len+s3+s2;
        return "020905"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="utf-to-gbk"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度

        QString t="020906"+len+s3+s2;
        return "020906"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="url_encode"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度

        QString t="020907"+len+s3+s2;
        return "020907"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="url_decode"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度
        QString t="020908"+len+s3+s2;
        return "020908"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="hex_to_dec"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度
        QString t="020909"+len+s3+s2;
        return "020909"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="asc_to_int"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度
        QString t="02090A"+len+s3+s2;
        return "02090A"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="bcd_to_int"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度
        QString t="02090B"+len+s3+s2;
        return "02090B"+len+s3+s2+create_crc(t.mid(2,-1));
    }
    else if(ui->comboBox->currentText()=="int_to_bcd"){
        int a=ui->textEdit->toPlainText().length()/2;
        QString s2=ui->textEdit->toPlainText();//数据内容
        if(ui->textEdit->toPlainText().length()%2){
            a=ui->textEdit->toPlainText().length()/2+1;
            s2+="0";
        }
        QString s3=QString("%1").arg(a, 4, 16, QLatin1Char('0'));
        QString len=QString("%1").arg(2+a, 4, 16, QLatin1Char('0'));//数据长度
        QString t="02090C"+len+s3+s2;
        return "02090C"+len+s3+s2+create_crc(t.mid(2,-1));
    }

    return "";
}
QString create_crc(QString s1)
{
    unsigned char CRC[2]={0};
    crc16_CCITT(CRC,(unsigned char*)s1.toStdString().c_str(),5,0);
    char buf[5]={0};
    HexToStr(buf,CRC,2);
    return QString(buf);
}

void Form::on_comboBox_currentTextChanged(const QString &arg1)
{
    m_comBoxText=arg1;
    qDebug()<<m_comBoxText;
}
