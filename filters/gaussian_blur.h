#include "filter.h"

class GaussianBlur : public Filter {
public:
    GaussianBlur(const float& sigma) : sigma_(sigma) {};
    Image Apply(const Image &image) const override;
private:
    float sigma_;
};
