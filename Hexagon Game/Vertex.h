#pragma once
#include "SLinkedList.h"

using namespace std;
template<class T> class Edge;    // To avoid circular dependency with Edge.h
template <class Type> 
class Vertex {
private:
    Type vData;
    bool visited;
    SLinkedList< Edge<Type>* > * adjList;      // Adjacency list representation for the graph
    template<class M> friend class DirGraph;
public:
    Vertex(Type data_) : visited(false) {
        this->vData = data_;
        this->adjList = new SLinkedList< Edge<Type>* >();
    }
   
    Vertex() : visited(false),vData(0),adjList(0) {
    }
    Type getData() { return vData; }
};
