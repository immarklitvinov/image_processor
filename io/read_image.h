#pragma once

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <algorithm>

#include "../image.h"

void Skip(std::ifstream &input, int32_t bytes_amount);

Image ReadImage(const std::string& path);
