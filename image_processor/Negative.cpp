#include "Negative.h"


void Negative::Apply(Image& image_given) {
    for (size_t j = 0; j < image_given.GetSize().height_of_image; ++j) {
        for (size_t i = 0; i < image_given.GetSize().width_of_image; ++i) {
            Colour c = image_given.GetColour(i, j);
            Colour colour_tmp(UCHAR_MAX - c.r, UCHAR_MAX - c.g, UCHAR_MAX - c.b);
            image_given.SetColour(colour_tmp, i, j);
        }
    }
}
