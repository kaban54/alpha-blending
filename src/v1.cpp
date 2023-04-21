#include "alpha.h"

void Blend (BmpImage *back_img, BmpImage *front_img, sf::Image &img)
{
    RGBA *px_back  =  back_img -> pixels;
    RGBA *px_front = front_img -> pixels;

    int w = back_img -> width;
    int h = back_img -> height;

    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 0;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            for (int rep = 0; rep < REP_NUM; rep++)
            {
                a = px_front -> a;
                r = ( (px_front -> r * a) + (px_back -> r * (255 - a)) ) >> 8;
                g = ( (px_front -> g * a) + (px_back -> g * (255 - a)) ) >> 8;
                b = ( (px_front -> b * a) + (px_back -> b * (255 - a)) ) >> 8;
            }

            img.setPixel (x, h - y, sf::Color (r, g, b));

            px_back++;
            px_front++;
        }
    }
}
