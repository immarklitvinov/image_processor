#include "write_image.h"

template<typename T>
void Write(std::ofstream &output, T &variable) {
    output.write(reinterpret_cast<const char *>(&variable), sizeof(variable));
}

void Skip(std::ofstream &output, int32_t bytes_amount) {
    for (size_t i = 0; i < bytes_amount; ++i) {
        output.write("\0", 1);
    }
}

void WriteImage(const Image &image, const std::string& path) {
    std::ofstream output(path, std::ios::out | std::ios::binary);

    if (output.is_open()) {
        output.write("BM", 2);
        Write(output, image.GetSize());
        Skip(output, 4);
        Write(output, bmp_const::OFFSET);
        Write(output, bmp_const::HEADER_LENGTH);
        Write(output, image.GetWidth());
        Write(output, image.GetHeight());
        Write(output, bmp_const::COLOR_PLANES);
        Write(output, bmp_const::BITS_PER_PIXEL);
        Skip(output, 4);
        Write(output, bmp_const::RAW_BITMAP_DATA);
        Write(output, bmp_const::DPI_NUMBER);
        Write(output, bmp_const::DPI_NUMBER);
        Skip(output, 8);

        size_t padding_length = PaddingLength(image.GetWidth());
        for (size_t i = 0; i < image.GetHeight(); ++i) {
            for (size_t j = 0; j < image.GetWidth(); ++j) {
                const Pixel& pixel = image.GetPixel(i, j);
                Write(output, pixel.blue_);
                Write(output, pixel.green_);
                Write(output, pixel.red_);
            }
            Skip(output, padding_length);
        }
    }
    output.close();
}