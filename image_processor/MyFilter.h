#pragma once
#include "BmpInputOutput.h"
#include "MatrixFilter.h"


class Laplacian : public MatrixFilter {
public:
    Laplacian();
    virtual void Apply(Image& image_given) final;
    virtual ~Laplacian(){};
};