#include "MyFilter.h"


Laplacian::Laplacian() : MatrixFilter({{1, 1, 1}, {1, -8, 1}, {1, 1, 1}}){}

void Laplacian::Apply(Image& image_given) {
    MatrixFilter::Apply(image_given);
}
