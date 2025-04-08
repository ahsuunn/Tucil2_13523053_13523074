// ImageProcessor.h
#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <string>
#include <vector>
#include "Pixel.h"

class ImageProcessor {
public:
    static std::vector<std::vector<Pixel>> loadImage(const std::string& filename, int& width, int& height);
    static bool saveImage(const std::string& filename, const std::vector<std::vector<Pixel>>& imageMatrix, int width, int height);
};

#endif
