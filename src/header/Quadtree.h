#ifndef QUADTREE
#define QUADTREE

#include <iostream>
#include <vector>
#include "ErrorMeasurement.h"
#include "Pixel.h"
using namespace std;

class QuadTreeNode{
    private:
    bool isLeaf;
    Pixel color; // Average value of a leaf
    int startX, startY, width, height;
    QuadTreeNode* children[4];
   
    public:
    QuadTreeNode();
    QuadTreeNode(Pixel color);
    QuadTreeNode(int startX, int startY, int width, int height, bool isLeaf);
    ~QuadTreeNode(); 

    void splitQuadTree(vector<vector<Pixel>>& imageMatrix, double threshold, int minBlockWidth, int minBlockHeight);
};

#endif QUADTREE