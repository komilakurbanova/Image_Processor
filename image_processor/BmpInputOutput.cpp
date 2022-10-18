#include "BmpInputOutput.h"
#include <iostream>
#include <stdexcept>

void IsBMP(unsigned char *file_header, std::ifstream &f) {
    if (file_header[0] != 'B' || file_header[1] != 'M') {
        f.close();
        throw std::runtime_error("\n The file is not a .bmp");
    }
}

void BmpInputOutput::Export(const char *path, const Image &image) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    try {
        IsOpened(f);
    } catch (std::runtime_error &error) {
        throw error;
    }
    size_t image_width = image.GetSize().width_of_image;
    size_t image_height = image.GetSize().height_of_image;
    unsigned char bmp_pad[NUMBER_OF_COLOURS] = {0, 0, 0};
    const int padding = (BIT - (NUMBER_OF_COLOURS * image_width) % BIT) % BIT;
    const int file_header_size = FILE_H_SIZE;
    const int information_header_size = INF_H_SIZE;
    const int file_size = file_header_size + information_header_size + NUMBER_OF_COLOURS * image_width * image_height +
                          padding * image_height;

    unsigned char file_header[file_header_size];

    for (int i = 0; i < FILE_H_SIZE; ++i) {
        file_header[i] = 0;
    }
    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;
    file_header[3] = file_size >> 2 * BIT;
    file_header[4] = file_size >> 4 * BIT;
    file_header[5] = file_size >> 6 * BIT;
    file_header[10] = file_header_size + information_header_size;

    unsigned char information_header[information_header_size];
    for (int i = 0; i < INF_H_SIZE; ++i) {
        information_header[i] = 0;
    }
    information_header[0] = information_header_size;
    information_header[4] = image_width;
    information_header[5] = image_width >> 2 * BIT;
    information_header[6] = image_width >> 4 * BIT;
    information_header[7] = image_width >> 6 * BIT;
    information_header[8] = image_height;
    information_header[9] = image_height >> 2 * BIT;
    information_header[10] = image_height >> 4 * BIT;
    information_header[11] = image_height >> 6 * BIT;
    information_header[12] = 1;
    information_header[14] = 6 * BIT;

    f.write(reinterpret_cast<char *>(file_header), file_header_size);
    f.write(reinterpret_cast<char *>(information_header), information_header_size);

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            unsigned char r = image.GetColour(i, j).r;
            unsigned char g = image.GetColour(i, j).g;
            unsigned char b = image.GetColour(i, j).b;
            unsigned char colour[] = {b, g, r};
            f.write(reinterpret_cast<char *>(colour), NUMBER_OF_COLOURS);
        }
        f.write(reinterpret_cast<char *>(bmp_pad), padding);
    }
    f.close();
}

Image BmpInputOutput::Read(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    try {
        IsOpened(f);
    } catch (std::runtime_error &error) {
        throw error;
    }
    const size_t file_header_size = FILE_H_SIZE;
    const size_t information_header_size = INF_H_SIZE;
    unsigned char file_header[file_header_size];
    f.read(reinterpret_cast<char *>(file_header), file_header_size);
    try {
        IsBMP(file_header, f);
    } catch (std::runtime_error &error) {
        throw error;
    }
    unsigned char information_header[information_header_size];
    f.read(reinterpret_cast<char *>(information_header), information_header_size);
    int width = information_header[4] + (information_header[5] << 2 * BIT) + (information_header[6] << 4 * BIT) +
                (information_header[7] << 6 * BIT);
    int height = information_header[8] + (information_header[9] << 2 * BIT) + (information_header[10] << 4 * BIT) +
                 (information_header[11] << 6 * BIT);
    const int padding = (BIT - (NUMBER_OF_COLOURS * width) % BIT) % BIT;
    Image image = Image(width, height);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            unsigned char colour[NUMBER_OF_COLOURS];
            f.read(reinterpret_cast<char *>(colour), NUMBER_OF_COLOURS);
            Colour colour_tmp;
            colour_tmp.b = colour[0];
            colour_tmp.g = colour[1];
            colour_tmp.r = colour[2];
            image.SetColour(colour_tmp, i, j);
        }
        f.ignore(padding);
    }
    f.close();
    return image;
}