#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <queue>
#include "BmpInputOutput.h"
#include "Crop.h"
#include "EdgeDetection.h"
#include "Gaussian.h"
#include "GrayScale.h"
#include "MyFilter.h"
#include "Negative.h"
#include "Sharpening.h"

struct Parameters {
    std::string name;
    unsigned char p_threshold;
    size_t p_width;
    size_t p_height;
    double p_sigma;
    Parameters(const std::string n, const unsigned char t);
    Parameters(const std::string n, const size_t w, const size_t h);
    Parameters(const std::string n, const float s);
    Parameters(const std::string n);
};
