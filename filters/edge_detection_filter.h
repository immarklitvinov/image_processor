#include "filter.h"

class EdgeDetectionFilter : public Filter{
public:
    EdgeDetectionFilter(const int32_t& threshold) : threshold_(threshold) {};
    Image Apply(const Image &image) const override;
private:
    int32_t threshold_;
};