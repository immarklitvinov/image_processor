cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_library(contrib_catch_main
        ../../contrib/catch/catch_main.cpp)

target_include_directories(contrib_catch_main
        PUBLIC ../../contrib/catch)

add_executable(image_processor
        image_processor.cpp
        image.cpp
        io/read_image.cpp
        io/write_image.cpp
        filters/filter.cpp
        filters/crop_filter.cpp
        filters/grayscale_filter.cpp
        filters/negative_filter.cpp
        filters/matrix_filter.cpp
        filters/sharp_filter.cpp
        filters/edge_detection_filter.cpp
        filters/gaussian_blur.cpp
        filters/crystallize_filter.cpp
        filters/crystallize_advanced_filter.cpp
        parser.cpp
        custom_exceptions.cpp
        filter_applier.cpp
        )
