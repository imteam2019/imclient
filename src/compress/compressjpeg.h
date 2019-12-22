#ifndef COMPRESSJPEG_H
#define COMPRESSJPEG_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Compress module of the IM Toolkit.
** It definited a class for compressing jpeg.
**
** Created by: Shengbo.Zeng
** Created date: 12/22/2019
**
**
**
****************************************************************************/
#include "compress.h"
#include "jpeglib.h"

class CompressJpeg : public Compress {
 public:
  CompressJpeg();
  ~CompressJpeg() override;
  unsigned char *compress(const unsigned char *inData, unsigned long inDataLen,
                          unsigned long width, unsigned long height,
                          unsigned long *outDataLen) override;

 protected:
  void init() override;

 private:
  int quality = 28;
  struct jpeg_compress_struct *cinfo;
  struct jpeg_error_mgr *jerr;
};

#endif  // COMPRESSJPEG_H
