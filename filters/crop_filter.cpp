#include "crop_filter.h"

CropFilter::CropFilter(const uint32_t &width, const uint32_t &height) {
    width_ = width;
    height_ = height;
}

Image CropFilter::Apply(const Image &image) const {

    Image output(height_, width_);
    size_t i_output = 0;
    for (size_t i = std::max(static_cast<int32_t>(image.GetHeight()) - static_cast<int32_t>(height_), 0); i < static_cast<int32_t>(image.GetHeight()); ++i) {
        size_t j_output = 0;
        for (size_t j = 0; j < std::min(static_cast<int32_t>(width_), static_cast<int32_t>(image.GetWidth())); ++j) {
            output.SetPixel(i_output, j_output, image.GetPixel(i, j));
            ++j_output;
        }
        ++i_output;
    }
    return output;
}
