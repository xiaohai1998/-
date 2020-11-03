#include "form2.h"
#include "ui_form2.h"
#include"ctool.h"
#include<QSerialPortInfo>
QList<QSerialPortInfo> seriList;
HANDLE m_HANDLE=NULL;
char outs[1024]={0};
Form2::Form2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form2)
{
    ui->setupUi(this);
    item_name="";
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    InitUi();
    seriList = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &info, seriList) {
        ui->serial_num_comboBox->addItem(info.portName());
    }
    for(QList<QSerialPortInfo>::iterator it=seriList.begin();it!=seriList.end();++it){
        if(it->portName()=="COM11"){
            ui->serial_num_comboBox->setCurrentText("COM11");
            break;
        }
    }

    m_thread=new QThread(this);
    m_mythread=new mythread();
    m_mythread->moveToThread(m_thread);
    m_thread->start();
    connect(m_mythread,&mythread::AlgorithmSignal,this,&Form2::deal_signal);
    connect(m_mythread,&mythread::CommSig,this,&Form2::deal_signal);
    connect(m_mythread,&mythread::FotaSig,this,&Form2::deal_signal);
    connect(m_mythread,&mythread::ManageSig,this,&Form2::deal_signal);
    connect(m_mythread,&mythread::MqttSig,this,&Form2::deal_signal);
    connect(m_mythread,&mythread::TaskSig,this,&Form2::deal_signal);
    connect(m_mythread,&mythread::ParamSig,this,&Form2::deal_signal);
    connect(m_mythread,&mythread::TimeSig,this,&Form2::deal_signal);
    connect(m_mythread,&mythread::ToolSig,this,&Form2::deal_signal);
    connect(m_mythread,&mythread::TTsSig,this,&Form2::deal_signal);
    connect(this,&Form2::start_signal,m_mythread,&mythread::start);
    connect(this,&Form2::destroyed,this,&Form2::deal_close);
    com_label_show=new QLabel(this);
    com_label_show->resize(300,30);
    com_label_show->move(850,800);
}

Form2::~Form2()
{
    delete ui;

    qDebug()<<pItems[0]<<pItems[1];
    //    for(int i=0;i<10;i++){
    //        if(pItems[i]!=NULL){
    //            delete pItems[i];
    //            qDebug()<<"释放";
    //        }
    //    }

}

