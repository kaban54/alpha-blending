#ifndef BMP_H
#define BMP_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct BMP_FILE_HEADER
{
    int16_t type;
    int32_t size;
    int16_t reserved1;
    int16_t reserved2;
    int32_t off_bits;
};

struct BMP_INFO_HEADER
{
    int32_t size;
    int32_t width;
    int32_t height;
    int16_t planes;
    int16_t bit_count;
    int32_t compression;
    int32_t image_size;
    int32_t x_px_per_meter;
    int32_t y_px_per_meter;
    int32_t clr_used;
    int32_t clr_important;
};

struct RGBA
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
};

struct BmpImage
{
    BMP_FILE_HEADER bmpfh;
    BMP_INFO_HEADER bmpih;
    RGBA *pixels;
    int width;
    int height;
};

enum BMP_ERRORS
{
    BMP_OK              = 0,
    BMP_NULLPTR         = 1,
    BMP_WRONG_FORMAT    = 2,
};

int LoadImage (FILE *file, BmpImage *img);
int SaveImage (FILE *file, BmpImage *img);

void read_bmp_file_header (FILE *file, BMP_FILE_HEADER *bmpfh);
void read_bmp_info_header (FILE *file, BMP_INFO_HEADER *bmpih);

void write_bmp_file_header (FILE *file, BMP_FILE_HEADER *bmpfh);
void write_bmp_info_header (FILE *file, BMP_INFO_HEADER *bmpih);

void GetBlendedImg (BmpImage *back_img, BmpImage *front_img, BmpImage *result_img);

void ImgDtor (BmpImage *img);

#endif