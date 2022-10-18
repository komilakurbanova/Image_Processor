#pragma once
#include "BmpInputOutput.h"
#include "MatrixFilter.h"

class Sharpening : public MatrixFilter {
public:
    Sharpening();
    virtual void Apply(Image& image_given) final;
    virtual ~Sharpening(){};
};