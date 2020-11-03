#include "mainwindow.h"
#include "ui_mainwindow.h"



QList<QSerialPortInfo> serial_list;


HANDLE gComHandle;

my_qserial myserial;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial_list = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &info, serial_list) {
        ui->serial_num_comboBox->addItem(info.portName());
    }

    for(QList<QSerialPortInfo>::iterator it=serial_list.begin();it!=serial_list.end();++it)
    {
        if(it->portName()=="COM11")
        {
            ui->serial_num_comboBox->setCurrentText("COM11");
            break;
        }

    }

    com_label_show=new QLabel(this);
    com_label_show->resize(300,30);
    com_label_show->move(700,620);
    InitConnect();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitConnect()
{
    connect(ui->pushButton_7,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_2,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_3,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_4,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_5,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_6,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_9,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_11,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_12,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_13,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_14,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(ui->pushButton_22,&QPushButton::clicked,&myserial,&my_qserial::write_data);
    connect(&myserial,SIGNAL(show_rsa_key(QString)),this,SLOT(show_rsa_key(QString)));
    connect(&myserial,SIGNAL(initcomfail()),this,SLOT(show_init_fail_com()));
    connect(&myserial,SIGNAL(ras_public_encrypt(QByteArray)),this,SLOT(show_rsa_pub_encrypt(QByteArray)));
    connect(&myserial,SIGNAL(rsa_pri_dec(QByteArray)),this,SLOT(show_rsa_pri_decrypt(QByteArray)));
    connect(&myserial,SIGNAL(rsa_pri_enc(QByteArray)),this,SLOT(show_rsa_pri_encrypt(QByteArray)));
    connect(&myserial,SIGNAL(rsa_pub_dec(QByteArray)),this,SLOT(show_rsa_pub_decrypt(QByteArray)));
    connect(&myserial,SIGNAL(rsa_pri_sign(QByteArray)),this,SLOT(show_rsa_pri_sign(QByteArray)));
    connect(&myserial,SIGNAL(rsa_pub_verify(QByteArray)),this,SLOT(show_rsa_pub_verify(QByteArray)));
    connect(ui->buttonBox,&QDialogButtonBox::rejected,&myserial,&my_qserial::close_port);
    connect(&myserial,SIGNAL(close_port_sig()),this,SLOT(set_close_port_label()));
    connect(&myserial,SIGNAL(open_port_sig()),this,SLOT(open_port_handle()));
    connect(&myserial,SIGNAL(sm2_enc(QByteArray)),this,SLOT(show_sm2_encrypt()));
    connect(&myserial,SIGNAL(sha1_enc(QByteArray)),this,SLOT(show_sha1_encrypt(QByteArray)));
    connect(&myserial,SIGNAL(sha256_enc(QByteArray)),this,SLOT(show_sha256_encrypt(QByteArray)));
    connect(&myserial,SIGNAL(sock_con(QByteArray)),this,SLOT(show_socket_connect(QByteArray)));
    connect(&myserial,SIGNAL(sock_rec(QByteArray)),this,SLOT(show_socket_rec(QByteArray)));
    connect(&myserial,SIGNAL(sock_send(QByteArray)),this,SLOT(show_socket_send(QByteArray)));
    connect(&myserial,SIGNAL(ota_http_up(QByteArray)),this,SLOT(show_ota_http(QByteArray)));
    connect(&myserial,SIGNAL(ota_trig_up(QByteArray)),this,SLOT(show_ota_trig_up(QByteArray)));
    connect(&myserial,SIGNAL(ota_check_sta(QByteArray)),this,SLOT(show_ota_check_state(QByteArray)));
    connect(&myserial,SIGNAL(sys_signal(QByteArray)),this,SLOT(show_sys_handle(QByteArray)));
    connect(&myserial,SIGNAL(ota_end_up(QByteArray)),this,SLOT(show_ota_end_update(QByteArray)));


}

void MainWindow::on_buttonBox_accepted()
{
    myserial.start(ui->serial_num_comboBox->currentText(),ui->rate_comboBox->currentText().toInt());
    if(myserial.isopenSerial())
        com_label_show->setText(ui->serial_num_comboBox->currentText()+" is open");
    else
        com_label_show->setText(ui->serial_num_comboBox->currentText()+" open fail");
}

void MainWindow::on_buttonBox_rejected()
{

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->textEdit_12->clear();
    ui->textEdit->clear();
    myserial.set_show_slot(rsa_key);
    myserial.setData("");
}

void MainWindow::set_close_port_label()
{
    com_label_show->setText(ui->serial_num_comboBox->currentText()+" closed");
    ui->serial_num_comboBox->setEnabled(true);
    ui->rate_comboBox->setEnabled(true);
}

void MainWindow::open_port_handle()
{
    ui->serial_num_comboBox->setEnabled(false);
    ui->rate_comboBox->setEnabled(false);
}

void MainWindow::show_rsa_key(QString data)
{

    ui->textEdit_12->append("rsa private keys are:");
    ui->textEdit_12->append(data);
    ui->textEdit->append("rsa public keys are:");
    ui->textEdit->append(data);
}

void MainWindow::show_rsa_pub_encrypt(QByteArray data)
{
    ui->textEdit_3->append("rsa public encrypt results are:");
    if(data=="02")
    {
        ui->textEdit_3->append(QString(data));
    }
    else{
        ui->textEdit_3->append("None");
    }
}

void MainWindow::show_rsa_pri_decrypt(QByteArray data)
{

    ui->textEdit_3->append("rsa private decrypt results are:");
    if(data=="05")
    {
        ui->textEdit_3->append(QString(data));
    }else{
        ui->textEdit_3->append("None");
    }
}

void MainWindow::show_rsa_pri_encrypt(QByteArray data)
{

    ui->textEdit_3->append("rsa private encrypt results are:");
    if(data=="03")
    {
        ui->textEdit_3->append(QString(data));
    }else{
        ui->textEdit_3->append("None");
    }
}

void MainWindow::show_rsa_pub_decrypt(QByteArray data)
{
    ui->textEdit_3->append("rsa public decrypt results are:");
    if(data=="04")
    {
        ui->textEdit_3->append(QString(data));
    }else{
        ui->textEdit_3->append("None");
    }
}

void MainWindow::show_rsa_pri_sign(QByteArray data)
{
    ui->textEdit_3->append("rsa private sign results are:");
    if(data=="07")
    {
        ui->textEdit_3->append(QString(data));
    }else{
        ui->textEdit_3->append("None");
    }
}

void MainWindow::show_rsa_pub_verify(QByteArray data)
{
    ui->textEdit_3->append("rsa public verify results are:");
    if(data=="06")
    {
        ui->textEdit_3->append(QString(data));
    }else{
        ui->textEdit_3->append("None");
    }
}

/**获取sm2公钥加密结果
 * @brief MainWindow::show_sm2_encrypt
 * @param data
 */
void MainWindow::show_sm2_encrypt(QByteArray data)
{
    ui->textEdit_8->append("sm2 public encrypt results are:");
    if(data=="08")
    {
        ui->textEdit_8->append(QString(data));
    }else{
        ui->textEdit_8->append("None");
    }
}

void MainWindow::show_sha1_encrypt(QByteArray data)
{
    ui->textEdit_11->append("sha1 public encrypt results are:");
    if(data=="09")
    {
        ui->textEdit_11->append(QString(data));
    }
    else{

        ui->textEdit_11->append("None");
    }
}

void MainWindow::show_sha256_encrypt(QByteArray data)
{
    ui->textEdit_11->append("sha256 public encrypt results are:");
    if(data=="0A"){
        ui->textEdit_11->append(QString(data));
    }else{

        ui->textEdit_11->append("None");
    }
}

void MainWindow::show_socket_connect(QByteArray data)
{
    ui->textEdit_13->append("socket connect results are:");
    if(data=="0B"){
        ui->textEdit_13->append(QString(data));
    }else{

        ui->textEdit_13->append("None");
    }
}

void MainWindow::show_socket_send(QByteArray data)
{
    ui->textEdit_13->append("socket send results are:");
    if(data=="0C"){
        ui->textEdit_13->append(QString(data));
    }else{

        ui->textEdit_13->append("None");
    }
}

void MainWindow::show_socket_rec(QByteArray data)
{
    ui->textEdit_13->append("socket rec results are:");
    if(data=="0D"){
        ui->textEdit_13->append(QString(data));
    }else{

        ui->textEdit_13->append("None");
    }
}

void MainWindow::show_ota_http(QByteArray data)
{
    ui->textEdit_14->append("ota http update results are:");
    if(data=="0E"){
        ui->textEdit_14->append(QString(data));
    }else{

        ui->textEdit_14->append("None");
    }
}

void MainWindow::show_ota_trig_up(QByteArray data)
{
    ui->textEdit_14->append("ota triggle update results are:");
    if(data=="0F"){
        ui->textEdit_14->append(QString(data));
    }else{

        ui->textEdit_14->append("None");
    }
}

void MainWindow::show_ota_check_state(QByteArray data)
{
    ui->textEdit_14->append("ota check state results are:");
    if(data=="10"){
        ui->textEdit_14->append(QString(data));
    }else{

        ui->textEdit_14->append("None");
    }
}

void MainWindow::show_ota_end_update(QByteArray data)
{
    ui->textEdit_14->append("ota end update results are:");
    if(data=="11"){
        ui->textEdit_14->append(QString(data));
    }else{

        ui->textEdit_14->append("None");
    }
}
void MainWindow::show_sys_handle(QByteArray data)
{
}

void MainWindow::show_init_fail_com()
{
    com_label_show->setText("com open fail");
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->textEdit->toPlainText().length()==0){
        QMessageBox::information(this,"提示","公钥数据不能为空",QMessageBox::Ok);
        return;
    }
    if(ui->textEdit_2->toPlainText().length()==0){
        QMessageBox::information(this,"提示","数据不能为空",QMessageBox::Ok);
        return;
    }
    if(!isOpenCom()){
        QMessageBox::information(this,"提示","请先打开串口!",QMessageBox::Ok);
        return;
    }
    ui->textEdit_3->clear();
    //    myserial.setData(ui->textEdit_2->toPlainText());
    myserial.set_show_slot(rsa_public_encrypt);
    myserial.setData("02");

}

