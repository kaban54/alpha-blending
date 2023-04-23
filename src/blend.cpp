#include "bmp.h"

const char   back_file_name [] = "back.bmp";
const char  front_file_name [] = "cat.bmp";
const char result_file_name [] = "result.bmp";

int main ()
{
    FILE * back_file = fopen ( back_file_name, "rb");
    FILE *front_file = fopen (front_file_name, "rb");

    BmpImage   back_img = {};
    BmpImage  front_img = {};
    BmpImage result_img = {};

    LoadImage (back_file , &back_img );
    LoadImage (front_file, &front_img);

    fclose ( back_file);
    fclose (front_file);

    GetBlendedImg (&back_img, &front_img, &result_img);

    FILE *result_file = fopen (result_file_name, "wb");
    SaveImage (result_file, &result_img);
    fclose (result_file);

    ImgDtor (&  back_img);
    ImgDtor (& front_img);
    ImgDtor (&result_img);

    return 0;
}

void GetBlendedImg (BmpImage *back_img, BmpImage *front_img, BmpImage *result_img)
{
    RGBA *px_back   =   back_img -> pixels;
    RGBA *px_front  =  front_img -> pixels;
    
    int w = back_img -> width;
    int h = back_img -> height;

    RGBA *px_result = (RGBA *) calloc (w * h, sizeof (px_result [0]));

    result_img -> pixels = px_result;
    result_img -> width  = w;
    result_img -> height = h;
    result_img -> bmpfh = back_img -> bmpfh;
    result_img -> bmpih = back_img -> bmpih;

    uint8_t a = 0;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            a = px_front -> a;
            px_result -> r = ( (px_front -> r * a) + (px_back -> r * (255 - a)) ) >> 8;
            px_result -> g = ( (px_front -> g * a) + (px_back -> g * (255 - a)) ) >> 8;
            px_result -> b = ( (px_front -> b * a) + (px_back -> b * (255 - a)) ) >> 8;
            px_result -> a = ( (px_front -> a * a) + (px_back -> a * (255 - a)) ) >> 8;

            px_back++;
            px_front++;
            px_result++;
        }
    }
}
