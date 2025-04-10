#include "header/Quadtree.h"

extern int splitCount;
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

//Split Quad Tree Method
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


//Method to render GIF
void QuadTreeNode::generateGifFromQuadTree(QuadTreeNode* root, int imgW, int imgH) {
    int maxDepth = root->treeDepth(root);

    for (int d = 0; d <= maxDepth; ++d) {
        createImageFromDepth(root, imgW, imgH, d);
    }
}

void QuadTreeNode::createImageFromDepth(QuadTreeNode* root, int imageW, int imageH, int depth) {
    std::vector<std::vector<Pixel>> renderMatrix(imageW, std::vector<Pixel>(imageH));
    FIBITMAP* image = FreeImage_Allocate(imageW, imageH, 24);

    std::vector<QuadTreeNode*> leafNodes;
    root->getLeafNodesAtDepth(depth, 0, leafNodes);

    for (QuadTreeNode* node : leafNodes) {
        for (int y = node->startY; y < node->startY + node->height; ++y) {
            for (int x = node->startX; x < node->startX + node->width; ++x) {
                renderMatrix[x][y] = node->color;
            }
        }
    }

    for (int y = 0; y < imageH; ++y) {
        BYTE* bits = FreeImage_GetScanLine(image, y);
        for (int x = 0; x < imageW; ++x) {
            const Pixel& px = renderMatrix[x][y];
            bits[x * 3 + FI_RGBA_BLUE] = px.b;
            bits[x * 3 + FI_RGBA_GREEN] = px.g;
            bits[x * 3 + FI_RGBA_RED] = px.r;
        }
    }

    std::ostringstream oss;
    oss << "frame" << std::setw(5) << std::setfill('0') << depth << ".bmp";
    FreeImage_Save(FIF_BMP, image, oss.str().c_str());
    FreeImage_Unload(image);
}

void QuadTreeNode::getLeafNodesAtDepth(int targetDepth, int currentDepth, std::vector<QuadTreeNode*>& result) {
    if (currentDepth == targetDepth) {
        result.push_back(this);
        return;
    }
    
    if (!this->isLeaf && currentDepth < targetDepth) {
        for (auto& c : this->children) {
            if (c) c->getLeafNodesAtDepth(targetDepth, currentDepth + 1, result);
        }
    }else{
        result.push_back(this);
        return;
    }
}


// Method for rendering image
void QuadTreeNode::fillBlock(vector<vector<Pixel>>& result, int startX, int startY, int width, int height, const Pixel& color) {
    for (int y = startY; y < startY + height; ++y) {
        for (int x = startX; x < startX + width; ++x) {
            if (x < result.size() && y < result[0].size()) {
                result[x][y] = color;
            } 
        }
    }
}

// Render dari QuadTree ke matrix hasil
void QuadTreeNode::renderQuadTreeToMatrix(QuadTreeNode* node, vector<vector<Pixel>>& result) {
    if (node->isLeaf) {
        fillBlock(result, node->startX, node->startY, node->width, node->height, node->color);
    } else {
        for (int i = 0; i < 4; i++) {
            if (node->children[i]) {
                renderQuadTreeToMatrix(node->children[i], result);
            }
        }
    }
}

// Helper Method
int QuadTreeNode::countNodes(QuadTreeNode* node) {
    if (node == nullptr) return 0;
    int count = 1;
    for (int i = 0; i < 4; ++i) {
        count += countNodes(node->children[i]);
    }
    return count;
}

int QuadTreeNode::treeDepth(QuadTreeNode* node) {
    if (node == nullptr || node->isLeaf) return 1;
    int maxDepth = 0;
    for (int i = 0; i < 4; ++i) {
        maxDepth = std::max(maxDepth, treeDepth(node->children[i]));
    }
    return 1 + maxDepth;
}
