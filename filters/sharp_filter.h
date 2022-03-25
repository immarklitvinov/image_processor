#include "filter.h"

class SharpFilter : public Filter{
public:
    SharpFilter() {};
    Image Apply(const Image &image) const override;
};