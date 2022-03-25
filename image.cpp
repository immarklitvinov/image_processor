#include <cmath>
#include <algorithm>
#include "image.h"

Pixel Pixel::operator*(const int32_t& multiplier) const {
    return Pixel(red_ * multiplier, green_ * multiplier, blue_ * multiplier);
}

Pixel& Pixel::operator+=(const Pixel &other) {
    red_ = std::clamp(red_ + other.red_, 0, 255);
    green_ = std::clamp(green_ + other.green_, 0, 255);
    blue_ = std::clamp(blue_ + other.blue_, 0, 255);
    return *this;
}

Pixel Pixel::operator+(const Pixel& other) {
    return *this += other;
}

const uint32_t& Image::GetSize() const {
    return this->size_;
}

const uint32_t& Image::GetHeight() const {
    return this->height_;
}

const uint32_t& Image::GetWidth() const {
    return this->width_;
}

const Pixel& Image::GetPixel(const int32_t& y, const int32_t& x) const {
    return this->pixels_.at(static_cast<size_t>(std::clamp(y, 0, static_cast<int32_t>(height_) - 1))).at(
            static_cast<size_t>(std::clamp(x, 0, static_cast<int32_t>(width_) - 1))
    );
}

const Pixel &Image::GetPixel(const std::vector<size_t>& point_coordinates) const {
    return this->GetPixel(point_coordinates[0], point_coordinates[1]);
}

void Image::SetPixel(const size_t& y, const size_t& x, Pixel pixel) {
    pixels_[y][x] = pixel;
}
