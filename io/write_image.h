#pragma once

#include <wchar.h>
#include <iostream>
#include <stdio.h>
#include <fstream>

#include "../image.h"


namespace bmp_const {
    const uint16_t COLOR_PLANES = 1;
    const uint16_t BITS_PER_PIXEL = 24;
    const uint32_t RAW_BITMAP_DATA = 16;
    const uint32_t DPI_NUMBER = 2835;
    const uint32_t OFFSET = 54;
    const uint32_t HEADER_LENGTH = 40;
}

void Skip(std::ofstream &output, int32_t bytes_amount);

void WriteImage(const Image& image, const std::string& path);
