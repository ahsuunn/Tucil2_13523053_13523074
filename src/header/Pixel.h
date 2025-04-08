#ifndef PIXEL
#define PIXEL

struct Pixel {
    int r, g, b;
    Pixel(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {}
};

#endif