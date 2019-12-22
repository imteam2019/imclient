#ifndef COMPRESS_H
#define COMPRESS_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Compress module of the IM Toolkit.
** It definited a abstract class.
**
** Created by: Shengbo.Zeng
** Created date: 12/22/2019
**
**
**
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
using namespace std;
class Compress {
 public:
  explicit Compress();
  virtual ~Compress() = 0;
  virtual unsigned char *compress(const unsigned char *inData,
                                  unsigned long inDataLen, unsigned long width,
                                  unsigned long height,
                                  unsigned long *outDataLen) = 0;

 protected:
  virtual void init() = 0;
};

#endif  // COMPRESS_H
