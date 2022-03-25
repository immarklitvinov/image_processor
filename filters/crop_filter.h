#include "filter.h"

class CropFilter : public Filter {
public:
    CropFilter(const uint32_t& width, const uint32_t& height);

    Image Apply(const Image& image) const override;

private:
    uint32_t width_;
    uint32_t height_;
};