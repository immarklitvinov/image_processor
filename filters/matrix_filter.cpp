#include <algorithm>
#include "matrix_filter.h"

MatrixFilter::MatrixFilter() {
    matrix_ = {{0}};
}

MatrixFilter::MatrixFilter(const std::vector<std::vector<float>>& matrix) {
    if (matrix.size() != matrix[0].size() || matrix.size() % 2 == 0) {
        matrix_ = {{0}};
    } else {
        matrix_ = matrix;
    }
}

Image MatrixFilter::Apply(const Image& image) const {
    uint32_t height = image.GetHeight();
    uint32_t width = image.GetWidth();
    int32_t radius = static_cast<int32_t>(matrix_.size() / 2 + 1);
    Image output(image.GetHeight(), image.GetWidth());
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            float red = 0;
            float green = 0;
            float blue = 0;
            for (int32_t delta_i = -radius + 1; delta_i != radius; ++delta_i) {
                for (int32_t delta_j = -radius + 1; delta_j != radius; ++delta_j) {
                    Pixel tmp_pixel = image.GetPixel(i + delta_i, j + delta_j);
                    float multiplier = matrix_[delta_i + radius - 1][delta_j + radius - 1];
                    red += tmp_pixel.red_ * multiplier;
                    green += tmp_pixel.green_ * multiplier;
                    blue += tmp_pixel.blue_ * multiplier;
                }
            }
            output.SetPixel(i, j, Pixel(red, green, blue));
        }
    }
    return output;
}
