#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

#include "custom_exceptions.h"

using Parameters = std::vector<std::pair<std::string, std::vector<float>>>;

Parameters ParseCmdLine(int argc, const char* argv[]);

class Parser {
public:
    Parser(int argc, const char* argv[]) : argc_(argc), argv_(argv) {};
    Parameters ParseLine();

private:
    int pos_ = 1;
    const int argc_ = 0;
    const char** argv_;
};
