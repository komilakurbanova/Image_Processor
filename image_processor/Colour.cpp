#include "Colour.h"

MulColour::MulColour(int r_set, int g_set, int b_set) {
    r = r_set;
    g = g_set;
    b = b_set;
}
MulColour MulColour::operator+(const MulColour& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return MulColour(r, g, b);
}

void MulColour::operator+=(const MulColour& other){
    *this = *this + other;
}

Colour::Colour() {
    r = 0;
    g = 0;
    b = 0;
}

Colour::Colour(unsigned char r_set, unsigned char g_set, unsigned char b_set) {
    r = r_set;
    g = g_set;
    b = b_set;
}

Colour::Colour(const Colour& other) {
    r = other.r;
    g = other.g;
    b = other.b;
}

Colour::~Colour() {
}
MulColour Colour::operator*(int mul) {
    MulColour colour = MulColour(r*mul, g*mul, b*mul);
    return colour;
}
