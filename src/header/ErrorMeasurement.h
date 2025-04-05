#ifndef ERROR_MEASUREMENT
#define ERROR_MEASUREMENT

#include <iostream>
#include <cmath>
#include <vector>
#include "quadtree.h"
#include "pixel.h"
using namespace std;

// Variance
vector<double> averageBlockValue(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height);
double blockVariance(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height);

// Mean Absolute Deviation
double blockMeanAbsoluteDeviation(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height);

// Max Difference
double bloxMaxPixelDifference(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height);

// Entropy
vector<vector<int>> computeHistogram(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height, int colorBit);
double computeChannelEntropy(vector<int>& histogram, int colorBit);
double blockEntropy(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height, int colorBit);

#endif ERROR_MEASUREMENT