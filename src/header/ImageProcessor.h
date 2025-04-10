// ImageProcessor.h
#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <string>
#include <vector>
#include "Pixel.h"
#include <Magick++.h>
#include "Quadtree.h"
using namespace Magick;
class QuadTreeNode;

class ImageProcessor {
public:
    static std::vector<std::vector<Pixel>> loadImage(const std::string& filename, int& width, int& height);
    static bool saveImage(const std::string& filename, const std::vector<std::vector<Pixel>>& imageMatrix, int width, int height);
    static void saveGif(const std::string& filename, const std::vector<Image>& gifFrames);
    static void saveFrame(QuadTreeNode* root, int width, int height);
};

#endif
