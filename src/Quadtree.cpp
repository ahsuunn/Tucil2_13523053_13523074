#include "Quadtree.h"


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
void QuadTreeNode::splitQuadTree(vector<vector<Pixel>>& imageMatrix, double threshold){
    if(!this->isLeaf){
        cout << "Tree that is already not a leaft can't be split again\n";
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
    
    this->children[0] = new QuadTreeNode(startX, startY + newWidth, newWidth, newHeight, true); //Top Left
    this->children[1] = new QuadTreeNode(startX + newHeight, startY + newWidth, newWidth, newHeight, true); //Top Right
    this->children[2] = new QuadTreeNode(startX, startY, newWidth, newHeight, true); //Bottom Left
    this->children[3] = new QuadTreeNode(startX + newHeight, startY, newWidth, newHeight, true); //Bottom Right
    
    for(int i = 0; i < 4; i++){
        this->children[i]->splitQuadTree(imageMatrix, threshold);
    }
}