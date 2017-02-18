#pragma once
#include "DirGraph.h"
#define NINF -10000
#define PINF 10000

using namespace std;

template<class T> class Edge; // To avoid circular dependency with Edge.h
template <class myType>
class TreeNode {
private:
    DirGraph<myType> * data;
    string type;
    bool visited;
    int value;
    SLinkedList < TreeNode<myType> * > *children;

    template<class U> friend class LinkedTree;
public:
    TreeNode(DirGraph<myType> * situation, string type_) : visited(false){
        this->type = type_;
        if (type == "MAX") value = NINF;
        else value = PINF;
        this->data = situation;
        this->children = new SLinkedList< TreeNode< myType > * >();
    }
    
    DirGraph<myType> * getData() { return data; }

    void updateData(int v) { value = v; }
    void updateType(string type_) { type = type_; }

    // This is used to avoid override of children during minimax
    void deleteChildren() { children->clear();}
};