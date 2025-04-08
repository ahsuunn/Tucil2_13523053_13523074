#include "header/ErrorMeasurement.h"

// Variance
vector<double> averageBlockValue(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height){
    int rowSize = imageMatrix.size();
    int colSize = imageMatrix[0].size();
    
    double sumR = 0;
    double sumG = 0;
    double sumB = 0;
    int count = 0;
    
    for (int i = startX; i < startX + width && i < rowSize; ++i) {
        for (int j = startY; j < startY + height && j < colSize; ++j) {
            sumR += imageMatrix[i][j].r ; sumG += imageMatrix[i][j].g; sumB += imageMatrix[i][j].b;
            count++;
        }
    }
    
    double averageR = sumR / count;
    double averageG = sumG / count;
    double averageB = sumB / count;
    vector<double> resulPixel = {averageR, averageG, averageB};
    
    return resulPixel; 
} 

double blockVariance(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height){
    double sumR = 0, sumG = 0, sumB = 0;
    int N = width * height;
    int rowSize = imageMatrix.size();
    int colSize = imageMatrix[0].size();
    
    vector<double> averagePixelValue = averageBlockValue(imageMatrix, startX, startY, width, height);
    double averageR = averagePixelValue[0];
    double averageG = averagePixelValue[1];
    double averageB = averagePixelValue[2];
    
    for (int i = startX; i < startX + width && i < rowSize; ++i) {
        for (int j = startY; j < startY + height && j < colSize; ++j) {
            sumR += pow((imageMatrix[i][j].r - averageR), 2);
            sumG += pow((imageMatrix[i][j].g - averageG), 2);
            sumB += pow((imageMatrix[i][j].b - averageB), 2);
        }
    }
    
    double variance = (sumR + sumG + sumB) / (3 * N);
    return variance;
}

// Mean Absolute Deviation
double blockMeanAbsoluteDeviation(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height){
    double sumR = 0, sumG = 0, sumB = 0;
    int N = width * height;
    int rowSize = imageMatrix.size();
    int colSize = imageMatrix[0].size();
    
    vector<double> averagePixelValue = averageBlockValue(imageMatrix, startX, startY, width, height);
    double averageR = averagePixelValue[0];
    double averageG = averagePixelValue[1];
    double averageB = averagePixelValue[2];
    
    for (int i = startX; i < startX + width && i < rowSize; ++i) {
        for (int j = startY; j < startY + height && j < colSize; ++j) {
            sumR += abs(imageMatrix[i][j].r - averageR);
            sumG += abs(imageMatrix[i][j].g - averageG);
            sumB += abs(imageMatrix[i][j].b - averageB);
        }
    }
    
    double MAD = (sumR + sumG + sumB) / (3 * N);
    return MAD;
}

// Max Difference
double bloxMaxPixelDifference(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height){
    int N = width * height;
    int rowSize = imageMatrix.size();
    int colSize = imageMatrix[0].size();
    Pixel maxPixel = {0,0,0};
    Pixel minPixel = {0,0,0};
    
    for (int i = startX; i < startX + width && i < rowSize; ++i) {
        for (int j = startY; j < startY + height && j < colSize; ++j) {
            maxPixel.r = max(maxPixel.r, imageMatrix[i][j].r);
            maxPixel.g = max(maxPixel.g, imageMatrix[i][j].g);
            maxPixel.b = max(maxPixel.b, imageMatrix[i][j].b);
            
            minPixel.r = min(minPixel.r, imageMatrix[i][j].r);
            minPixel.g = min(minPixel.g, imageMatrix[i][j].g);
            minPixel.b = min(minPixel.b, imageMatrix[i][j].b);
        }
    }
    
    double maxPixelDifference = ((maxPixel.r - minPixel.r) + (maxPixel.g - minPixel.g) + (maxPixel.b + minPixel.b))/3;
    return maxPixelDifference;
}

    // Entropy
    vector<vector<int>> computeHistogram(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height, int colorBit) {
        vector<int> histogramR(pow(2,colorBit), 0); 
        vector<int> histogramG(pow(2,colorBit), 0); 
        vector<int> histogramB(pow(2,colorBit), 0); 
        vector<vector<int>> histogram(3);
        
        int rowSize = imageMatrix.size();
        int colSize = imageMatrix[0].size();
        // Iterate through the block
        for (int i = startX; i < startX + width && i < rowSize; ++i) {
            for (int j = startY; j < startY + height && j < colSize; ++j) {
                histogramR[imageMatrix[i][j].r]++;
                histogramG[imageMatrix[i][j].g]++;
                histogramB[imageMatrix[i][j].b]++;
            }
        }
        histogram[0] = histogramR;
        histogram[1] = histogramG;
        histogram[2] = histogramB;
        

        return histogram;
    }

    double computeChannelEntropy(vector<int>& histogram, int totalPixels){
        double entropy = 0;
        for (int i = 0; i < histogram.size(); ++i) {
            if(histogram[i] > 0){
                double probability = static_cast<double>(histogram[i]) / totalPixels; 
                entropy -= probability * log2(probability);
            }
        }
        return entropy;
    }

    double blockEntropy(vector<vector<Pixel>>& imageMatrix, int startX, int startY, int width, int height, int colorBit){
        double entropyR = 0, entropyG = 0, entropyB = 0;
        int totalPixel = width * height;

        vector<vector<int>> histogram = computeHistogram(imageMatrix, startX, startY, width, height, colorBit);
        vector<int> histogramR = histogram[0];
        vector<int> histogramG = histogram[1];
        vector<int> histogramB = histogram[2];
        
        entropyR = computeChannelEntropy(histogramR, totalPixel);
        entropyG = computeChannelEntropy(histogramG, totalPixel);
        entropyB = computeChannelEntropy(histogramB, totalPixel);
        
        
        double entropy = (entropyR + entropyG + entropyB) / 3;
        return entropy;
    }