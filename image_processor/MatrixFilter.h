#pragma once
#include "Filter.h"
#include <vector>
#include <cmath>
#include <numbers>
#include <algorithm>

class MatrixFilter : public Filter {

public:
    MatrixFilter(){}
    MatrixFilter(const std::vector<std::vector<int>>& matrix_new);
    virtual ~MatrixFilter(){};

protected:
    std::vector<std::vector<int>> matrix_;
    virtual void Apply(Image& image) override;

private:
    void Matrix(Image& image);
    void SetNewColour(std::vector<std::vector<Colour>>& image, const MulColour& colour, const size_t j, const size_t i);
    void ThreeSquareMatrix(Image& image);
};