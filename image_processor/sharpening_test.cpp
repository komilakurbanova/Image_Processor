#include <catch.hpp>
#include "BmpInputOutput.h"
#include "Sharpening.h"

TEST_CASE("BMP_SHARPENING") {
    Image copy(0, 0);
    copy = BmpInputOutput::Read("../projects/image_processor/examples/example.bmp");
    Sharpening parameters = Sharpening();
    parameters.Apply(copy);
    BmpInputOutput::Export("../projects/image_processor/examples/example_sharpened.bmp", copy);
}