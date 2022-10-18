#include "Image.h"

Image::Image(size_t width, size_t height) {
    width_ = width;
    height_ = height;
    colours_ = std::vector<std::vector<Colour>>(height_, std::vector<Colour>(width_));
}

Image::Image(std::vector<std::vector<Colour>>& image_matrix) {
    try {
        width_ = image_matrix[0].size();
        height_ = image_matrix.size();
        colours_ = image_matrix;
    } catch (...) {
        throw std::runtime_error("This image is empty");
    }
}


Colour Image::GetColour(size_t x, size_t y) const {
    return colours_[y][x];
}

void Image::SetColour(const Colour &colour_set, int x, int y) {
    colours_[y][x].r = colour_set.r;
    colours_[y][x].g = colour_set.g;
    colours_[y][x].b = colour_set.b;
}

Size Image::GetSize() const {
    Size image_size;
    image_size.height_of_image = height_;
    image_size.width_of_image = width_;
    return image_size;
}
std::vector<std::vector<Colour>> Image::GetMatrix() const {
    return colours_;
}