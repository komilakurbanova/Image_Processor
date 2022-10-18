cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(my_project
        image_processor.cpp
        Image.cpp
        Colour.cpp
        BmpInputOutput.cpp
        Crop.cpp
        GrayScale.cpp
        Negative.cpp
        Sharpening.cpp
        MatrixFilter.cpp
        EdgeDetection.cpp
        MyFilter.cpp
        Gaussian.cpp image_processor.h)



add_catch(test_bmp
        Colour.cpp
        Image.cpp
        BmpInputOutput.cpp
        Crop.cpp
        read_export_test.cpp)

add_catch(test_crop
        Colour.cpp Image.cpp
        BmpInputOutput.cpp
        Crop.cpp
        crop_test.cpp)

add_catch(test_grayscale
        Colour.cpp
        Image.cpp
        BmpInputOutput.cpp
        GrayScale.cpp
        grayscale_test.cpp)

add_catch(test_negative
        Colour.cpp
        Image.cpp
        BmpInputOutput.cpp
        Negative.cpp
        negative_test.cpp)

add_catch(test_sharpening
        Colour.cpp
        Image.cpp
        BmpInputOutput.cpp
        MatrixFilter.cpp
        Sharpening.cpp
        sharpening_test.cpp)

add_catch(test_edgedetection
        Colour.cpp
        Image.cpp
        BmpInputOutput.cpp
        MatrixFilter.cpp
        GrayScale.cpp
        EdgeDetection.cpp
        edgedetection_test.cpp)

add_catch(test_myfilter
        Colour.cpp
        Image.cpp
        BmpInputOutput.cpp
        MatrixFilter.cpp
        MyFilter.cpp
        myfilter_test.cpp)
