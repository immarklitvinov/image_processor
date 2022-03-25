#include <random>
#include <cmath>
#include "crystallize_advanced_filter.h"

float DistanceAdvanced(size_t i, size_t j, size_t point_index, const std::vector<std::vector<size_t>>& points) {
    return std::hypot(static_cast<int32_t>(i) - static_cast<int32_t>(points[point_index][0]),
                      static_cast<int32_t>(j) - static_cast<int32_t>(points[point_index][1]));
}

struct ClosestPoints {
    ClosestPoints(const size_t& i, const size_t& j, const std::vector<std::vector<size_t>>& points) {
        first_dist = DistanceAdvanced(i, j, 0, points);
        first_point_index = 0;
        second_dist = DistanceAdvanced(i, j, 1, points);
        second_point_index = 1;
        if (first_dist > second_dist) {
            std::swap(first_dist, second_dist);
            std::swap(first_point_index, second_point_index);
        }
    }

    void Swap() {
        std::swap(first_dist, second_dist);
        std::swap(first_point_index, second_point_index);
    }

    float first_dist;
    float second_dist;
    size_t first_point_index;
    size_t second_point_index;
};

Image CrystallizeAdvancedFilter::Apply(const Image &image) const {
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

            ClosestPoints closest_points(i, j, points);

            for (size_t k = 1; k < points_amount_; ++k) {
                float new_dist = DistanceAdvanced(i, j, k, points);
                if (new_dist < closest_points.first_dist) {
                    closest_points.Swap();
                    closest_points.first_dist = new_dist;
                    closest_points.first_point_index = k;
                } else if (new_dist < closest_points.second_dist) {
                    closest_points.second_dist = new_dist;
                    closest_points.second_point_index = k;
                }
            }
            Pixel pixel = image.GetPixel(points[closest_points.first_point_index]) *
                          (closest_points.first_dist / (closest_points.first_dist + closest_points.second_dist)) +
                          image.GetPixel(points[closest_points.second_point_index]) *
                          (closest_points.second_dist / (closest_points.first_dist + closest_points.second_dist));
            output.SetPixel(i, j, pixel);
        }
    }

    return output;
}
