#include <catch.hpp>
#include "BmpInputOutput.h"
#include "Negative.h"

TEST_CASE("BMP_NEGATIVE") {
    Image copy(0, 0);
    copy = BmpInputOutput::Read("../projects/image_processor/examples/example.bmp");
    Negative parameter = Negative();
    parameter.Apply(copy);
    BmpInputOutput::Export("../projects/image_processor/examples/example_negative.bmp", copy);

    copy = BmpInputOutput::Read("../projects/image_processor/examples/image.bmp");
    parameter.Apply(copy);
    Image web(0, 0);
    web = BmpInputOutput::Read("../projects/image_processor/examples/web_filter_negative.bmp");
    REQUIRE(copy.GetSize().width_of_image == web.GetSize().width_of_image);
    REQUIRE(copy.GetSize().height_of_image == web.GetSize().height_of_image);
    for (auto i = 0; i < copy.GetSize().height_of_image; ++i) {
        for (auto j = 0; j < copy.GetSize().width_of_image; ++j) {
            Colour c = copy.GetColour(j, i);
            Colour w = web.GetColour(j, i);
            REQUIRE(c.r == w.r);
            REQUIRE(c.g == w.g);
            REQUIRE(c.b == w.b);
        }
    }
}