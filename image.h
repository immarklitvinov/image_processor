#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <cstdint>

#include "custom_exceptions.h"

template<typename T>
size_t PaddingLength(const T& width) {
    return (4 - (3 * static_cast<int32_t>(width)) % 4) % 4;
}

struct Pixel {
    Pixel() : red_(0), green_(0), blue_(0) {};

    template<typename T>
    Pixel(T r, T g, T b) {
        red_ = static_cast<uint8_t>(std::clamp(static_cast<int32_t>(std::round(r)), 0, 255));
        green_ = static_cast<uint8_t>(std::clamp(static_cast<int32_t>(std::round(g)), 0, 255));
        blue_ = static_cast<uint8_t>(std::clamp(static_cast<int32_t>(std::round(b)), 0, 255));
    }

    template<typename T>
    Pixel operator*(const T& multiplier) const {
        return Pixel(red_ * multiplier, green_ * multiplier, blue_ * multiplier);
    }

    template<typename T>
    Pixel operator*(const T& multiplier) {
        return Pixel(red_ * multiplier, green_ * multiplier, blue_ * multiplier);
    }

    Pixel operator+(const Pixel& other);
    Pixel operator*(const int32_t& multiplier) const;
    Pixel& operator+=(const Pixel& other);

    uint8_t red_ = 0;
    uint8_t green_ = 0;
    uint8_t blue_ = 0;
};

class Image {
public:
    Image() : height_(0), width_(0), size_(54) {};

    template<typename T>
    Image(T height, T width) {
        height_ = static_cast<uint32_t>(height);
        width_ = static_cast<uint32_t>(width);
        pixels_ = std::vector<std::vector<Pixel>> (height_, std::vector<Pixel>(width_));
        size_ = 54 + static_cast<uint32_t>(height) * (static_cast<uint32_t>(width) * 3 + 4 - (static_cast<uint32_t>(width) * 3) % 4);
    }

    const uint32_t& GetSize() const;
    const uint32_t& GetHeight() const;
    const uint32_t& GetWidth() const;
    const Pixel& GetPixel(const int32_t& y, const int32_t& x) const;
    const Pixel& GetPixel(const std::vector<size_t>& point_coordinates) const;
    void SetPixel(const size_t& y, const size_t& x, Pixel pixel);

private:
    uint32_t height_ = 0;
    uint32_t width_ = 0;
    uint32_t size_ = 54;
    std::vector<std::vector<Pixel>> pixels_;
};
