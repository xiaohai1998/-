#include "mythread.h"

mythread::mythread()
{

}
void mythread::start(QString item_name)
{
    if(item_name=="算法操作接口"){
        emit AlgorithmSignal();
    }
    else if(item_name=="通信类操作接口"){
        emit CommSig();
    }
    else if(item_name=="FOTA操作接口"){
        emit FotaSig();
    }
    else if(item_name=="系统管理类操作接口"){
        emit ManageSig();
    }
    else if(item_name=="MQTT操作接口"){
        emit MqttSig();

    }
    else if(item_name=="系统任务操作接口"){
        emit TaskSig();
    }
    else if(item_name=="PARAM操作接口"){
        emit ParamSig();
    }
    else if(item_name=="时间操作接口"){
        emit TimeSig();
    }
    else if(item_name=="工具类操作接口"){
        emit ToolSig();
    }
    else if(item_name=="TTS操作接口"){
        emit TTsSig();
    }
}
