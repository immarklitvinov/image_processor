#pragma once

#include <iostream>
#include <fstream>
#include <string>

class NoInputFilePath : public std::exception {
public:
    NoInputFilePath() {};

    const char* what() const noexcept override;
private:
    std::string message_ = "No input file path.";
};

class NoOutputFilePath : public std::exception {
public:
    NoOutputFilePath() {};

    const char* what() const noexcept override;
private:
    std::string message_ = "No output file path.";
};

class NoAppliedFilters : public std::exception {
public:
    NoAppliedFilters() {};

    const char* what() const noexcept override;
private:
    std::string message_ = "No filters applied.";
};

class WrongArgumentSyntax : public std::exception {
public:
    WrongArgumentSyntax() {};

    const char* what() const noexcept override;
private:
    std::string message_ = "Wrong argument syntax: probably you forgot '-' before the filter name .";
};

class WrongInputFilePath : public std::exception {
public:
    WrongInputFilePath() : message_("No such file at that path.") {};

    const char* what() const noexcept override;
private:
    std::string message_;
};

class WrongFileFormat : public std::exception {
public:
    WrongFileFormat() {};

    const char* what() const noexcept override;
private:
    std::string message_ = "The input file has wrong type (.bmp file expected).";
};

class WrongBmpFormat : public std::exception {
public:
    WrongBmpFormat() {};

    const char* what() const noexcept override;
private:
    std::string message_ = "The BMP file has wrong format (24-bit-per-pixel expected).";
};

class WrongAmountOfFilterArguments : public std::exception {
public:
    WrongAmountOfFilterArguments(const std::string& filter_type, const int32_t& required_amount) : message_(
            "The filter " + filter_type + " requires " + std::to_string(required_amount) + " arguments."
            ) {};

    const char* what() const noexcept override;
private:
    std::string message_;
};

class WrongFilterName : public std::exception {
public:
    WrongFilterName(const std::string& string) : message_(
            "No such filter: " + string + ". Have a look at the info.") {};

    const char* what() const noexcept override;
private:
    std::string message_;
};