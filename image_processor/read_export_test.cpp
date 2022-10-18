#include <catch.hpp>
#include "BmpInputOutput.h"
#include <iostream>

TEST_CASE("BMP_COPY") {
    Image copy(0, 0);
    copy = BmpInputOutput::Read("../projects/image_processor/examples/example.bmp");
    BmpInputOutput::Export("../projects/image_processor/examples/copy.bmp", copy);
    Image copy1(0, 0);
    copy1 = BmpInputOutput::Read("../projects/image_processor/examples/copy.bmp");
    int a = 0;
    for (int i = 0; i < copy.GetSize().height_of_image; ++i) {
        for (int j = 0; j < copy.GetSize().width_of_image; ++j) {
            ++a;
            REQUIRE(copy.GetColour(i, j).r == copy1.GetColour(i, j).r);
            REQUIRE(copy.GetColour(i, j).g == copy1.GetColour(i, j).g);
            REQUIRE(copy.GetColour(i, j).b == copy1.GetColour(i, j).b);
        }
    }
}

TEST_CASE("ExceptionOpen") {
    Image copy(0, 0);
    try {
        copy = BmpInputOutput::Read("../projects/image_processor/examples/non_exist_file.bmp");
        throw std::runtime_error("Impossible expression");
    } catch (std::runtime_error& error) {
        REQUIRE(strcmp(error.what(), "Impossible expression") != 0);
        REQUIRE(strcmp(error.what(), "\n Could not open the file") == 0);
    }
}

TEST_CASE("ExceptionNotBMP") {
    Image copy(0, 0);
    try {
        copy = BmpInputOutput::Read("../projects/image_processor/examples/non-bmp_file.jpeg");
        throw std::runtime_error("Impossible expression");
    } catch (std::runtime_error& error) {
        REQUIRE(strcmp(error.what(), "Impossible expression") != 0);
        REQUIRE(strcmp(error.what(), "\n The file is not a .bmp") == 0);
    }
}