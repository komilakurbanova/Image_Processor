#include "GrayScale.h"
#include <cmath>


void Gray::MakeGray(Colour& colour_new, Colour colour_given) {
    unsigned char tmp_colour =
        static_cast<unsigned char>(std::round(0.299 * colour_given.r + 0.587 * colour_given.g + 0.114 * colour_given.b));
    colour_new.r = tmp_colour;
    colour_new.g = tmp_colour;
    colour_new.b = tmp_colour;
}

void Gray::Apply(Image& image_given) {
    for (size_t j = 0; j < image_given.GetSize().height_of_image; ++j) {
        for (size_t i = 0; i < image_given.GetSize().width_of_image; ++i) {
            Colour colour_tmp = Colour();
            MakeGray(colour_tmp, image_given.GetColour(i, j));
            image_given.SetColour(colour_tmp, i, j);
        }
    }
}