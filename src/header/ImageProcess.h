#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <vector>
#include <string>
#include "../stbi/stb_image.h"
#include "../stbi/stb_image_write.h"
#include "Pixel.h"

class ImageProcessor {
    public:
        static std::vector<std::vector<Pixel> > loadImage(const std::string& filename, int& width, int& height);
        static void saveImage(const std::string& filename, const std::vector<std::vector<Pixel> >& pixels);
};

#endif