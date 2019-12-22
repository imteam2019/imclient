#include "compressjpeg.h"

CompressJpeg::CompressJpeg() {
  init();
  return;
}

void CompressJpeg::init() {
  // TODO initial
  this->cinfo = new jpeg_compress_struct();
  this->jerr = new jpeg_error_mgr();
  return;
}

CompressJpeg::~CompressJpeg() {
  jpeg_destroy_compress(cinfo);
  delete this->cinfo;
}
/**
 * @brief CompressJpeg::compress 对指定缓冲区内的图片数据进行压缩
 * @param inData 数据源缓冲区指针
 * @param inDataLen 数据源缓冲区长度
 * @param outDataLen 存放返回压缩后缓冲区的长度
 * @return 返回压缩后缓冲区的指针，如果数据源为空，或发生错误，则返回空指针
 */
unsigned char *CompressJpeg::compress(const unsigned char *inData,
                                      unsigned long inDataLen,
                                      unsigned long width, unsigned long height,
                                      unsigned long *outDataLen) {
  if (inData == nullptr || 0 == inDataLen || 0 == width || 0 == height)
    return nullptr;

  unsigned char *outBuffer = nullptr;

  JSAMPROW image_buffer;
  JDIMENSION image_width = width;
  JDIMENSION image_height = height;

  JSAMPROW row_pointer[1]; /* pointer to JSAMPLE row[s] */
  unsigned int row_stride; /* physical row width in image buffer */

  // qi.constScanLine()
  // image_buffer = (JSAMPROW)qi.constScanLine(0);
  image_buffer = (JSAMPROW)inData;

  cinfo->err = jpeg_std_error(jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(cinfo);
  jpeg_mem_dest(cinfo, &outBuffer, outDataLen);

  cinfo->image_width = image_width;
  cinfo->image_height = image_height;
  cinfo->input_components = 4;
  cinfo->in_color_space = JCS_EXT_BGRA;
  cinfo->optimize_coding = true;

  jpeg_set_defaults(cinfo);

  jpeg_set_quality(cinfo, quality, true);

  jpeg_start_compress(cinfo, true);

  row_stride = image_width * 4;

  while (cinfo->next_scanline < cinfo->image_height) {
    row_pointer[0] = &image_buffer[cinfo->next_scanline * row_stride];
    jpeg_write_scanlines(cinfo, row_pointer, 1);
  }

  jpeg_finish_compress(cinfo);

  return outBuffer;
}
