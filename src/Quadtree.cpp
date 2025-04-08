#include "header/Quadtree.h"


// Constructor
QuadTreeNode::QuadTreeNode(Pixel color): isLeaf(true), color(color){
    for(int i=0 ; i < 4; i++) children[i] = nullptr;
}

QuadTreeNode::QuadTreeNode(): isLeaf(true){
    for(int i=0 ; i < 4; i++) children[i] = nullptr;
}

QuadTreeNode::QuadTreeNode(int startX, int startY, int width, int height, bool isLeaf): 
    isLeaf(isLeaf),
    startX(startX),
    startY(startY),
    width(width),
    height(height),
    color({0,0,0})
    {
    for(int i=0 ; i < 4; i++) children[i] = nullptr;
}

//Destructor
QuadTreeNode::~QuadTreeNode(){
    for(int i=0 ; i < 4; i++) {
        if(children[i]) delete children[i];
    }
}

//Method
void QuadTreeNode::splitQuadTreeWithVariance(vector<vector<Pixel>>& imageMatrix, double threshold, int minBlockArea){
    if(!this->isLeaf){
        cout << "Tree that is already not a leaft can't be split again\n";
        return;
    }
    
    vector<double> avgColor = averageBlockValue(imageMatrix, startX, startY, width, height);
    this->color = {
        static_cast<int>(avgColor[0]),
        static_cast<int>(avgColor[1]),
        static_cast<int>(avgColor[2])
    };

    if(this->height * this->width < minBlockArea){
        return;
    }

    double variance = blockVariance(imageMatrix, startX, startY, width, height);
    if(variance < threshold){
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (children[i]) delete children[i];
    }

    this->isLeaf = false;
    int newHeight = this->height/2;
    int newWidth = this->width/2;

    int widthRight = width - newWidth;
    int heightBottom = height - newHeight;
    
    this->children[0] = new QuadTreeNode(startX, startY, newWidth, newHeight, true); // Top Left
    this->children[1] = new QuadTreeNode(startX + newWidth, startY, widthRight, newHeight, true); // Top Right
    this->children[2] = new QuadTreeNode(startX, startY + newHeight, newWidth, heightBottom, true); // Bottom Left
    this->children[3] = new QuadTreeNode(startX + newWidth, startY + newHeight, widthRight, heightBottom, true); // Bottom Right
    
    for(int i = 0; i < 4; i++){
        this->children[i]->splitQuadTreeWithVariance(imageMatrix,threshold,minBlockArea);
    }
}

void QuadTreeNode::splitQuadTreeWithMAD(vector<vector<Pixel>>& imageMatrix, double threshold, int minBlockArea){
    if(!this->isLeaf){
        cout << "Tree that is already not a leaft can't be split again\n";
        return;
    }
    
    vector<double> avgColor = averageBlockValue(imageMatrix, startX, startY, width, height);
    this->color = {
        static_cast<int>(avgColor[0]),
        static_cast<int>(avgColor[1]),
        static_cast<int>(avgColor[2])
    };

    if(this->height * this->width < minBlockArea){
        return;
    }

    double MAD = blockMeanAbsoluteDeviation(imageMatrix, startX, startY, width, height);
    if(MAD < threshold){
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (children[i]) delete children[i];
    }

    this->isLeaf = false;
    int newHeight = this->height/2;
    int newWidth = this->width/2;

    int widthRight = width - newWidth;
    int heightBottom = height - newHeight;
    
    this->children[0] = new QuadTreeNode(startX, startY, newWidth, newHeight, true); // Top Left
    this->children[1] = new QuadTreeNode(startX + newWidth, startY, widthRight, newHeight, true); // Top Right
    this->children[2] = new QuadTreeNode(startX, startY + newHeight, newWidth, heightBottom, true); // Bottom Left
    this->children[3] = new QuadTreeNode(startX + newWidth, startY + newHeight, widthRight, heightBottom, true); // Bottom Right
    
    for(int i = 0; i < 4; i++){
        this->children[i]->splitQuadTreeWithMAD(imageMatrix,threshold,minBlockArea);
    }
}
void QuadTreeNode::splitQuadTreeWithMaxDiff(vector<vector<Pixel>>& imageMatrix, double threshold, int minBlockArea){
    if(!this->isLeaf){
        cout << "Tree that is already not a leaft can't be split again\n";
        return;
    }
    
    vector<double> avgColor = averageBlockValue(imageMatrix, startX, startY, width, height);
    this->color = {
        static_cast<int>(avgColor[0]),
        static_cast<int>(avgColor[1]),
        static_cast<int>(avgColor[2])
    };

    if(this->height * this->width < minBlockArea){
        return;
    }

    double maxPixelDifference = bloxMaxPixelDifference(imageMatrix, startX, startY, width, height);
    if(maxPixelDifference < threshold){
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (children[i]) delete children[i];
    }

    this->isLeaf = false;
    int newHeight = this->height/2;
    int newWidth = this->width/2;

    int widthRight = width - newWidth;
    int heightBottom = height - newHeight;
    
    this->children[0] = new QuadTreeNode(startX, startY, newWidth, newHeight, true); // Top Left
    this->children[1] = new QuadTreeNode(startX + newWidth, startY, widthRight, newHeight, true); // Top Right
    this->children[2] = new QuadTreeNode(startX, startY + newHeight, newWidth, heightBottom, true); // Bottom Left
    this->children[3] = new QuadTreeNode(startX + newWidth, startY + newHeight, widthRight, heightBottom, true); // Bottom Right
    
    for(int i = 0; i < 4; i++){
        this->children[i]->splitQuadTreeWithMaxDiff(imageMatrix,threshold,minBlockArea);
    }
}
void QuadTreeNode::splitQuadTreeWithEntropy(vector<vector<Pixel>>& imageMatrix, double threshold, int minBlockArea){
    if(!this->isLeaf){
        cout << "Tree that is already not a leaft can't be split again\n";
        return;
    }
    
    vector<double> avgColor = averageBlockValue(imageMatrix, startX, startY, width, height);
    this->color = {
        static_cast<int>(avgColor[0]),
        static_cast<int>(avgColor[1]),
        static_cast<int>(avgColor[2])
    };

    if(this->height * this->width < minBlockArea){
        return;
    }

    double entropy = blockEntropy(imageMatrix, startX, startY, width, height, 8);
    if(entropy < threshold){
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (children[i]) delete children[i];
    }

    this->isLeaf = false;
    int newHeight = this->height/2;
    int newWidth = this->width/2;

    int widthRight = width - newWidth;
    int heightBottom = height - newHeight;
    
    this->children[0] = new QuadTreeNode(startX, startY, newWidth, newHeight, true); // Top Left
    this->children[1] = new QuadTreeNode(startX + newWidth, startY, widthRight, newHeight, true); // Top Right
    this->children[2] = new QuadTreeNode(startX, startY + newHeight, newWidth, heightBottom, true); // Bottom Left
    this->children[3] = new QuadTreeNode(startX + newWidth, startY + newHeight, widthRight, heightBottom, true); // Bottom Right
    
    for(int i = 0; i < 4; i++){
        this->children[i]->splitQuadTreeWithEntropy(imageMatrix,threshold,minBlockArea);
    }
}