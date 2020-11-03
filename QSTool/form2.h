#ifndef FORM2_H
#define FORM2_H

#include <QWidget>
#include<QTextCodec>
#include<QDebug>
#include<QStandardItemModel>
#include<QMessageBox>
#include <iostream>
#include<windows.h>
#include<stdio.h>
#include"mythread.h"
#include<QLabel>
#include<QThread>
#include<QVector>
#ifdef UNICODE

#define QStringToTCHAR(x)     (wchar_t*) x.utf16()

#define PQStringToTCHAR(x)    (wchar_t*) x->utf16()

#define TCHARToQString(x)     QString::fromUtf16((x))

#define TCHARToQStringN(x,y)  QString::fromUtf16((x),(y))

#else

#define QStringToTCHAR(x)     x.local8Bit().constData()

#define PQStringToTCHAR(x)    x->local8Bit().constData()

#define TCHARToQString(x)     QString::fromLocal8Bit((x))

#define TCHARToQStringN(x,y)  QString::fromLocal8Bit((x),(y))

#endif
using namespace std;
namespace Ui {
class Form2;
}

class Form2 : public QWidget
{
    Q_OBJECT

public:
    explicit Form2(QWidget *parent = 0);
    ~Form2();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void deal_signal();

    void deal_close();
signals:

    void start_signal(QString);
    void algorithm_signal(QString);
private:
    void InitUi();
    QString item_name;
    QLabel *com_label_show;
    QStandardItem **pItems;
    QThread *m_thread;
    mythread *m_mythread;

    QVector<const char *>datas_vector;


private:
    Ui::Form2 *ui;
};
HANDLE open_com(TCHAR *name);
unsigned char Send_driver_T(HANDLE fd, BYTE *data,DWORD dwDataLen);
unsigned char Receive_driver_T(HANDLE fd, BYTE *data);
#endif // FORM2_H
