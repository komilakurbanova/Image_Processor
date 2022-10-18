#include <catch.hpp>
#include "BmpInputOutput.h"
#include "Crop.h"

TEST_CASE("BMP_CROP") {
    Image copy(0, 0);
    Image copy1(0, 0);
    copy = BmpInputOutput::Read("../projects/image_processor/examples/example.bmp");
    copy1 = copy;
    Crop parameter = Crop(copy.GetSize().width_of_image, copy.GetSize().height_of_image);
    parameter.Apply(copy);
    for (int i = 0; i < copy.GetSize().height_of_image; ++i) {
        for (int j = 0; j < copy.GetSize().width_of_image; ++j) {
            REQUIRE(copy.GetColour(i, j).r == copy1.GetColour(i, j).r);
            REQUIRE(copy.GetColour(i, j).g == copy1.GetColour(i, j).g);
            REQUIRE(copy.GetColour(i, j).b == copy1.GetColour(i, j).b);
        }
    }
    parameter = Crop(200, 600);
    parameter.Apply(copy);
    REQUIRE(copy.GetSize().width_of_image == 200);
    REQUIRE(copy.GetSize().height_of_image == 600);

    parameter = Crop(2048, 500);
    parameter.Apply(copy);
    REQUIRE(copy.GetSize().width_of_image == 200);
    REQUIRE(copy.GetSize().height_of_image == 500);
}
