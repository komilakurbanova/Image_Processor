#include <catch.hpp>
#include "BmpInputOutput.h"
#include "GrayScale.h"
#include <math.h>


TEST_CASE("BMP_GRAY") {
    Image copy(0, 0);
    copy = BmpInputOutput::Read("../projects/image_processor/examples/example.bmp");
    Gray parameter = Gray();
    parameter.Apply(copy);
    BmpInputOutput::Export("../projects/image_processor/examples/example_gray.bmp", copy);

    copy = BmpInputOutput::Read("../projects/image_processor/examples/image.bmp");
    parameter.Apply(copy);
    Image web(0, 0);
    web = BmpInputOutput::Read("../projects/image_processor/examples/web_filter_grayscale.bmp");
    REQUIRE(copy.GetSize().width_of_image == web.GetSize().width_of_image);
    REQUIRE(copy.GetSize().height_of_image == web.GetSize().height_of_image);
    for (auto i = 0; i < copy.GetSize().height_of_image; ++i) {
        for (auto j = 0; j < copy.GetSize().width_of_image; ++j) {
            Colour c = copy.GetColour(j, i);
            Colour w = web.GetColour(j, i);
            REQUIRE(c.r == c.g);
            REQUIRE(c.r == c.b);
            REQUIRE(c.b == c.g);
            REQUIRE(w.r == w.g);
            REQUIRE(w.r == w.b);
            REQUIRE(w.b == w.g);
            REQUIRE(std::abs(c.r - w.r) < 2);
        }
    }
}