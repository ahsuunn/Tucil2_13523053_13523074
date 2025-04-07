// ImageProcessor.cpp
#include "header/ImageProcessor.h"
#include <FreeImage.h>
#include <iostream>

std::vector<std::vector<Pixel>> ImageProcessor::loadImage(const std::string& filename, int& width, int& height) {
    FreeImage_Initialise();

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.c_str(), 0);
    if (format == FIF_UNKNOWN) format = FreeImage_GetFIFFromFilename(filename.c_str());
    if (format == FIF_UNKNOWN || !FreeImage_FIFSupportsReading(format)) {
        std::cerr << "Unsupported or unknown image format: " << filename << std::endl;
        exit(1);
    }

    FIBITMAP* bitmap = FreeImage_Load(format, filename.c_str());
    if (!bitmap) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        exit(1);
    }

    FIBITMAP* rgbBitmap = FreeImage_ConvertTo24Bits(bitmap);
    FreeImage_Unload(bitmap);

    width = FreeImage_GetWidth(rgbBitmap);
    height = FreeImage_GetHeight(rgbBitmap);

    std::vector<std::vector<Pixel>> imageMatrix(width, std::vector<Pixel>(height));

    for (int y = 0; y < height; ++y) {
        BYTE* bits = FreeImage_GetScanLine(rgbBitmap, y);
        for (int x = 0; x < width; ++x) {
            Pixel px;
            px.b = bits[FI_RGBA_BLUE];
            px.g = bits[FI_RGBA_GREEN];
            px.r = bits[FI_RGBA_RED];
            if (format == FIF_PNG) {
                imageMatrix[width-x-1][y] = px;
            } else {
                imageMatrix[x][y] = px;
            }
            bits += 3;
        }
    }

    FreeImage_Unload(rgbBitmap);
    FreeImage_DeInitialise();

    return imageMatrix;
}

void ImageProcessor::saveImage(const std::string& filename, const std::vector<std::vector<Pixel>>& imageMatrix, int width, int height) {
    FreeImage_Initialise();

    FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);
    if (!bitmap) {
        std::cerr << "Failed to allocate bitmap for saving." << std::endl;
        exit(1);
    }

    for (int y = 0; y < height; ++y) {
        BYTE* bits = FreeImage_GetScanLine(bitmap, y);
        for (int x = 0; x < width; ++x) {
            if(width>height){
                const Pixel& px = imageMatrix[width - x - 1][height - y - 1];
                bits[x * 3 + FI_RGBA_BLUE] = px.b;
                bits[x * 3 + FI_RGBA_GREEN] = px.g;
                bits[x * 3 + FI_RGBA_RED] = px.r;
            } else {
                const Pixel& px = imageMatrix[width - x - 1][y];
                bits[x * 3 + FI_RGBA_BLUE] = px.b;
                bits[x * 3 + FI_RGBA_GREEN] = px.g;
                bits[x * 3 + FI_RGBA_RED] = px.r;
            }
        }
    }
    

    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(filename.c_str());
    if (!FreeImage_Save(format, bitmap, filename.c_str())) {
        std::cerr << "Failed to save image: " << filename << std::endl;
    }

    FreeImage_Unload(bitmap);
    FreeImage_DeInitialise();
}
