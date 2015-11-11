#include "stdio.h"
#include "stdlib.h"
#include "tea.h"

/*
 buf为输入明文，输出密文 maybe 64bit =8 Bytes.
 key为密钥  maybe 128bit =16 Bytes.
 */
//void tea_encrypt(  char* buf, char* key ){
//	 long *v=( long *)buf;
//	 long *k=( long *)key;
//
//     long y=v[0], z=v[1], sum=0, i;         /* set up */
//    unsigned long delta=0x9e3779b9;                 /* a key schedule constant */
//     long a=k[0], b=k[1], c=k[2], d=k[3];   /* cache key */
//    for (i=0; i < 32; i++) {                        /* basic cycle start */
//        sum += delta;
//        y += ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
//        z += ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);/* end cycle */
//    }
//    v[0]=y;
//    v[1]=z;
//}

void tea_encrypt(  char* buf, char* key ){
    int  *v=( int  *)buf;
    int *k=( int  *)key;
    
    int  y=v[0], z=v[1], sum=0, i;         /* set up */
    unsigned int delta=0x9e3779b9;                 /* a key schedule constant */
    int a=k[0], b=k[1], c=k[2], d=k[3];   /* cache key */
    for (i=0; i < 32; i++) {                        /* basic cycle start */
        sum += delta;
        y += ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
        z += ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);/* end cycle */
    }
    v[0]=y;
    v[1]=z;
}

/*
 buf为输入密文，输出明文 maybe 64bit =8 Bytes.
 key为密钥 maybe 128bit =16 Bytes.
 */
//void tea_decrypt(  char* buf,  char* key ){
//	 long *v=(long *)buf;
//	 long *k=( long *)key;
//     long y=v[0], z=v[1];
//    unsigned long sum=0xC6EF3720, i; /* set up */
//    unsigned long delta=0x9e3779b9;                  /* a key schedule constant */
//    long a=k[0], b=k[1], c=k[2], d=k[3];    /* cache key */
//    for(i=0; i<32; i++) {                            /* basic cycle start */
//        z -= ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);
//        y -= ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
//        sum -= delta;                                /* end cycle */
//    }
//    v[0]=y;
//    v[1]=z;
//}

void tea_decrypt(  char* buf,  char* key ){
    int *v=(int *)buf;
    int *k=( int *)key;
    int y=v[0], z=v[1];
    unsigned int sum=0xC6EF3720, i; /* set up */
    unsigned int delta=0x9e3779b9;                  /* a key schedule constant */
    int a=k[0], b=k[1], c=k[2], d=k[3];    /* cache key */
    for(i=0; i<32; i++) {                            /* basic cycle start */
        z -= ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);
        y -= ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
        sum -= delta;                                /* end cycle */
    }
    v[0]=y;
    v[1]=z;
}



/*
 buf 为输入明文，输出密文
 len 数据长度
 key 为密钥  maybe 128bit =16 Bytes.
 */
void tea_encrypt_fun(char* buf, int len,  char* key )
{
    int cycle = len/8;
    int i;
    for(i=0;i<cycle;i++)
    {
        tea_encrypt(&buf[i*8],key );
    }
    
}

/*
 buf为输入密文，输出明文
 len 数据长度
 key为密钥 maybe 128bit =16 Bytes.
 */
void tea_decrypt_fun(char* buf, int len,char* key )
{
    int cycle = len/8;
    int i;
    for(i=0;i<cycle;i++)
    {
//        printf("----------wahaha------------%d\n",i);
        tea_decrypt(&buf[i*8],key );
    }
    
}

