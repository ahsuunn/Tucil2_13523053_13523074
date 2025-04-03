#ifndef QUADTREE
#define QUADTREE

#include <iostream>

struct Pixel {
    int r, g, b;
};

class QuadTreeNode{
    private:
    bool isLeaf;
    Pixel color; // Average value of a leaf
    int startX, startY, width, height;

    QuadTreeNode* children[4];

   
    public:
    QuadTreeNode(Pixel color): isLeaf(true), color(color){
        for(int i=0 ; i < 4; i++) children[i] = nullptr;
    }
    
    QuadTreeNode(): isLeaf(false){
        for(int i=0 ; i < 4; i++) children[i] = nullptr;
    }
    
    ~QuadTreeNode(){
        for(int i=0 ; i < 4; i++) {
            if(children[i]) delete children[i];
        }

    }

};



#endif QUADTREE