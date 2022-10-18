#pragma once
#include "Colour.h"
#include <vector>
#include <string_view>

struct Size {
    size_t width_of_image;
    size_t height_of_image;
};

class Image {
private:
    size_t width_;
    size_t height_;
    std::vector<std::vector<Colour>> colours_;

public:
    Image(size_t width, size_t height);
    Image(std::vector<std::vector<Colour>>& image_matrix);

    Colour GetColour(size_t x, size_t y) const;
    void SetColour(const Colour &colour_set, int x, int y);
    Size GetSize() const;
    std::vector<std::vector<Colour>> GetMatrix() const;
};
