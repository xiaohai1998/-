#ifndef MYTHREAD_H
#define MYTHREAD_H

#include<QObject>
class mythread:public QObject
{
    Q_OBJECT
public:
    mythread();
    void start(QString str);

signals:
    void AlgorithmSignal();
    void CommSig();
    void FotaSig();
    void ManageSig();
    void MqttSig();
    void TaskSig();
    void ParamSig();
    void TimeSig();
    void ToolSig();
    void TTsSig();
};

#endif // MYTHREAD_H
