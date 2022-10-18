#include "image_processor.h"

Parameters::Parameters(const std::string n, const unsigned char t) {
    name = n;
    p_threshold = t;
    p_width = 0;
    p_height = 0;
    p_sigma = 0;
}
Parameters::Parameters(const std::string n, const size_t w, const size_t h) {
    name = n;
    p_threshold = 0;
    p_width = w;
    p_height = h;
    p_sigma = 0;
}
Parameters::Parameters(const std::string n, const float s) {
    name = n;
    p_threshold = 0;
    p_width = 0;
    p_height = 0;
    p_sigma = s;
}
Parameters::Parameters(const std::string n) {
    name = n;
    p_threshold = 0;
    p_width = 0;
    p_height = 0;
    p_sigma = 0;
}

Size ArgCrop(int argc, char** argv, const size_t i) {
    if (i == argc - 1 || i == argc - 2) {
        throw std::runtime_error("\n Not enough parameter to crop");
    }
    int crop_width;
    int crop_height;
    std::string string_width = argv[i + 1];
    for (char el : string_width) {
        if (!isdigit(el)) {
            throw std::runtime_error("\n Width must be a natural number to crop");
        }
    }
    crop_width = std::stoi(string_width);
    if (crop_width <= 0) {
        throw std::runtime_error("\n Width must be a natural number to crop");
    }
    std::string string_height = argv[i + 2];
    for (char el : string_height) {
        if (!isdigit(el)) {
            throw std::runtime_error("\n Height must be a natural number to crop");
        }
    }
    crop_height = std::stoi(string_height);
    if (crop_height <= 0) {
        throw std::runtime_error("\n Height must be a natural number to crop");
    }
    Size size;
    size.width_of_image = crop_width;
    size.height_of_image = crop_height;
    return size;
}

unsigned char ArgEdge(int argc, char** argv, const size_t i) {
    if (i == argc - 1) {
        throw std::runtime_error("\n Not enough parameters to detect edges");
    }
   double threshold;
   std::string string_threshold = argv[i + 1];
   bool more_than_one_dot = false;
   for (char el : string_threshold) {
       if (!isdigit(el)) {
           if (el == '.' || el == ',') {
               if (!more_than_one_dot) {
                   more_than_one_dot = true;
                   if (string_threshold == "." || string_threshold == ","){
                       throw std::runtime_error("\n Threshold must be a double from 0 to 1 to detect edges");
                   }
               } else {
                   throw std::runtime_error("\n Threshold must be a double from 0 to 1 to detect edges");
               }
           }
       }
   }
   threshold = std::stod(string_threshold);
   if (threshold < 0 || threshold > 1) {
       throw std::runtime_error("\n Threshold must be a double from 0 to 1 to detect edges");
   }
   return static_cast<unsigned char>(std::round(threshold * UCHAR_MAX));
}


float ArgGauss(int argc, char** argv, const size_t i) {
    if (i == argc - 1) {
        throw std::runtime_error("\n Not enough parameters to gauss blur");
    }
    double sigma;
    std::string string_sigma = argv[i + 1];
    bool more_than_one_dot = false;
    bool minus_was = false;
    for (char el : string_sigma) {
        if (!isdigit(el)) {
            if (el == '.' || el == ',') {
                if (!more_than_one_dot) {
                    more_than_one_dot = true;
                } else {
                    throw std::runtime_error("\n Sigma must be a double but not zero to blur");
                }
            }
            else if (el != '-' || string_sigma[0]!=el || minus_was) {
                throw std::runtime_error("\n Sigma must be a double but not zero to blur");
            } else {
                minus_was = true;
            }
        }
    }
    sigma = std::stod(string_sigma);
    if (sigma == 0) {
        throw std::runtime_error("\n Sigma must be a double but not zero to blur");
    }
    return static_cast<double>(sigma);
}


int main(int argc, char** argv) {
    Image image = Image(0, 0);
    if (argc < 3) {
        if (argc == 1) {
            std::ifstream f;
            try {
                f.open("../help.txt", std::ios::in | std::ios::binary);
                IsOpened(f);
            } catch (std::runtime_error &error) {
                throw error;
            }
            std::string str;
            while(std::getline(f, str))
            {
                std::cout << str << std::endl;
            }
            f.close();
            return 0;
        } else {
            throw std::runtime_error("\n Image processor needs both paths to read and write");
        }
    }
    std::queue<Parameters> filters_queue;
    const char* read_path = argv[1];
    const char* export_path = argv[2];
    image = BmpInputOutput::Read(read_path);
    for (size_t i = 3; i < argc; ++i) {
        if (strcmp(argv[i], "-crop") == 0) {
            Size crop_sizes = ArgCrop(argc, argv, i);
            filters_queue.push(Parameters(argv[i], crop_sizes.width_of_image, crop_sizes.height_of_image));
            i += 2;
        } else if (strcmp(argv[i], "-gs") == 0) {
            filters_queue.push(Parameters(argv[i]));
        } else if (strcmp(argv[i], "-neg") == 0) {
            filters_queue.push(Parameters(argv[i]));
        } else if (strcmp(argv[i], "-sharp") == 0) {
            filters_queue.push(Parameters(argv[i]));
        } else if (strcmp(argv[i], "-edge") == 0) {
            unsigned char threshold = ArgEdge(argc, argv, i);
            filters_queue.push(Parameters(argv[i], threshold));
            ++i;
        } else if (strcmp(argv[i], "-blur") == 0) {
            float sigma = ArgGauss(argc, argv, i);
            filters_queue.push(Parameters(argv[i], sigma));
            ++i;
        } else if (strcmp(argv[i], "-laplace") == 0) {
            filters_queue.push(Parameters(argv[i]));
        } else {
            throw std::runtime_error("\n Unknown argument was given");
        }
    }
    while (!filters_queue.empty()) {
        if (filters_queue.front().name == "-crop") {
               Crop object = Crop(filters_queue.front().p_width, filters_queue.front().p_height);
               object.Apply(image);
        } else if (filters_queue.front().name == "-gs") {
              Gray object = Gray();
              object.Apply(image);
        } else if (filters_queue.front().name == "-neg") {
               Negative object = Negative();
               object.Apply(image);
        } else if (filters_queue.front().name == "-sharp") {
                Sharpening object = Sharpening();
                object.Apply(image);
        } else if (filters_queue.front().name == "-edge") {
            EdgeDetection object = EdgeDetection(filters_queue.front().p_threshold);
            object.Apply(image);
        } else if (filters_queue.front().name == "-blur") {
            Gauss object = Gauss(filters_queue.front().p_sigma);
            object.Apply(image);
        } else if (filters_queue.front().name == "-laplace") {
            Laplacian object = Laplacian();
            object.Apply(image);
        }
        filters_queue.pop();
    }
    BmpInputOutput::Export(export_path, image);
    return 0;
}