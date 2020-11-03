#include "mainwindow.h"
#include <QApplication>
#include "form.h"
#include<iostream>
#include"ctool.h"
#include"assert.h"
#include<stdlib.h>
#include "form2.h"
#include<vector>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    #if 1
    Form w;
    w.show();



#endif
    #if 0
    Form2 w;
    w.show();
    #endif

    vector<int>vec(10);//10个元素全部初始化为零


    //    char **oo=NULL;
    //    assert(oo);
    char buf[100];
    sprintf(buf, "%x", 14567);//16进制打印
    cout << buf << endl;



    unsigned char s1[2]={0x00,0x13};
    unsigned char c1=s1[0];
    unsigned char c2=s1[1];
    int b=c1<<8|c2;
    cout<<b<<endl;

    unsigned char s2[2]={012,013};
    unsigned char c3=s2[0];
    unsigned char c4=s2[1];
    int b2=c3<<6|c4;
    cout<<b2<<endl;

    //int转unsigned char 十六进制数组
    int d=100;
    unsigned char s3[2]={0};
    s3[0]=(d>>8)&0xff;
    s3[1]=d&0xff;
    printf("%x\n",s3[1]);
    return a.exec();

}



