#include "filter.h"

class CrystallizeAdvancedFilter : public Filter {
public:
    CrystallizeAdvancedFilter(const size_t& points_amount) : points_amount_(points_amount) {};
    Image Apply(const Image &image) const override;
private:
    size_t points_amount_;
};