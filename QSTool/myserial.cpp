#include "myserial.h"

my_qserial::my_qserial(QObject *parent) : QObject(parent)
{
    will_show=no_slots;
    port=NULL;
    isOpenSucc=false;
}

my_qserial::~my_qserial()
{
    if(port)
        delete port;
}
void my_qserial::start(QString portname,int baud)
{
    my_thread = new QThread();
    show_func_id();
    //show_slots_id();
    port = new QSerialPort();
    init_port(portname,baud);
    this->moveToThread(my_thread);
    port->moveToThread(my_thread);
    my_thread->start();//开启多线程

}
bool my_qserial::isopenSerial()
{
    return isOpenSucc;
}
void my_qserial::setData(QString data)
{
    m_data=data;
}
void my_qserial::show_func_id()
{
    qDebug() << "func_id is:" << QThread::currentThreadId();
}
void my_qserial::show_slots_id()
{
    qDebug() << "slots_id is:" << QThread::currentThreadId();
    show_func_id();
}
void my_qserial::init_port(QString portname,int baud)
{
    port->setPortName(portname);
    port->setBaudRate(baud);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    if(port->open(QIODevice::ReadWrite))
    {
        isOpenSucc=true;
        emit open_port_sig();
    }else
        qDebug() << "open it failed";
    connect(this->port,SIGNAL(readyRead()),this,SLOT(handle_data2()),Qt::DirectConnection);//接收串口数据
    //直接连接的大概意思是：信号一旦发射，槽立即执行，并且槽是在信号发射的线程中执行的。
}
void my_qserial::set_show_slot(show_slots b)
{
    will_show=b;
}
void my_qserial::set_show_slot2(show_slots b)
{
    will_show=b;
}
void my_qserial::close_port()
{
    if(isopenSerial()){
        port->close();
        emit close_port_sig();
        isOpenSucc=false;
    }
}
void my_qserial::open_port()
{
    if(isopenSerial())
        return;
    start(m_name,m_bit);
}
void my_qserial::setFunction(thread_fun a)
{
    do_work=a;

}
void my_qserial::set_portName_bit(QString name, int bit)
{
    m_name=name;
    m_bit=bit;
}