void Form2::InitUi()
{
    QStandardItemModel *model = new QStandardItemModel(0, 1,this);
    ui->treeView->setColumnWidth(0,50);

    model->setHeaderData(0, Qt::Horizontal, tr("模块"));


    QStandardItem *items[]={new QStandardItem("算法操作接口"),
                            new QStandardItem("通信类操作接口"),
                            new QStandardItem("FOTA操作接口"),
                            new QStandardItem("系统管理类操作接口"),
                            new QStandardItem("MQTT操作接口"),
                            new QStandardItem("系统任务操作接口"),
                            new QStandardItem("PARAM操作接口"),
                            new QStandardItem("时间操作接口"),
                            new QStandardItem("工具类操作接口"),
                            new QStandardItem("TTS操作接口")};

    pItems=items;


    for(unsigned int i=0;i<sizeof(items)/sizeof(items[0]);i++){
        model->setItem(i, 0, items[i]);
    }

    QString AlgorithmItem[]={"API_ALGORITHM_HmacSha1","API_ALGORITHM_Rsacrypt",
                             "API_ALGORITHM_Sha1",
                             "API_ALGORITHM_Sha256",
                             "API_ALGORITHM_SignVerify",
                             "API_Algotithm_SM2Encrypt"};

    QList<QStandardItem *> childItems;
    for(unsigned int i=0;i<sizeof(AlgorithmItem)/sizeof(AlgorithmItem[0]);i++){
        QStandardItem *item = new QStandardItem(AlgorithmItem[i]);
        childItems.push_back(item);
    }
    items[0]->appendRows(childItems);
    childItems.clear();

    QString CommItem[]={"API_COMM_CheckStatus","API_COMM_Close",
                        "API_COMM_Connect",
                        "API_COMM_GetLocalIp",
                        "API_COMM_HttpGet",
                        "API_COMM_HttpPost",
                        "API_COMM_ModuleConnect",
                        "API_COMM_ModuleDisconnect",
                        "API_COMM_ModuleGetHostByName",
                        "API_COMM_ModuleGetquality",
                        "API_COMM_ModuleGetStatus",
                        "API_COMM_ModuleInit",
                        "API_COMM_ReadLength",
                        "API_COMM_ReceivePackage",
                        "API_COMM_SendPackage",
                        "API_COMM_Sntp_CheckStatus",
                        "API_COMM_Sntp_Start",
                        "API_COMM_WIFI_Connect_Success_Event_Register",
                        "API_COMM_WIFI_Connect_Success_Event_Unregister",
                        "API_COMM_WIFI_Connectfail_Event_Register",
                        "API_COMM_WIFI_Connectfail_Event_Unregister",
                        "API_COMM_WIFI_Disconnect_Event_Register",
                        "API_COMM_WIFI_Disconnect_Event_Unregister",
                        "API_COMM_WIFIGetAPInfo",
                        "API_COMM_WIFIGetMac",
                        "API_COMM_WIFIGetquality",
                        "API_COMM_WIFIGetStatus",
                        "API_COMM_WIFIGetVersion",
                        "API_COMM_WIFISetMac",
                        "API_COMM_WIFISetNetWork"};

    for(unsigned int i=0;i<sizeof(CommItem)/sizeof(CommItem[0]);i++){
        QStandardItem *item = new QStandardItem(CommItem[i]);

        childItems.push_back(item);
    }
    items[1]->appendRows(childItems);
    childItems.clear();






    QString FOTAItem[]={"API_FOTA_RegionEarse","API_FOTA_RegionRead",
                        "API_FOTA_RegionWrite",
                        "API_FOTA_Trigger",
                        "API_FOTA_Update_CheckState",
                        "API_FOTA_Update_Exit",
                        "API_FOTA_Update_Http"};

    for(unsigned int i=0;i<sizeof(FOTAItem)/sizeof(FOTAItem[0]);i++){
        QStandardItem *item = new QStandardItem(FOTAItem[i]);
        childItems.push_back(item);
    }
    items[2]->appendRows(childItems);
    childItems.clear();


    QString ManageItem[]={"API_SYS_Button_Register_Callback",
                          "API_SYS_Button_UnRegister_Callback",
                          "API_SYS_Calloc",
                          "API_SYS_Free",
                          "API_SYS_GetFreeHeapSize",
                          "API_SYS_Getlibver",
                          "API_SYS_GetSDKver",
                          "API_SYS_GetVbatVol",
                          "API_SYS_GetVolume",
                          "API_SYS_LedOpCode",
                          "API_SYS_LedStatus",
                          "API_SYS_Malloc",
                          "API_SYS_Realloc",
                          "API_SYS_Reboot",
                          "API_SYS_SetVolume"};

    for(unsigned int i=0;i<sizeof(ManageItem)/sizeof(ManageItem[0]);i++){
        QStandardItem *item = new QStandardItem(ManageItem[i]);
        childItems.push_back(item);
    }
    items[3]->appendRows(childItems);
    childItems.clear();

    QString MATTItem[]={"API_MQTT_Close",
                        "API_MQTT_Connect",
                        "API_MQTT_Publish",
                        "API_MQTT_Subscribe",
                        "API_MQTT_Unsubscribe"};
    for(unsigned int i=0;i<sizeof(MATTItem)/sizeof(MATTItem[0]);i++){
        QStandardItem *item = new QStandardItem(MATTItem[i]);
        childItems.push_back(item);
    }
    items[4]->appendRows(childItems);
    childItems.clear();

    QString TaskItem[]={"API_MULTITASK_QueueCreate",
                        "API_MULTITASK_QueueDelete",
                        "API_MULTITASK_QueueReceive",
                        " API_MULTITASK_QueueReset",
                        "API_MULTITASK_QueueSend",
                        "API_MULTITASK_QueueSpacesAvailable",
                        "API_MULTITASK_SemaphoreCreateMutex",
                        "API_MULTITASK_SemaphoreDelete",
                        "API_MULTITASK_SemaphoreGive",
                        "API_MULTITASK_SemaphoreTake",
                        "API_MULTITASK_TaskCreate",
                        "API_MULTITASK_TaskDelay",
                        "API_MULTITASK_TaskDelete"};

    for(unsigned int i=0;i<sizeof(TaskItem)/sizeof(TaskItem[0]);i++){
        QStandardItem *item = new QStandardItem(TaskItem[i]);
        childItems.push_back(item);
    }
    items[5]->appendRows(childItems);
    childItems.clear();


    QString ParamItem[]={"API_PARAM_Delete_data",
                         "API_PARAM_Read_str",
                         "API_PARAM_Read_val",
                         "API_PARAM_Write_str",
                         "API_PARAM_Write_val"};
    for(unsigned int i=0;i<sizeof(ParamItem)/sizeof(ParamItem[0]);i++){
        QStandardItem *item = new QStandardItem(ParamItem[i]);
        childItems.push_back(item);
    }
    items[6]->appendRows(childItems);
    childItems.clear();

    QString TimeItem[]={"API_TIME_GetRtcValue",
                        "API_TIME_GetTime",
                        "API_TIME_SetTime()",
                        "API_TIME_TimeCheck",
                        "API_TIME_TimeOpen",
                        "API_TIME_TimerCreate",
                        "API_TIME_TimerDelete",
                        "API_TIME_TimeStop"};

    for(unsigned int i=0;i<sizeof(TimeItem)/sizeof(TimeItem[0]);i++){
        QStandardItem *item = new QStandardItem(TimeItem[i]);
        childItems.push_back(item);
    }
    items[7]->appendRows(childItems);
    childItems.clear();

    QString ToolItem[]={"API_TOOL_16To10",
                        "API_TOOL_AscToBcd",
                        "API_TOOL_AscToHex",
                        "API_TOOL_AscToInt",
                        "API_TOOL_BcdToAsc",
                        "API_TOOL_BcdToInt",
                        "API_TOOL_BcdToUint64",
                        "API_TOOL_C2ToInt",
                        "API_TOOL_C4ToUint",
                        "API_TOOL_CStrlcpy",
                        "API_TOOL_GbktoUtf",
                        "API_TOOL_Getrand",
                        "API_TOOL_GetTimestamp",
                        "API_TOOL_HexToAsc",
                        "API_TOOL_IntToBcd",
                        "API_TOOL_IntToC2Hex",
                        "API_TOOL_StrCaseCmp",
                        "API_TOOL_StrRemovechar",
                        "API_TOOL_tlv_analyze",
                        "API_TOOL_tlv_analyze_taglist",
                        "API_TOOL_tlv_build",
                        "API_TOOL_tlv_destroy",
                        "API_TOOL_tlv_find",
                        "API_TOOL_tlv_get_taglist",
                        "API_TOOL_tlv_pack",
                        "API_TOOL_UintToC4",
                        "API_TOOL_urldecode",
                        "API_TOOL_urlencode",
                        "API_TOOL_UtftoGbk",
                        "strmcpy"};

    for(unsigned int i=0;i<sizeof(ToolItem)/sizeof(ToolItem[0]);i++){
        QStandardItem *item = new QStandardItem(ToolItem[i]);
        childItems.push_back(item);
    }
    items[8]->appendRows(childItems);
    childItems.clear();

    QString TTSItem[]={"API_TTS_CheckState",
                       "API_TTS_playAudios",
                       "API_TTS_PlayAudioString",
                       "API_TTS_SetPitch",
                       "API_TTS_SetSpeed"};
    for(unsigned int i=0;i<sizeof(TTSItem)/sizeof(TTSItem[0]);i++){
        QStandardItem *item = new QStandardItem(TTSItem[i]);
        childItems.push_back(item);
    }
    items[9]->appendRows(childItems);
    childItems.clear();


    ui->treeView->setModel(model);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void Form2::on_treeView_clicked(const QModelIndex &index)
{
    item_name=ui->treeView->model()->itemData(index).values()[0].toString();

}

void Form2::on_pushButton_clicked()
{
    if(m_HANDLE==NULL){
        QMessageBox::information(this,"提示","请先打开串口",QMessageBox::Ok);
        return;
    }
    if(item_name=="算法操作接口"){
        qDebug()<<"算法操作接口测试";
        emit start_signal(item_name);
        datas_vector.clear();
        //存放要发送的数据
        datas_vector.push_back("02000a000400021234195E");
        datas_vector.push_back("02000B000400021234FF38");
        datas_vector.push_back("0200090045406569C22743BC4A83D9978"
                               "CF34B7A1B3D9003A73B85F793C7820F94"
                               "8D1531916F2ED05DF403B908E10AFE382"
                               "FBD64133C4DA60366904CDA5DA1AE5794"
                               "502F5793000212349E0F");
        datas_vector.push_back("0200030005010002123423AE");
        datas_vector.push_back("02000400830200805F18988B2DBDEEE09"
                               "FDCE5D2A533268869649A39866A5900F4"
                               "0753DF01C229181C573A4D9C4A5D1BF48"
                               "AD3B83882FBB875B95B9357BC84B9DB98"
                               "AD38D05FCC2D079A0CB146B8CD6CD525F"
                               "E43BE3DE02CFB756D8FD4F3159836D188"
                               "DAFCAAAB158522A24433CC63021289B24"
                               "43E3FD6BD4F9F2CA7C33C29F782663698"
                               "57B277DD5A20");
        datas_vector.push_back("02000500050100021234AE4F");
        datas_vector.push_back("020006008302008003B6EF299FEE9B91B"
                               "4F5E1345410FA48C3F305F5D361C6253E"
                               "1EAFEE735A2C3F704DD18564FABDE1286"
                               "7B941426865E52FD9C922887436DC1207"
                               "19254AC6EB1047FB261F4864A6C91D805"
                               "0E70B24274A864141AC8C7582F2E1AC5D"
                               "F3A188F05B5EB8A8DE8810657F2DE2DEB"
                               "FC4A8FBB01107EC5E33CBB4AA1E25ACB9"
                               "D902B5BD10CA");
        datas_vector.push_back("02000700050000021234250F");
        datas_vector.push_back("02000800050000021234E00C");

    }
    else if(item_name=="通信类操作接口"){
        emit start_signal(item_name);
        datas_vector.clear();
        datas_vector<<"02010100000093E1"<<"0201040000006C14"
                   <<"0201050000005F25"<<"0201070000003947"
                  <<"0201080000002979"<<"0201090000001A48"
                 <<"020112000000F182"<<"02010A0000009BB8"
                <<"02010B000000CEEB"<<"02010C000000FDDA"
               <<"02010D000000644D"<<"02010E000000577C"
              <<"02010F000000022F"<<"02011000000097E0"
             <<"020111000000A4D1";
    }
    else if(item_name=="FOTA操作接口"){
        emit start_signal(item_name);
        datas_vector.clear();
        datas_vector<<"020201000000083D"<<"0202020000005D6E";
    }
    else if(item_name=="系统管理类操作接口"){
        emit start_signal(item_name);
        datas_vector.clear();
        datas_vector<<"02030300000018EB"<<"0203020000002BDA"<<"020304000000817C"
                   <<"020307000000D42F"<<"020308000000C411"<<"020305000000B24D"
                  <<"020306000000E71E"<<"020309000000F720"<<"02030A00000076D0"
                 <<"02030B0000002383"<<"02030C00000010B2";
    }
    else if(item_name=="MQTT操作接口"){
        emit start_signal(item_name);
        datas_vector.clear();
        datas_vector<<"";

    }
    else if(item_name=="系统任务操作接口"){


    }
    else if(item_name=="PARAM操作接口"){
        datas_vector.clear();
    }
    else if(item_name=="时间操作接口"){
        emit start_signal(item_name);
        datas_vector.clear();
        datas_vector<<"020702000000E12B"<<"020701000720201103134157A29B"
                   <<"02070500000078BC"<<"0207040000004B8D"<<"0207060000002DEF"
                  <<"0207070000001EDE";
    }
    else if(item_name=="工具类操作接口"){
        emit start_signal(item_name);
        datas_vector.clear();
        datas_vector<<"0209010004000212341622"<<"0209020004000212344371"
                   <<"0209030004000212347040"<<"020904000400021234E9D7"
                  <<"020905000400021234DAE6"<<"0209060004000212348FB5"
                 <<"020907000400021234BC84"<<"020908000400021234ACBA"
                <<"0209090004000212349F8B"<<"02090A0004000212341E7B"
               <<"02090B0004000212344B28"<<"02090C0004000212347819"
              <<"02090F00000087EC"<<"0209170000008BB4"<<"0209110000002112"
             <<"0209120000007441"<<"0209130000004770"<<"020914000000DEE7"
            <<"020915000000EDD6"<<"020916000000B885"<<"0209100000001223"
           <<"02090D000000E18E"<<"02090E000000D2BF";

    }
    else if(item_name=="TTS操作接口"){
        datas_vector.clear();
    }
    else
    {
        QMessageBox::information(this,"提示","请选择测试项",QMessageBox::Ok);
        return;
    }
}

void Form2::on_buttonBox_accepted()
{
    QString temp="\\\\.\\"+ui->serial_num_comboBox->currentText();
    m_HANDLE=open_com(QStringToTCHAR(temp));
    if(m_HANDLE!=INVALID_HANDLE_VALUE)
    {
        com_label_show->setText(ui->serial_num_comboBox->currentText()+" is open");
        ui->serial_num_comboBox->setEnabled(false);
        ui->rate_comboBox->setEnabled(false);
    }
    else
        com_label_show->setText(ui->serial_num_comboBox->currentText()+" open fail");
}


HANDLE open_com(TCHAR *name)
{
    HANDLE m_hcom=CreateFile(name,GENERIC_WRITE|GENERIC_READ,0,NULL,OPEN_EXISTING,
                             0,NULL);
    if(m_hcom==INVALID_HANDLE_VALUE)
    {
        cout<<"creat file failed"<<endl;
        return NULL;
    }
    //设置缓冲区大小
    if(!SetupComm(m_hcom,1024,1024)){
        cout<<"setup failed"<<endl;
        CloseHandle(m_hcom);
        return NULL;
    }
    //设置超时
    COMMTIMEOUTS TimeOuts;
    memset(&TimeOuts,0,sizeof(TimeOuts));
    TimeOuts.ReadIntervalTimeout = 100;
    TimeOuts.ReadTotalTimeoutConstant = 1000;
    TimeOuts.ReadTotalTimeoutMultiplier = 100;
    TimeOuts.WriteTotalTimeoutConstant = 2000;
    TimeOuts.WriteTotalTimeoutMultiplier = 50;
    SetCommTimeouts(m_hcom,&TimeOuts);

    PurgeComm(m_hcom,PURGE_TXCLEAR|PURGE_RXCLEAR);//清空缓冲区

    DWORD dwError;
    COMSTAT cs;
    if (!ClearCommError(m_hcom,&dwError, &cs))
    {
        CloseHandle(m_hcom);
        return NULL;
    }
    //设置串口参数
    DCB dcb ;
    memset(&dcb,0,sizeof(DCB));

    if (!GetCommState(m_hcom,&dcb))
    {
        printf("GetCommState fail\n");
        return NULL;
    }

    dcb.DCBlength = sizeof(dcb);

    if (!BuildCommDCB(TEXT("115200,n,8,1"),&dcb))//填充ＤＣＢ的数据传输率、奇偶校验类型、数据位、停止位
    {
        printf("Build COmmDCB fail\n");
        CloseHandle(m_hcom);
        return NULL;
    }

    if(SetCommState(m_hcom,&dcb))
    {
        printf("SetCommState OK!\n");

    }
    return m_hcom;
}
unsigned char Send_driver_T(HANDLE fd, BYTE *data,DWORD dwDataLen)
{
    DWORD dwError;
    DWORD dwExpectSend = dwDataLen;
    DWORD dwRealSend = 0;
    BYTE *pSendBuffer;
    pSendBuffer = data;

    if(ClearCommError(fd,&dwError,NULL))
    {
        PurgeComm(fd,PURGE_TXABORT | PURGE_TXCLEAR);
    }

    if(!WriteFile(fd,pSendBuffer,dwExpectSend ,&dwRealSend,NULL))
    {
        //写串口失败
        printf("send error!\n");
        return 1;
    }

    return 0;
}
unsigned char Receive_driver_T(HANDLE fd, BYTE *data)
{
    DWORD dwError;
    DWORD dwWantRead=520;
    DWORD dwRealRead=0;
    BYTE* pReadBuf;
    pReadBuf=data;
    if (ClearCommError(fd,&dwError,NULL))
    {
        PurgeComm(fd,PURGE_TXABORT | PURGE_TXCLEAR);
    }
    if(!ReadFile(fd,pReadBuf,dwWantRead ,&dwRealRead,NULL))    //成功返回非0 //失败返回0
    {
        return 1;

    }
    if(dwRealRead>0){
        printf("recv_len = %d\n",dwRealRead);
    }
    memset(outs,0,1024);
    HexToStr(outs,pReadBuf,dwRealRead);
    printf("strs are %s\n",outs);
    return 0;

}
int Close_driver(void *fd)
{
    CloseHandle(fd);
    return 0;
}

void Form2::on_buttonBox_rejected()
{
    Close_driver(m_HANDLE);
    com_label_show->setText(ui->serial_num_comboBox->currentText()+" close");
}

void Form2::deal_signal()
{

    BYTE SendData[20] ={"123456"};
    unsigned char dist[1024]={0};
    BYTE RecvData[100] = {0};
    ui->textEdit->clear();
    ui->textEdit->append("算法操作接口测试");
    for(int i=0;i<datas_vector.size();i++){
        StrToHex(dist,(const unsigned char *)datas_vector[i],strlen(datas_vector[i]));
        if(Send_driver_T(m_HANDLE, dist,strlen(datas_vector[i])/2))//最后一个参数为字节数
        {
            printf("send fail\n");
        }else {
            printf("send success!\n");
        }
        Receive_driver_T(m_HANDLE, RecvData);

        if(i==4||i==6){
            ui->textEdit->append("receive:"+QString((const char *)RecvData));
        }
        else if(i==8){
            if(QString((const char *)RecvData)=="0000")
                ui->textEdit->append("receive:rsa public verify successfully！");
        }else{
            ui->textEdit->append("receive:"+QString(outs));
        }
        memset(dist,0,sizeof(dist));
        memset(RecvData,0,sizeof(RecvData));
    }


//    StrToHex(dist,(const unsigned char *)"02000a000400021234195E",strlen("02000a000400021234195E"));
//    if(Send_driver_T(m_HANDLE, dist,strlen("02000a000400021234195E")/2))//最后一个参数为字节数
//    {
//        printf("send fail\n");
//    }else {
//        printf("send success!\n");
//    }
//    Receive_driver_T(m_HANDLE, RecvData);
//    ui->textEdit->append("receive:"+QString(outs));

//    memset(dist,0,sizeof(dist));
//    memset(RecvData,0,sizeof(RecvData));

//    StrToHex(dist,(const unsigned char *)"02000B000400021234FF38",strlen("02000B000400021234FF38"));
//    if(Send_driver_T(m_HANDLE, dist,strlen("02000B000400021234FF38")/2))//最后一个参数为字节数
//    {
//        printf("send fail\n");
//    }
//    else {
//        printf("send success!\n");
//    }

//    Receive_driver_T(m_HANDLE, RecvData);
//    ui->textEdit->append("receive:"+QString(outs));



}

void Form2::deal_close()
{
    if(m_thread->isRunning()==false)
    {
        return;
    }
    m_thread->quit();
    m_thread->wait();
    delete m_thread;
}
