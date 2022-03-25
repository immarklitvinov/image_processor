#include "negative_filter.h"

Image NegativeFilter::Apply(const Image &image) const {
    Image output(image.GetHeight(), image.GetWidth());
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel pixel = image.GetPixel(i, j);
            output.SetPixel(i, j, Pixel(255 - pixel.red_, 255 - pixel.green_, 255 - pixel.blue_));
        }
    }
    return output;
}
