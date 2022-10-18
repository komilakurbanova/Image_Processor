#pragma once
#include "BmpInputOutput.h"
#include "MatrixFilter.h"
#include "GrayScale.h"

class EdgeDetection : public MatrixFilter {
    unsigned char threshold_;
public:
    EdgeDetection(unsigned char threshold);
    virtual void Apply(Image& image_given) final;
    virtual ~EdgeDetection(){};
};