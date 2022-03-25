#include "grayscale_filter.h"
#include <algorithm>

Image GrayscaleFilter::Apply(const Image &image) const {
    Image output(image.GetHeight(), image.GetWidth());
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel pixel = image.GetPixel(i, j);
            uint8_t tmp_color = static_cast<uint8_t>(std::clamp(0.299 * pixel.red_  + 0.587 * pixel.green_ + 0.114 * pixel.blue_, 0., 255.));
            output.SetPixel(i, j, Pixel(tmp_color, tmp_color, tmp_color));
        }
    }
    return output;
}
