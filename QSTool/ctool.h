#ifndef CTOOL_H
#define CTOOL_H
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<string.h>
#include<QString>
void AsciiToHex(unsigned char *SrcAscii,int srcLen,unsigned char *distHEX);
/*
 * hex to Ascii
 * */
void HexToAscii(unsigned char *SrcHex,int srcLen,unsigned char *distAscii);
int roundStrAndInt(QString &str);

unsigned char HexToC(unsigned char hex);
unsigned char CToHex(unsigned char C);
void StrToHex(unsigned char *dist,const unsigned char *src,int len);
void HexToStr(char *dist,const unsigned char *src,int len);
/*一个HEX 转 HEX STR*/
void vOneTwo(unsigned char *in, unsigned int lc, unsigned char *out);
/*一个HEX STR 转 HEX*/
void vTwoOne(char *in, unsigned int in_len, unsigned char *out);
void crc16_CCITT(unsigned char *crcout,unsigned char *datain, int datalen,unsigned int initcrc);


char* creat_crc_buf(char *buf,int iLen);





#endif // CTOOL_H
