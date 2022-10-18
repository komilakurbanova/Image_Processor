#include <catch.hpp>
#include "BmpInputOutput.h"
#include "EdgeDetection.h"

TEST_CASE("BMP_EDGE_DETECTION") {
    Image copy(0, 0);
    copy = BmpInputOutput::Read("../projects/image_processor/examples/example.bmp");
    auto copy1 = copy;

    EdgeDetection parameter = EdgeDetection(30);
    parameter.Apply(copy1);
    BmpInputOutput::Export("../projects/image_processor/examples/example_edge_30.bmp", copy1);

    parameter = EdgeDetection(100);
    parameter.Apply(copy);
    BmpInputOutput::Export("../projects/image_processor/examples/example_edge_100.bmp", copy);
}
