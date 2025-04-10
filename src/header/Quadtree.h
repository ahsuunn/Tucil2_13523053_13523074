#ifndef QUADTREE
#define QUADTREE

#include <Magick++.h>
#include <iomanip> 
#include <iostream>
#include <vector>
#include "ErrorMeasurement.h"
#include "Pixel.h"
#include <FreeImage.h>
#include "ImageProcessor.h"
using namespace std;
using namespace Magick;

class QuadTreeNode{
    public:
    //Attribute
    bool isLeaf;
    Pixel color;
    int startX, startY, width, height;
    QuadTreeNode* children[4];
    
    //Ctor and dtor
    QuadTreeNode();
    QuadTreeNode(Pixel color);
    QuadTreeNode(int startX, int startY, int width, int height, bool isLeaf);
    ~QuadTreeNode();
    
    //Split Quad Tree Method
    void splitQuadTreeWithVariance(vector<vector<Pixel>>& imageMatrix, double threshold, int minBlockArea);
    void splitQuadTreeWithMAD(vector<vector<Pixel>>& imageMatrix, double threshold, int minBlockArea);
    void splitQuadTreeWithMaxDiff(vector<vector<Pixel>>& imageMatrix, double threshold, int minBlockArea);
    void splitQuadTreeWithEntropy(vector<vector<Pixel>>& imageMatrix, double threshold, int minBlockArea);
    
    //Helper Method
    static int countNodes(QuadTreeNode* node);
    static int treeDepth(QuadTreeNode* node);
    
    //Method to render GIF
    void getLeafNodesAtDepth(int targetDepth, int currentDepth, std::vector<QuadTreeNode*>& result);
    static void createImageFromDepth(QuadTreeNode* root, int imageW, int imageH, int depth);
    static void generateGifFromQuadTree(QuadTreeNode* root, int imgW, int imgH);
    
    //Method to render Image
    static void fillBlock(vector<vector<Pixel>>& result, int startX, int startY, int width, int height, const Pixel& color);
    static void renderQuadTreeToMatrix(QuadTreeNode* node, vector<vector<Pixel>>& result);

};

#endif