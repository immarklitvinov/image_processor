#include "custom_exceptions.h"

const char* NoInputFilePath::what() const noexcept {
    return message_.c_str();
}

const char* NoOutputFilePath::what() const noexcept {
    return message_.c_str();
}

const char* NoAppliedFilters::what() const noexcept {
    return message_.c_str();
}

const char* WrongArgumentSyntax::what() const noexcept {
    return message_.c_str();
}

const char* WrongInputFilePath::what() const noexcept {
    return message_.c_str();
}

const char* WrongFileFormat::what() const noexcept {
    return message_.c_str();
}

const char* WrongBmpFormat::what() const noexcept {
    return message_.c_str();
}

const char *WrongAmountOfFilterArguments::what() const noexcept {
    return message_.c_str();
}

const char *WrongFilterName::what() const noexcept {
    return message_.c_str();
}
