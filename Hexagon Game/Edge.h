#pragma once
#include "Vertex.h"


//************************************
// The only available edges are:
// 1->2
// 1->3
// 1->4
// 1->5
// 1->6
// 2->3
// 2->4
// 2->5
// 2->6
// 3->4
// 3->5
// 3->6
// 4->5
// 4->6
// 5->6
//************************************

template<class Type> 
class Edge
{
private:
    string lineEdge;
    bool added;
    Vertex<Type> * origin;
    Vertex<Type> * destination; 
    template <class M> friend class DirGraph;
    
public:
    
    Edge(Vertex<Type> * origin_, Vertex<Type> * destination_, string lineEdge_)
    {
        this->lineEdge = lineEdge_;
        this->origin = origin_;
        this->destination = destination_;
        this->added = false;
    }

    string getLine() { return lineEdge; }
    Vertex<Type> * getOrigin() { return origin; };
    Vertex<Type> * getDestination() { return destination; };
};