bool MainWindow::isOpenCom()
{
    return myserial.isopenSerial();

}
/**私钥解密
 * @brief MainWindow::on_pushButton_2_clicked
 */
void MainWindow::on_pushButton_2_clicked()
{
    if(ui->textEdit_12->toPlainText().length()==0){
        QMessageBox::information(this,"提示","私钥数据不能为空",QMessageBox::Ok);
        return;
    }
    if(ui->textEdit_2->toPlainText().length()==0){
        QMessageBox::information(this,"提示","数据不能为空",QMessageBox::Ok);
        return;
    }
    if(!isOpenCom()){
        QMessageBox::information(this,"提示","请先打开串口!",QMessageBox::Ok);
        return;
    }
    ui->textEdit_3->clear();
    myserial.set_show_slot(rsa_private_decrypt);
    myserial.setData("05");
}



/**私钥加密
 * @brief MainWindow::on_pushButton_3_clicked
 */
void MainWindow::on_pushButton_3_clicked()
{
    if(ui->textEdit_12->toPlainText().length()==0){
        QMessageBox::information(this,"提示","私钥数据不能为空",QMessageBox::Ok);
        return;
    }
    if(ui->textEdit_2->toPlainText().length()==0){
        QMessageBox::information(this,"提示","数据不能为空",QMessageBox::Ok);
        return;
    }
    if(!isOpenCom()){
        QMessageBox::information(this,"提示","请先打开串口!",QMessageBox::Ok);
        return;
    }
    ui->textEdit_3->clear();
    myserial.set_show_slot(rsa_private_encrypt);
    myserial.setData("03");
}
/**公钥解密
 * @brief MainWindow::on_pushButton_4_clicked
 */
