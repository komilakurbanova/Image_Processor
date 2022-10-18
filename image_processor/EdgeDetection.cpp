#include "EdgeDetection.h"

EdgeDetection::EdgeDetection(unsigned char threshold) : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}) {
    threshold_ = threshold;
}

void EdgeDetection::Apply(Image& image_given) {
    Gray().Gray::Apply(image_given);
    MatrixFilter::Apply(image_given);
    Colour white = Colour(UCHAR_MAX, UCHAR_MAX, UCHAR_MAX);
    Colour black = Colour(0, 0, 0);
    for (auto i = 0; i < image_given.GetSize().height_of_image; ++i) {
        for (auto j = 0; j < image_given.GetSize().width_of_image; ++j) {
            if (image_given.GetColour(j, i).r > threshold_) {
                image_given.SetColour(white, j, i);
            } else {
                image_given.SetColour(black, j, i);
            }
        }
    }
}
