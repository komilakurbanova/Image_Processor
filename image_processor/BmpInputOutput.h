#pragma once
#include "Image.h"
#include <fstream>

const int FILE_H_SIZE = 14;
const int INF_H_SIZE = 40;
const int NUMBER_OF_COLOURS = 3;
const int BIT = 4;

template <typename T>
void IsOpened(T& f) {
    if (!f.is_open()) {
        throw std::runtime_error("\n Could not open the file");
    }
}

class BmpInputOutput {
public:
    static void Export(const char* path, const Image& image);
    static Image Read(const char* path);
};
