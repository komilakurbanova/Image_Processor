#include "Crop.h"

Crop::Crop(size_t width, size_t height) {
    width_ = width;
    height_ = height;
}

void Crop::Apply(Image& image_given) {
    size_t width_given = image_given.GetSize().width_of_image;
    size_t height_given = image_given.GetSize().height_of_image;
    size_t width_new = std::min(image_given.GetSize().width_of_image, width_);
    size_t height_new = std::min(height_given, height_);
    if (height_given == height_new && width_given == width_new) {
        return;
    }
    std::vector<std::vector<Colour>> image_matrix = image_given.GetMatrix();
    std::vector<std::vector<Colour>> matrix_new;
    for (auto i=0; i<width_new; ++i) {
        image_matrix[i].resize(width_new);
    }
    for (auto i=0; i<height_new; ++i) {
        image_matrix[height_given - i - 1].resize(width_new);
        matrix_new.push_back(image_matrix[height_given - i - 1]);
    }
    std::reverse(matrix_new.begin(), matrix_new.end());
    image_given = Image(matrix_new);
}
Crop::~Crop() {
    width_ = 0;
    height_ = 0;
}
