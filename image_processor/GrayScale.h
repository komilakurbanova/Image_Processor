#pragma once
#include "BmpInputOutput.h"
#include "Filter.h"

class Gray : public Filter{
private:
    static void MakeGray(Colour& colour_new, Colour colour_given);
public:
    Gray(){};
    virtual void Apply(Image& image_given) final;
    virtual ~Gray(){};
};