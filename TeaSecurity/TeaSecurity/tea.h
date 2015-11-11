#ifndef _TEA_H
#define _TEA_H

/*
buf 为输入明文，输出密文
len 数据长度
key 为密钥  maybe 128bit =16 Bytes.
*/
void tea_encrypt_fun(char* buf, int len,char* key );

/*
buf为输入密文，输出明文
len 数据长度
key为密钥 maybe 128bit =16 Bytes.
*/
void tea_decrypt_fun(char* buf, int len,char* key );

#endif
