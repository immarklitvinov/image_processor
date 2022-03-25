#pragma once

#include "filters/crop_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/negative_filter.h"
#include "filters/matrix_filter.h"
#include "filters/sharp_filter.h"
#include "filters/edge_detection_filter.h"
#include "filters/gaussian_blur.h"
#include "filters/crystallize_filter.h"
#include "filters/crystallize_advanced_filter.h"
#include "custom_exceptions.h"

class FilterApplier {
public:
    FilterApplier(const std::vector<std::pair<std::string, std::vector<float>>>& arguments) : arguments_(arguments){};

    Image Apply(const Image& image);
private:
    std::vector<std::pair<std::string, std::vector<float>>> arguments_;
};