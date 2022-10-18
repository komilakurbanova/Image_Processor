#include <catch.hpp>
#include "BmpInputOutput.h"
#include "MyFilter.h"


TEST_CASE("BMP_MY") {
    Image copy(0, 0);
    copy = BmpInputOutput::Read("../projects/image_processor/examples/example.bmp");
    Laplacian parameter = Laplacian();
    parameter.Apply(copy);
    BmpInputOutput::Export("../projects/image_processor/examples/example_laplacian.bmp", copy);
}