void my_qserial::handle_data()
{
    QByteArray data = port->readAll();
    qDebug() << "data received:" << data;
    // ui->plainTextEdit->insertPlainText(QString(array.toHex(' ').toUpper().append(' ')));
    // ui->plainTextEdit->insertPlainText(QString(array));
    //    qDebug() << "handling thread is:" << QThread::currentThreadId();
    switch (will_show) {
    case rsa_key:
        emit show_rsa_key(QString(data.toHex(' ').toUpper().append(' ')));
        break;
    case rsa_public_encrypt:
        emit ras_public_encrypt(data);
        break;
    case rsa_private_decrypt:
        emit rsa_pri_dec(data);
        break;
    case rsa_private_encrypt:
        emit rsa_pri_enc(data);
        break;
    case rsa_public_decrypt:
        emit rsa_pub_dec(data);
        break;
    case rsa_private_sign:
        emit rsa_pri_sign(data);
        break;
    case rsa_public_verify:
        emit rsa_pub_verify(data);
        break;
    case sm2_public_encrypt:
        emit sm2_enc(data);
        break;
    case sha1_encrypt:
        emit sha1_enc(data);
        break;
    case sha256_encrypt:
        emit sha256_enc(data);
        break;
    case socket_connect:
        emit sock_con(data);
        break;
    case socket_send:
        emit sock_send(data);
        break;
    case socket_rec:
        emit sock_rec(data);
        break;
    case ota_http_update:
        emit ota_http_up(data);
        break;
    case ota_triggle_update:
        emit ota_trig_up(data);
        break;
    case ota_state_check:
        emit ota_check_sta(data);
        break;
    case ota_end_update:
        emit ota_end_up(data);
        break;
    case time_gets:
        emit get_time(data);
        break;
    case TLV_BUILD:
        emit tlv_build(data);
        break;
    default:
        break;
    }

}
void my_qserial::handle_data2()
{
    QByteArray data ;
    data.clear();
    while (port->bytesAvailable()) {

        data.append(port->readAll());
    }
//    if(port->waitForReadyRead(220)){
//        qDebug()<<"waitForReadyRead Error";
//    }
    qDebug() <<data.length()<< "data received:" << data;
    switch (will_show) {
    case QUEUE_DELETE:
        emit queue_delete(data);
        break;
    case SNTPSTART:
        emit API_COMM_Sntp_Start(data);
        break;
    case WIFIGETAPINFO:
        emit API_COMM_WIFIGetAPInfo(data);
        break;
    case WIFIGETMAC:
        emit API_COMM_WIFIGetMac(data);
        break;
    case WIFIGETQUALITY:
        emit API_COMM_WIFIGetquality(data);
        break;
    case WIFIGETSTATUS:
        emit API_COMM_WIFIGetStatus(data);
        break;
    case WIFIGETVERSION:
        emit API_COMM_WIFIGetVersion(data);
        break;
    case WIFISETMAC:
        emit API_COMM_WIFISetMac(data);
        break;
    case GETLOCALIP:
        emit API_COMM_GetLocalIp(data);
        break;
    case WIFISETNETWORK:
        emit API_COMM_WIFISetNetWork(data);
        break;
    case MODULEGETPOSTNAME:
        emit API_COMM_ModuleGetHostByName(data);
        break;
    case MODULEGETQUALITY:
        emit API_COMM_ModuleGetquality(data);
        break;
    case MODULEDISCONNECT:
        emit API_COMM_ModuleDisconnect(data);
        break;
    case MODULEGETSTATUS:
        emit API_COMM_ModuleGetStatus(data);
        break;
    case HTTP_GET:
        emit http_get(data);
        break;
    case HTTP_POST:
        emit http_post(data);
        break;
    case sha1:
        emit sha1_enc(data);
        break;
    case sha256:
        emit sha256_enc(data);
        break;
    case hmac1:
        emit hmac_sig(data);
        break;
    case ota_http_update:
        emit ota_http_up(data);
        break;
    case ota_triggle_update:
        emit ota_trig_up(data);
        break;
    case ota_state_check:
        emit ota_check_sta(data);
        break;
    case ota_end_update:
        emit ota_end_up(data);
        break;
    case sm2_public_encrypt:
        emit sm2_enc(data);
        break;
    case rsa_public_encrypt:
        emit ras_public_encrypt(data);
        break;
    case rsa_private_decrypt:
        emit rsa_pri_dec(data);
        break;
    case rsa_private_encrypt:
        emit rsa_pri_enc(data);
        break;
    case rsa_public_decrypt:
        emit rsa_pub_dec(data);
        break;
    case rsa_private_sign:
        emit rsa_pri_sign(data);
        break;
    case rsa_public_verify:
        emit rsa_pub_verify(data);
        break;
    case time_gets:
        emit get_time(data);
        break;
    case GET_TASK_TICK:
        emit get_task_tick(data);
        break;
    case TIME_CREATE:
        emit time_create(data);
        break;
    case TIME_OPEN:
        emit time_open(data);
        break;
    case TIME_DELETE:
        emit time_delete(data);
        break;
    case TASK_CREATE:
        emit task_create(data);
        break;
    case TASK_DELETE:
        emit task_delete(data);
        break;
    case QUEUE_CREATE:
        emit queue_create(data);
        break;
    case MSG_SEND:
        emit msg_send(data);
        break;
    case MSG_RECEIVE:
        emit msg_receive(data);
        break;
    case MSG_DELETE:
        emit msg_delete(data);
        break;
    case MSG_RESET:
        emit msg_reset(data);
        break;
    case SEMAPHORE_CREATE:
        emit semaphore_create(data);
        break;
    case SEMAPHORE_TAKE:
        emit semaphore_take(data);
        break;
    case SEMAPHORE_FREE:
        emit semaphore_free(data);
        break;
    case SEMAPHORE_DELETE:
        emit semaphore_delete(data);
        break;
    case PARAM_INT_READ:
        emit param_int_read(data);
        break;
    case PARAM_INT_WRITE:
        emit param_int_write(data);
        break;
    case PARAM_STR_READ:
        emit param_str_read(data);
        break;
    case PARAM_STR_WRITE:
        emit param_str_write(data);
        break;
    case SYS_LED_SET:
        emit sys_led_set(data);
        break;
    case SYS_LED_GET:
        emit sys_led_get(data);
        break;
    case SYS_BATTERY:
        emit sys_battery(data);
        break;
    case SYS_SPEAKER:
        emit sys_speaker(data);
        break;
    case SYS_LIBVERSION:
        emit sys_libversion(data);
        break;
    case SYS_SDKVERSION:
        emit sys_sdkversion(data);
        break;
    case SYS_MEMORY_RELLOC:
        emit sys_memory_realloc(data);
        break;
    case SYS_MEMORY_CALLOC:
        emit sys_memory_calloc(data);
        break;
    case SYS_MEMORY_FREE:
        emit sys_memory_free(data);
        break;
    case socket_connect:
        emit sock_con(data);
        break;
    case socket_send:
        emit sock_send(data);
        break;
    case socket_rec:
        emit sock_rec(data);
        break;
    case TTS_SET_SPEED:
        emit tts_set_speed(data);
        break;
    case TTS_SET_PITCH:
        emit tts_set_pitch(data);
        break;
    case TTS_BEEP_PLAYER:
        emit tts_beep_player(data);
        break;
    case TTS_PLAY_AUDIOS:
        emit tts_play_audio(data);
        break;
    case TTS_PLAY_AUDIOS_STRING:
        emit tts_play_aduio_string(data);
        break;
    case TTS_CHECK_STATE:
        emit tts_check_state(data);
        break;
    case mqtt_connect:
        emit mqtt_con(data);
        break;
    case mqtt_disconnect:
        emit mqtt_discon(data);
        break;
    case mqtt_publish:
        emit mqtt_publi(data);
        break;
    case mqtt_subscribe:
        emit mqtt_subs(data);
        break;
    case mqtt_unsubscribe:
        emit mqtt_unsubs(data);
        break;
    case MQTT_CLoSE:
        emit mqtt_close(data);
        break;
    case HEX_TO_ASC:
        emit hex_to_asc(data);
        break;
    case ASC_TO_HEX:
        emit asc_to_hex(data);
        break;
    case ASC_TO_BCD:
        emit asc_to_bcd(data);
        break;
    case BCD_TO_ASC:
        emit asc_to_hex(data);
        break;
    case GBK_TO_UTF:
        emit gbk_to_utf(data);
        break;
    case UTF_TO_GBK:
        emit utf_to_gbk(data);
        break;
    case URL_ENCODE:
        emit url_encode(data);
        break;
    case URL_DECODE:
        emit url_decode(data);
        break;
    case HEX_TO_DEC:
        emit hex_to_dec(data);
        break;
    case ASC_TO_INT:
        emit asc_to_int(data);
        break;
    case BCD_TO_INT:
        emit bcd_to_int(data);
        break;
    case INT_TO_BCD:
        emit int_to_bcd(data);
        break;
    case TLV_BUILD:
        emit tlv_build(data);
        break;
    case TLV_DESTORY:
        emit tlv_destory(data);
        break;
    case BCDTOUINT64:
        emit BcdToUint64(data);
        break;
    case UINTTOC4:
        emit UintToC4(data);
        break;
    case C2TOINT:
        emit C2ToInt(data);
        break;
    case C4TOUINT:
        emit C4ToUint(data);
        break;
    case CSTRLCPY:
        emit CStrlcpy(data);
        break;
    case GETRAND:
        emit Getrand(data);
        break;
    case GETTIMERSTAMP:
        emit GetTimestamp(data);
        break;
    case STRCASECMP:
        emit StrCaseCmp(data);
        break;
    case STRREMOVECHAR:
        emit StrRemovechar(data);
        break;
    case PARAM_DELETE_DATA:
        emit param_delete_data(data);
        break;
    case TIME_STOP:
        emit time_stop(data);
        break;
    case SYS_BUTTON:
        emit sys_button(data);
        break;
    case SYS_BUTTON_UNREG:
        emit sys_btn_unreg(data);
        break;
    default:
        break;
    }

}

/**串口发送数据（可实现多次发送）
 * @brief my_qserial::write_data
 */
void my_qserial::write_data()
{

    qDebug()<<m_data;
  //  qDebug()<<m_data.length()<<"---------------";
    //    qDebug() << "write_id is:" << QThread::currentThreadId();
    if(port==NULL){
        qDebug()<<"Init com error";
        emit initcomfail();
        return;
    }
    //    port->write("data",4);
    port->write(QByteArray::fromHex(m_data.toLatin1()));//向串口写入数据（直接发送十六进制数据）
    if(!port->waitForBytesWritten()) //增加一句waitForBytesWritten()
    {
     qDebug() << "waitForBytesWritten Error" ;
    }
    QThread::msleep(200);
//    port->write(QByteArray::fromHex(m_data.toLatin1()));//向串口写入数据（直接发送十六进制数据）
//    if(!port->waitForBytesWritten()) //增加一句waitForBytesWritten()
//    {
//     qDebug() << "waitForBytesWritten Error" ;
//    }
    m_data.clear();

}
