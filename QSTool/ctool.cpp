#include"ctool.h"

void AsciiToHex(unsigned char *SrcAscii,int srcLen,unsigned char *distHEX)
{
    char hexstrtmp[3]={0x00},i;
    for(i=0;i<srcLen;i++)
    {
        sprintf(hexstrtmp,"%x",SrcAscii[i]);
        //		printf("hexstrtmp:%s\n",hexstrtmp);
        /*一个HEX STR 转 HEX*/
        //		void vTwoOne(char *in, unsigned int in_len, unsigned char *out)
        vTwoOne(hexstrtmp,2,&distHEX[i]);
        printf("distHEX[%d]->%x\n",i,distHEX[i]);
    }
}
/*
 * hex to Ascii
 * */
void HexToAscii(unsigned char *SrcHex,int srcLen,unsigned char *distAscii)
{
    int i;
    unsigned char Asciitmp[2];
    for(i=0;i<srcLen;i++)
    {
        //printf("SrcHex[%d]:%c\n",i,SrcHex[i]);
        sprintf((char *)Asciitmp,"%c",SrcHex[i]);
        //printf("Asciitmp[0]:%c\n",Asciitmp[0]);
        distAscii[i] = Asciitmp[0];
    }
}
unsigned char  HexToC(unsigned char hex)
{
    unsigned char c;
    switch(hex)
    {
    case 0x00:
    {
        c='0';
    };break;
    case 0x01:
    {
        c='1';
    };break;
    case 0x02:
    {
        c='2';
    };break;
    case 0x03:
    {
        c='3';
    };break;
    case 0x04:
    {
        c='4';
    };break;
    case 0x05:
    {
        c='5';
    };break;
    case 0x06:
    {
        c='6';
    };break;
    case 0x07:
    {
        c='7';
    };break;
    case 0x08:
    {
        c='8';
    };break;
    case 0x09:
    {
        c='9';
    };break;
    case 0x0A:
    {
        c='A';
    };break;
    case 0x0B:
    {
        c='B';
    };break;
    case 0x0C:
    {
        c='C';
    };break;
    case 0x0D:
    {
        c='D';
    };break;
    case 0x0E:
    {
        c='E';
    };break;
    case 0x0F:
    {
        c='F';
    };break;
    default:;

        ;break;
    }
    return c;
}
unsigned char  CToHex(unsigned char C)
{
    unsigned char hex;
    switch(C)
    {
    case '0':
    {
        hex = 0x00;
    };break;
    case '1':
    {
        hex = 0x01;
    };break;
    case '2':{
        hex = 0x02;
    };break;
    case '3':{
        hex = 0x03;
    };break;
    case '4':{
        hex = 0x04;
    };break;
    case '5':{
        hex = 0x05;
    };break;
    case '6':{
        hex = 0x06;
    };break;
    case '7':{
        hex = 0x07;
    };break;
    case '8':{
        hex = 0x08;
    };break;
    case '9':{
        hex = 0x09;
    };break;
    case 'A':{
        hex = 0x0A;
    };break;
    case 'a':{
        hex = 0x0A;
    };break;
    case 'B':{
        hex = 0x0B;
    };break;
    case 'b':{
        hex = 0x0B;
    };break;
    case 'C':{
        hex = 0x0C;
    };break;
    case 'c':{
        hex = 0x0C;
    };break;
    case 'D':{
        hex = 0x0D;
    };break;
    case 'd':{
        hex = 0x0D;
    };break;
    case 'E':{
        hex = 0x0E;
    };break;
    case 'e':{
        hex = 0x0E;
    };break;
    case 'F':{
        hex = 0x0F;
    };break;
    case 'f':{
        hex = 0x0F;
    };break;
    default:{
        printf("error char-->%c\n",C);
        hex = 0xFF;
    }
        ;break;
    }
    return hex;
}
void StrToHex(unsigned char *dist,const unsigned char *src,int len)
{
    //	unsigned char buffer[100]={0};
    int index = 0,i;
    for(i=0;i<len;i++)
    {
        dist[index] = (CToHex(src[i])<<4);
        //  buffer[index] = (CToHex(src[i])<<4);
        //  printf("dist[%d]=%02x  - src[%d]=%c\n",index,dist[index],i,src[i]);
        i++;
        dist[index] |= (CToHex(src[i]));
        // buffer[index] |= (CToHex(src[i]));
        // printf("dist[%d]=%02x  - src[%d]=%c\n",index,dist[index],i,src[i]);
        index++;
    }
}
void HexToStr(char *dist,const unsigned char *src,int len)
{
    unsigned char c[3]={0};
    unsigned char tmp[1024*4+1]={0};
    int i;
    for(i=0;i<len;i++)
    {
        memset(c,0x00,sizeof(c));

        // >> 右移4 取高位
        switch(src[i]>>4)
        {
            case 0x00:
            case 0x01:
            case 0x02:
            case 0x03:
            case 0x04:
            case 0x05:
            case 0x06:
            case 0x07:
            case 0x08:
            case 0x09:
            case 0x0A:
            case 0x0B:
            case 0x0C:
            case 0x0D:
            case 0x0E:
            case 0x0F:{
               c[0] = HexToC(src[i]>>4); //c[1] = HexToC(src[i]>>4); jerry modify for show tr31 result
            };break;
            default:{
               c[0] = 'F'; //c[1] = 'F';jerry modify for show tr31 result
                printf("---------------->高位非法参数\n");
            };break;
        }/*switch End*/


        // &0x0F  取低位

        switch(src[i]&0x0F)
        {
            case 0x00:
            case 0x01:
            case 0x02:
            case 0x03:
            case 0x04:
            case 0x05:
            case 0x06:
            case 0x07:
            case 0x08:
            case 0x09:
            case 0x0A:
            case 0x0B:
            case 0x0C:
            case 0x0D:
            case 0x0E:
            case 0x0F:{
                c[1] = HexToC(src[i]&0x0F);//c[0] = HexToC(src[i]&0x0F);jerry modify for show tr31 result
            };break;
            default:{
                c[1] = 'F';//c[0] = 'F';
                printf("---------------->低位非法参数\n");
            };break;
        }/*switch End*/


        // oper str to tmp;
        strcat((char *)tmp,(char *)c);
        //printf("tmp->%s",tmp);

    }/*for End*/
    //printf("(tmp)HexToStr->%s",tmp);
    strcpy((char *)dist,(char *)tmp);
}

