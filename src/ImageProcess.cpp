#include "header/ImageProcess.h"

std::vector<std::vector<Pixel> > ImageProcessor::loadImage(const std::string& filename, int& width, int& height){
    int channels;
    unsigned char* imgData = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if(!imgData){
        throw std::runtime_error("Failed to load image: " + filename);
    }

    std::vector<std::vector<Pixel> > pixelMatrix(height, std::vector<Pixel>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * 3;
            pixelMatrix[y][x] = Pixel(imgData[idx], imgData[idx + 1], imgData[idx + 2]);
        }
    }

    stbi_image_free(imgData);
    return pixelMatrix;
}

void ImageProcessor::saveImage(const std::string& filename, const std::vector<std::vector<Pixel> >& pixels){
    int width = pixels[0].size();
    int height = pixels.size();
    std::vector<unsigned char> imgData(width * height * 3);
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * 3;
            imgData[idx] = pixels[y][x].r;
            imgData[idx + 1] = pixels[y][x].g;
            imgData[idx + 2] = pixels[y][x].b;
        }
    }

    stbi_write_jpg(filename.c_str(), width, height, 3, imgData.data(), width * 3);
}