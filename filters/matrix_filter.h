#include "filter.h"

class MatrixFilter : public Filter {
public:
    MatrixFilter();
    MatrixFilter(const std::vector<std::vector<float>>& matrix);
    Image Apply(const Image &image) const override;
private:
    std::vector<std::vector<float>> matrix_;
};
