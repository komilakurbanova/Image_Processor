#pragma once
#include "BmpInputOutput.h"

class Filter {
public:
    virtual void Apply(Image& image) = 0;
};