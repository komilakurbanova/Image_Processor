#pragma once
#include "Filter.h"
#include <algorithm>
#include <iterator>

class Crop:public Filter {
    size_t width_;
    size_t height_;
public:
    Crop(size_t width, size_t height);
    virtual void Apply(Image& image) final;
    ~Crop();
};