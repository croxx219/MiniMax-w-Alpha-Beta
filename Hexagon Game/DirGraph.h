#pragma once
#include <iostream>
#include <string>
#include "HTable.h"
#include "Vertex.h"
#include "Edge.h"
#include "Node.h"
#include "CyclicLinkedList.h"

using namespace std;

template<class Type> 
class DirGraph
{
private:   
    HTable<string, Edge<Type>*> * edgeTable;   // A hash table is used for faster retrieval of the vertices of the graph
    CyclicLinkedList< Vertex<Type>*> * listv;  // List of vertices, remains fixed after initialization
    SLinkedList< Edge<Type>*> * edges;         // List of edges
    
    template<class M> friend class LinkedTree;
public:

    DirGraph() {
        edgeTable = new HTable<string, Edge<Type>*>();
        listv = new CyclicLinkedList<Vertex<Type>*>();
        edges = new SLinkedList < Edge<Type>*>();
        this->buildGraph();
    };

    //Creates 6 vertices numbered 1 to 6.
    void buildGraph()
    {
        for (int i = 1; i <= 6; i++) {
            Vertex<Type> * tmp = new Vertex<Type>(i);
            listv->push_back(tmp);         
        }
    }
    
    // Find the edge containing the key
    Edge<Type> * findEdge(const string & key)
    {
        return edgeTable->search(key);
    }

    bool addEdge(int origin, int destination, string type) {
        // This method guarantees correct storage in hash table
        if (origin > destination) {
            int tmp = origin;
            origin = destination;
            destination = tmp;
        }

        Vertex<Type> * v1 = new Vertex<Type>(origin);
        Vertex<Type> * v2 = new Vertex<Type>(destination);

        string firstValue = to_string(origin);
        string secondValue = to_string(destination);
        string mkey = firstValue + "," + secondValue;

        // Add to hash table and edge list
        if (!findEdge(mkey)) {
            Edge<Type> * edge = new Edge<Type>(v1, v2, type);
            edgeTable->insert(mkey, edge);
            edges->push_back(edge);
            return true;
        }
        else return false;
    }

    void printGraph() {
        cout << "Status: " << endl;
        Node<Edge<Type>*> * itr = edges->getHead();
        while (itr != NULL) {
            cout << itr->getNodeData()->getOrigin()->getData() << "," << itr->getNodeData()->getDestination()->getData() << " " << itr->getNodeData()->getLine() << "\n";
            itr = itr->getNext();
        }
        cout << endl;
    }
   
    ~DirGraph()
    {
        delete listv;
        delete edges;
        delete edgeTable;
    }

};