/*一个HEX 转 HEX STR*/
void vOneTwo(unsigned char *in, unsigned int lc, unsigned char *out)
{
    static unsigned char ucHexToChar[17] = "0123456789ABCDEF";
    unsigned int nCounter;
    memcpy(ucHexToChar,"0123456789ABCDEF",16);
    for(nCounter = 0; nCounter < lc; nCounter++){
        out[2*nCounter] = ucHexToChar[(in[nCounter] >> 4)];
        out[2*nCounter+1] = ucHexToChar[(in[nCounter] & 0x0F)];
    }
}

/*long to hex str*/
void vLongToHex(long in,unsigned char *out)
{
    // FF FF FF FF
    out[0] = in&0xFF;
    out[1] = (in>>8)&0xFF;
    out[2] = (in>>16)&0xFF;
    out[3] = (in>>24)&0xFF;
}
/*一个HEX STR 转 HEX*/
void vTwoOne(char *in, unsigned int in_len, unsigned char *out)
{
    unsigned char tmp;
    unsigned int i;

    for(i=0;i<in_len;i+=2)
    {

        tmp = in[i];

        if(tmp > '9')
            tmp = toupper(tmp) - ('A' - 0x0A);
        else
            tmp &= 0x0f;

        tmp <<= 4;
        out[i/2]=tmp;
        tmp=in[i+1];
        if(tmp>'9')
            tmp = toupper(tmp) - ('A' - 0x0A);
        else
            tmp &= 0x0f;

        out[i/2]+=tmp;
    }
}
const unsigned short g_awhalfCrc16CCITT[16]={ /* CRC 半字节余式表*/
0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
};
void crc16_CCITT(unsigned char *crcout,unsigned char *datain, int datalen,unsigned int initcrc)
{
    unsigned char charmp;
    if(datalen > 0)
    while (datalen-- != 0)
    {
        charmp = (( unsigned char)(initcrc>>8))>>4;
        initcrc <<= 4;
        initcrc ^= g_awhalfCrc16CCITT[charmp^(*datain>>4)];
        charmp = (( unsigned char)(initcrc>>8))>>4;
        initcrc <<= 4;
        initcrc ^= g_awhalfCrc16CCITT[charmp^(*datain&0x0F)];
        datain++;
    }

    crcout[0] = initcrc >> 8;
    crcout[1] = initcrc & 0xFF;
}
char* creat_crc_buf(char *buf,int iLen)
{
    //CRC校验
    unsigned char CRC[2]={0};
    crc16_CCITT(CRC,(unsigned char*)buf,iLen,0);

    char *buf1=new char[5];
    memset(buf1,0,sizeof(char)*5);
    HexToStr(buf1,CRC,2);

    return buf1;
}
int roundStrAndInt(QString &str)
{
    int a=str.length()/2+1;
    str+="0";
    return a;
}
