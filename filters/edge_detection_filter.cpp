#include "edge_detection_filter.h"
#include "matrix_filter.h"
#include "grayscale_filter.h"

Image EdgeDetectionFilter::Apply(const Image &image) const {
    GrayscaleFilter filter1;
    MatrixFilter filter2({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}});
    Image output = filter1.Apply(image);
    output = filter2.Apply(output);
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (output.GetPixel(i, j).red_ > threshold_) {
                output.SetPixel(i, j, Pixel(255, 255, 255));
            } else {
                output.SetPixel(i, j, Pixel());
            }
        }
    }
    return output;
}
