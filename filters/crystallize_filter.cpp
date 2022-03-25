#include <random>
#include <cmath>
#include "crystallize_filter.h"

float Distance(size_t i, size_t j, size_t point_index, const std::vector<std::vector<size_t>>& points) {
    return std::hypot(static_cast<int32_t>(i) - static_cast<int32_t>(points[point_index][0]),
                      static_cast<int32_t>(j) - static_cast<int32_t>(points[point_index][1]));
}

Image CrystallizeFilter::Apply(const Image &image) const {
    std::vector<bool> wide_line(image.GetWidth() * image.GetHeight());
    for (size_t i = 0; i < points_amount_; ++i) {
        wide_line[i] = true;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(wide_line.begin(), wide_line.end(), g);

    std::vector<std::vector<size_t>> points(points_amount_, std::vector<size_t>(2));
    size_t inserted_amount = 0;
    for (size_t i = 0; i < wide_line.size(); ++i) {
        if (wide_line[i]) {
            points[inserted_amount] = {i / image.GetWidth(), i % image.GetWidth()};
            ++inserted_amount;
        }
    }

    Image output(image.GetHeight(), image.GetWidth());
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {

            std::pair<float, size_t> closest_point = std::make_pair(Distance(i, j, 0, points), 0);

            for (size_t k = 1; k < points_amount_; ++k) {
                float new_dist = Distance(i, j, k, points);
                if (new_dist < closest_point.first) {
                    closest_point = std::make_pair(new_dist, k);
                }
            }

            output.SetPixel(i, j, image.GetPixel(points[closest_point.second]));
        }
    }

    return output;
}