void MainWindow::on_pushButton_4_clicked()
{
    if(ui->textEdit->toPlainText().length()==0){
        QMessageBox::information(this,"提示","公钥数据不能为空",QMessageBox::Ok);
        return;
    }
    if(ui->textEdit_2->toPlainText().length()==0){
        QMessageBox::information(this,"提示","数据不能为空",QMessageBox::Ok);
        return;
    }
    if(!isOpenCom()){
        QMessageBox::information(this,"提示","请先打开串口!",QMessageBox::Ok);
        return;
    }
    ui->textEdit_3->clear();
    myserial.set_show_slot(rsa_public_decrypt);
    myserial.setData("04");
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->textEdit_8->clear();
    myserial.set_show_slot(sm2_public_encrypt);
    myserial.setData("08");
}
/**私钥签名
 * @brief MainWindow::on_pushButton_5_clicked
 */
void MainWindow::on_pushButton_5_clicked()
{
    ui->textEdit_3->clear();
    myserial.set_show_slot(rsa_private_sign);
    myserial.setData("07");
}
/**公钥验签
 * @brief MainWindow::on_pushButton_6_clicked
 */
void MainWindow::on_pushButton_6_clicked()
{
    ui->textEdit_3->clear();
    myserial.set_show_slot(rsa_public_verify);
    myserial.setData("06");
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->textEdit_11->clear();
    myserial.set_show_slot(sha1_encrypt);
    if(ui->comboBox_4->currentText()=="SHA-1")
        myserial.setData("09");
    else
        myserial.setData("0A");
}
/**网络连接
 * @brief MainWindow::on_pushButton_12_clicked
 */
