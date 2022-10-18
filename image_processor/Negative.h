#pragma once
#include "BmpInputOutput.h"
#include "Filter.h"

class Negative : public Filter{
public:
    Negative(){};
    virtual void Apply(Image& image_given) final;
    virtual ~Negative(){};
};
