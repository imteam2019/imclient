#ifndef DES_H
#define DES_H

/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the DES Encrypt/Decrypt module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 11/26/2019
**
**
**
****************************************************************************/
class DES{
public:

    int encrypt ( unsigned char key[8], unsigned char* data, int blocks = 1 );
    int decrypt ( unsigned char key[8], unsigned char* data, int blocks = 1 );
    int yencrypt ( unsigned char key[8], unsigned char* data, int size );
    int ydecrypt ( unsigned char key[8], unsigned char* in, int blocks, int* size = 0 );
    int extend ( int size ) { return (size/8+1)*8; };

private:
    void des(unsigned char* in, unsigned char* out, int blocks);
    void des_block(unsigned char* in, unsigned char* out);

private:
    unsigned long KnL[32];
    enum Mode { ENCRYPT, DECRYPT };
    void deskey(unsigned char key[8], Mode md);
    void usekey(unsigned long *);
    void cookey(unsigned long *);

private:
    void scrunch(unsigned char *, unsigned long *);
    void unscrun(unsigned long *, unsigned char *);
    void desfunc(unsigned long *, unsigned long *);

private:
    static unsigned char Df_Key[24];
    static unsigned short bytebit[8];
    static unsigned long bigbyte[24];
    static unsigned char pc1[56];
    static unsigned char totrot[16];
    static unsigned char pc2[48];
    static unsigned long SP1[64];
    static unsigned long SP2[64];
    static unsigned long SP3[64];
    static unsigned long SP4[64];
    static unsigned long SP5[64];
    static unsigned long SP6[64];
    static unsigned long SP7[64];
    static unsigned long SP8[64];
};
#endif
