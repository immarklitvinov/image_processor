#include "sharp_filter.h"
#include "matrix_filter.h"

Image SharpFilter::Apply(const Image &image) const {
    MatrixFilter filter({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}});
    return filter.Apply(image);
}
