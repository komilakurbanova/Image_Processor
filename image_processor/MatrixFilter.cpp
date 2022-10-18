#include "MatrixFilter.h"

MatrixFilter::MatrixFilter(const std::vector<std::vector<int>>& matrix_new) {
    matrix_ = matrix_new;
}

void MatrixFilter::Apply(Image& image) {
    Matrix(image);
}

void MatrixFilter::Matrix(Image& image) {
    if (matrix_.size() == 3 && matrix_[0].size() == 3) {
        ThreeSquareMatrix(image);
    }
}
void MatrixFilter::SetNewColour(std::vector<std::vector<Colour>>& image, const MulColour& colour, const size_t j,
                                const size_t i) {
    unsigned char r_new = static_cast<unsigned char>(std::min(UCHAR_MAX, std::max(colour.r, 0)));
    unsigned char g_new = static_cast<unsigned char>(std::min(UCHAR_MAX, std::max(colour.g, 0)));
    unsigned char b_new = static_cast<unsigned char>(std::min(UCHAR_MAX, std::max(colour.b, 0)));
    Colour new_colour = Colour(r_new, g_new, b_new);
    image[i][j] = new_colour;
}

void MatrixFilter::ThreeSquareMatrix(Image& image) {
    size_t width = image.GetSize().width_of_image;
    size_t height = image.GetSize().height_of_image;
    std::vector<std::vector<Colour>> vector_copy;
    Colour c = Colour();

    vector_copy.reserve(height + 2);
    vector_copy.push_back(std::vector<Colour>(width + 2, c));
    std::vector<Colour> tmp = {c};
    tmp.reserve(width + 2);
    for (auto i = 0; i < height; ++i) {
        tmp = {c};
        for (auto j = 0; j < width; ++j) {
            tmp.push_back(image.GetColour(j, i));
        }
        tmp.push_back(c);
        vector_copy.push_back(tmp);
    }
    vector_copy.push_back(std::vector<Colour>(width + 2, c));

    for (auto i = 1; i < width + 1; ++i) {
        vector_copy[0][i] = image.GetColour(i - 1, 0);
        vector_copy[height + 1][i] = image.GetColour(i - 1, height - 1);
    }
    for (auto i = 1; i < height + 1; ++i) {
        vector_copy[i][0] = image.GetColour(0, i - 1);
        vector_copy[i][width + 1] = image.GetColour(width - 1, i - 1);
    }
    vector_copy[0][0] = image.GetColour(0, 0);
    vector_copy[0][width + 1] = image.GetColour(width - 1, 0);
    vector_copy[height + 1][0] = image.GetColour(0, height - 1);
    vector_copy[height + 1][width + 1] = image.GetColour(width - 1, height - 1);

    std::vector<std::vector<Colour>> vector_new(height + 2, std::vector<Colour>(width + 2, c));
    for (auto y = 1; y < height + 1; ++y) {
        for (auto x = 1; x < width + 1; ++x) {
            MulColour colour_mul = MulColour(0, 0, 0);
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    colour_mul += vector_copy[y + i][x + j] * matrix_[1 + i][1 + j];
                }
            }
            SetNewColour(vector_new, colour_mul, x, y);
        }
    }
    std::vector<std::vector<Colour>> vector_cropped;
    vector_cropped.reserve(height);
    for (auto y = 1; y < height + 1; ++y) {
        tmp.clear();
        for (auto x = 1; x < width + 1; ++x) {
            tmp.push_back(vector_new[y][x]);
        }
        vector_cropped.push_back(tmp);
    }
    image = Image(vector_cropped);
}
