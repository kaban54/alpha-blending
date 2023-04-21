#ifndef ALPHA_H
#define ALPHA_H

#include "bmp.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <immintrin.h>

#ifndef REP_NUM
#define REP_NUM 1
#endif

const char font_file_name [] = "Minecraft-Regular.ttf";
const size_t BUFSIZE = 64;

void DrawAlpha (BmpImage *back_img, BmpImage *front_img);

void Blend (BmpImage *back_img, BmpImage *front_img, sf::Image &img);

#endif