#include <cmath>
#include "gaussian_blur.h"

Image GaussianBlur::Apply(const Image &image) const {
    int32_t matrix_size = static_cast<int32_t>(std::ceilf(6 * sigma_));
    if (matrix_size % 2 == 0) {
        matrix_size += 1;
    }
    std::vector<float> coefficients(matrix_size);
    double pi = std::atan(1) * 4;
    int32_t radius = matrix_size / 2;
    for (int32_t i = 0; i < matrix_size; ++i) {
        coefficients[i] = 1. / (std::sqrt(2 * pi * sigma_ * sigma_)) * std::exp(-(i - radius) * (i - radius) / (2 * sigma_ * sigma_));
    }

    uint32_t height = image.GetHeight();
    uint32_t width = image.GetWidth();
    Image output(image.GetHeight(), image.GetWidth());
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            float red = 0;
            float green = 0;
            float blue = 0;
            for (int32_t delta_i = -radius + 1; delta_i != radius; ++delta_i) {
                Pixel tmp_pixel = image.GetPixel(i + delta_i, j);
                float multiplier = coefficients[delta_i + radius - 1];
                red += tmp_pixel.red_ * multiplier;
                green += tmp_pixel.green_ * multiplier;
                blue += tmp_pixel.blue_ * multiplier;
            }
            output.SetPixel(i, j, Pixel(red, green, blue));
        }
    }
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            float red = 0;
            float green = 0;
            float blue = 0;
            for (int32_t delta_j = -radius + 1; delta_j != radius; ++delta_j) {
                Pixel tmp_pixel = output.GetPixel(i, j + delta_j);
                float multiplier = coefficients[delta_j + radius - 1];
                red += tmp_pixel.red_ * multiplier;
                green += tmp_pixel.green_ * multiplier;
                blue += tmp_pixel.blue_ * multiplier;
            }
            output.SetPixel(i, j, Pixel(red, green, blue));
        }
    }
    return output;
}