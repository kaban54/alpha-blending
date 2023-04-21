#include "alpha.h"


const __m256i ALPHA_MASK = _mm256_set_epi8 (0x80, 30, 0x80, 30, 0x80, 30, 0x80, 30,
                                            0x80, 22, 0x80, 22, 0x80, 22, 0x80, 22,
                                            0x80, 14, 0x80, 14, 0x80, 14, 0x80, 14,
                                            0x80,  6, 0x80,  6, 0x80,  6, 0x80,  6);

const __m256i HI_MASK = _mm256_set_epi8 (  31,   29,   27,   25,   23,   21,   19,   17, 
                                         0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                                           15,   13,   11,    9,    7,    5,    3,    1, 
                                         0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80);

const __m256i LO_MASK = _mm256_set_epi8 (0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
                                           31,   29,   27,   25,   23,   21,   19,   17, 
                                         0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                                           15,   13,   11,    9,    7,    5,    3,    1);

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
        for (int x = 0; x < w; x += 8)
        {
            __m256i res = _mm256_setzero_si256 ();

            for (int rep = 0; rep < REP_NUM; rep++)
            {
                __m256i front = _mm256_loadu_si256((__m256i *) (px_front + y * w + x));
                __m256i back  = _mm256_loadu_si256((__m256i *) (px_back  + y * w + x));

                __m256i front_hi = _mm256_unpackhi_epi8 (front, _mm256_setzero_si256 ());
                __m256i back_hi  = _mm256_unpackhi_epi8 (back , _mm256_setzero_si256 ());

                __m256i front_lo = _mm256_unpacklo_epi8 (front, _mm256_setzero_si256 ());
                __m256i back_lo  = _mm256_unpacklo_epi8 (back , _mm256_setzero_si256 ());

                __m256i alpha_hi = _mm256_shuffle_epi8 (front_hi, ALPHA_MASK);
                __m256i alpha_lo = _mm256_shuffle_epi8 (front_lo, ALPHA_MASK);

                front_hi = _mm256_mullo_epi16 (front_hi, alpha_hi);
                front_lo = _mm256_mullo_epi16 (front_lo, alpha_lo);

                alpha_hi = _mm256_sub_epi16 (_mm256_set1_epi16 (0xff), alpha_hi);
                alpha_lo = _mm256_sub_epi16 (_mm256_set1_epi16 (0xff), alpha_lo);

                back_hi = _mm256_mullo_epi16 (back_hi, alpha_hi);
                back_lo = _mm256_mullo_epi16 (back_lo, alpha_lo);

                back_hi = _mm256_add_epi8 (back_hi, front_hi);
                back_lo = _mm256_add_epi8 (back_lo, front_lo);

                back_hi = _mm256_shuffle_epi8 (back_hi, HI_MASK);
                back_lo = _mm256_shuffle_epi8 (back_lo, LO_MASK);

                res = _mm256_add_epi8 (back_hi, back_lo);
            }

            for (int i = 0; i < 8; i++)
            {
                RGBA *px = ((RGBA *) &res) + i;
                img.setPixel (x + i, h - y, sf::Color (px -> r, px -> g, px -> b));
            }
        }
    }
}