void MainWindow::on_pushButton_12_clicked()
{
    ui->textEdit_13->clear();
    myserial.set_show_slot(socket_connect);
    myserial.setData("0B");
}
/**socket发送
 * @brief MainWindow::on_pushButton_13_clicked
 */
void MainWindow::on_pushButton_13_clicked()
{
    ui->textEdit_13->clear();
    myserial.set_show_slot(socket_send);
    myserial.setData("0C");
}
/**socket接收
 * @brief MainWindow::on_pushButton_14_clicked
 */
void MainWindow::on_pushButton_14_clicked()
{
    ui->textEdit_13->clear();
    myserial.set_show_slot(socket_rec);
    myserial.setData("0D");
}
/**Http升级
 * @brief MainWindow::on_pushButton_18_clicked
 */
void MainWindow::on_pushButton_18_clicked()
{
    ui->textEdit_14->clear();
    myserial.set_show_slot(ota_http_update);
    myserial.setData("0E");

}

void MainWindow::on_pushButton_19_clicked()
{
    ui->textEdit_14->clear();
    myserial.set_show_slot(ota_triggle_update);
    myserial.setData("0F");
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->textEdit_14->clear();
    myserial.set_show_slot(ota_state_check);
    myserial.setData("10");
}
/**结束升级
 * @brief MainWindow::on_pushButton_21_clicked
 */
void MainWindow::on_pushButton_21_clicked()
{
    ui->textEdit_14->clear();
    myserial.set_show_slot(ota_end_update);
    myserial.setData("11");
}
/**系统重启
 * @brief MainWindow::on_pushButton_22_clicked
 */
void MainWindow::on_pushButton_22_clicked()
{
//    memset(&sys_pack,0,sizeof(sys_pack_t));
//    sys_pack.reboot=true;
    ui->textEdit_15->clear();
    myserial.set_show_slot(sys_reboot);
    myserial.setData("12");
}



void MainWindow::on_pushButton_23_clicked()
{
    ui->textEdit_15->clear();
    myserial.set_show_slot(sys_memory_handle);
    myserial.setData("13");
}
/**LED操作
 * @brief MainWindow::on_pushButton_26_clicked
 */
void MainWindow::on_pushButton_26_clicked()
{
    ui->textEdit_15->clear();
    myserial.set_show_slot(sys_memory_handle);
    myserial.setData("13");
}


