#include "filter_applier.h"

Image FilterApplier::Apply(const Image& image) {
    Image output(image);
    for (const auto& [filter_name, filter_args] : arguments_) {
        if (filter_name == "-crop") {
            if (filter_args.size() != static_cast<size_t>(2)) {
                throw WrongAmountOfFilterArguments(filter_name, 2);
            }
            CropFilter filter(static_cast<int32_t>(filter_args[0]), static_cast<int32_t>(filter_args[0]));
            output = filter.Apply(output);
        } else if (filter_name == "-crystallize_advanced") {
            if (filter_args.size() != static_cast<size_t>(1)) {
                throw WrongAmountOfFilterArguments(filter_name, 1);
            }
            CrystallizeAdvancedFilter filter(static_cast<int32_t>(filter_args[0]));
            output = filter.Apply(output);
        } else if (filter_name == "-crystallize") {
            if (filter_args.size() != static_cast<size_t>(1)) {
                throw WrongAmountOfFilterArguments(filter_name, 1);
            }
            CrystallizeFilter filter(static_cast<int32_t>(filter_args[0]));
            output = filter.Apply(output);
        } else if (filter_name == "-edge") {
            if (filter_args.size() != static_cast<size_t>(1)) {
                throw WrongAmountOfFilterArguments(filter_name, 1);
            }
            EdgeDetectionFilter filter(static_cast<int32_t>(filter_args[0]));
            output = filter.Apply(output);
        } else if (filter_name == "-blur") {
            if (filter_args.size() != static_cast<size_t>(1)) {
                throw WrongAmountOfFilterArguments(filter_name, 1);
            }
            GaussianBlur filter(filter_args[0]);
            output = filter.Apply(output);
        } else if (filter_name == "-gs") {
            if (filter_args.size() != static_cast<size_t>(0)) {
                throw WrongAmountOfFilterArguments(filter_name, 0);
            }
            GrayscaleFilter filter;
            output = filter.Apply(output);
        } else if (filter_name == "-neg") {
            if (filter_args.size() != static_cast<size_t>(0)) {
                throw WrongAmountOfFilterArguments(filter_name, 0);
            }
            NegativeFilter filter;
            output = filter.Apply(output);
        } else if (filter_name == "-sharp") {
            if (filter_args.size() != static_cast<size_t>(0)) {
                throw WrongAmountOfFilterArguments(filter_name, 0);
            }
            SharpFilter filter;
            output = filter.Apply(output);
        } else {
            throw WrongFilterName(filter_name);
        }
    }
    return output;
}
