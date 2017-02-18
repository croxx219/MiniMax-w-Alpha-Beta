#pragma once
#include "TreeNode.h"
#include "DirGraph.h"
#include <string>

template <class Type>
class LinkedTree {
private:
    SLinkedList<DirGraph<Type>*> * endgames;  // List of endgames moves
    TreeNode<Type> * root;
    int userPlayer, compPlayer;
    string userString, compString;

public:
    LinkedTree(int selection) {
        endgames = new SLinkedList<DirGraph<Type>*>();
        root = new TreeNode<Type>(new DirGraph<Type>(), "MAX");  // Initialize first tree node to be max, trying to make computer wins
        userPlayer = selection;

        if (selection == 1) {
            userString = "solid";
            compString = "dashed";
            compPlayer = 2;
        }
        else {
            userString = "dashed";
            compString = "solid";
            compPlayer = 1;
        }
        this->createEndGames();
    }

    void createEndGames() {
        DirGraph<Type> * startGraph = new DirGraph<Type>();
        Node<Vertex<Type>*> * first = startGraph->listv->getHead();
        Node<Vertex<Type>*> * second = first->getNext();
        Node<Vertex<Type>*> * third = NULL;
        for (int j = 0; j < 20;j++) {
            DirGraph<Type> * tmp = new DirGraph<Type>();

            switch (j) {
            case 0:
                third = second->getNext();
                break;
            case 6:
               third = second->getNext()->getNext();
                break;
            case 12:
                third = second->getNext()->getNext()->getNext();
                break;
            case 18:
                second = second->getNext();
                third = second->getNext()->getNext();
                break;

            }

            tmp->addEdge(first->getNodeData()->getData(), second->getNodeData()->getData(), "solid");
            tmp->addEdge(first->getNodeData()->getData(), third->getNodeData()->getData(), "solid");
            tmp->addEdge(second->getNodeData()->getData(), third->getNodeData()->getData(), "solid");

            if (first->getNodeData()->getData() == 6) {
                first = startGraph->listv->getHead();
                second = first->getNext();
            }
            else {
                first = first->getNext();
                second = second->getNext();
            }
            third = third->getNext();
            endgames->push_back(tmp);
        }
    }

    TreeNode<Type> * getRoot() { return root; }

    bool isTerminal(TreeNode<Type> * ptr) {
        if (endgames->empty()) {
            cout << "End Games haven't been created" << endl;
            return false;
        }
        int count = 0;
        Node<DirGraph<Type>*> * tmp = endgames->getHead();    // First Graph for endgame
        while (tmp != NULL) {
            Node<Edge<Type>*> * itr = tmp->getNodeData()->edges->getHead();  // Head to edge list of endgame graph
            while (itr != NULL) {
                string pkey = to_string((itr->getNodeData()->getOrigin()->getData())) + "," + to_string((itr->getNodeData()->getDestination()->getData()));
                if (ptr->getData()->findEdge(pkey) != NULL) {
                    if ((ptr->type == "MAX" && ptr->getData()->findEdge(pkey)->getLine() == "solid") 
                     || (ptr->type == "MIN" && ptr->getData()->findEdge(pkey)->getLine() == "dashed"))
                        count++;
                }
                if (count == 3) {
                    // Assign terminal value if terminal node is found
                    if (ptr->type == "MAX") {
                        ptr->updateData(1);
                    }
                    else {
                        ptr->updateData(-1);
                    }
                    return true;
                }
                itr = itr->getNext();
            }
            count = 0;
            tmp = tmp->getNext();

        }

        return false;
    }

    // This functions copies all edges of parent node to children (hash table and edge list)
    void addparentEdge(DirGraph<Type> * ptr, DirGraph<Type> * parent) {
        Node<Edge<Type>*> * itr2 = parent->edges->getHead();
        while (itr2 != NULL) {
            ptr->addEdge(itr2->getNodeData()->getOrigin()->getData(),itr2->getNodeData()->getDestination()->getData(), itr2->getNodeData()->getLine());
            itr2 = itr2->getNext();
        }

    }

    void generateChildren(TreeNode<Type> * parent) {
        string linetype, childrenType;
        if (parent->type == "MAX") {
            linetype = "dashed";
            childrenType = "MIN";
        }
        else
        {
            linetype = "solid";
            childrenType = "MAX";
        }
       
        for (int i = 1; i < 6; i++) {        
            for (int j = i + 1; j <= 6; j++) {
                DirGraph<Type> *tmp = new DirGraph<Type>();
                addparentEdge(tmp, parent->getData());
                string key = to_string(i) + "," + to_string(j);
                tmp->addEdge(i, j, linetype);
                if (!parent->getData()->findEdge(key)) {             
                    TreeNode<Type> * ptr = new TreeNode<Type>(tmp, childrenType);
                    isTerminal(ptr);
                    if (!isTerminal(parent)) {
                        parent->children->push_back(ptr);
                    }
                }
            }
        }
    }
    

    int max(int a, int b) {
        return (a > b) ? a : b;
    }
    int min(int a, int b) {
        return (a < b) ? a : b;
    }

    int minvalue(TreeNode<Type> * state, int a, int b) {
        if (isTerminal(state)) return state->value;
        state->value = PINF;
        if(state->children->getHead() == NULL)
            generateChildren(state);
        printChildren(state);
        Node<TreeNode<Type>*> * itr = state->children->getHead();
        while (itr != NULL) {
            state->value = min(state->value, maxvalue(itr->getNodeData(), a, b));
            if (state->value <= a) return state->value;
            b = min(a, state->value);
            itr = itr->getNext();
        }

        return state->value;

    }
    int maxvalue(TreeNode<Type> * state, int a, int b) {
        if (isTerminal(state)) return state->value;
        state->value = NINF;
        if (state->children->getHead() == NULL)
            generateChildren(state);
        printChildren(state);
        Node<TreeNode<Type>*> * itr = state->children->getHead();
        while (itr != NULL) {
            state->value = max(state->value,minvalue(itr->getNodeData(),a,b));
            if (state->value >= b) return state->value;
            a = max(a, state->value);
            itr = itr->getNext();
        }

        return state->value;
    }

    void printChildren(TreeNode<Type> * node) {
        if (node->children->getHead() != NULL) {
            Node<TreeNode<Type>*> * itr = node->children->getHead();
            while (itr != NULL) {
                itr->getNodeData()->getData()->printGraph();
                itr = itr->getNext();
            }
        }
    }
    
    // Minimax with alpha beta prunning, runs using DFS(with runtime stack created by recursion)
    TreeNode<Type> * minimax(TreeNode<Type> * node) {      
        int v = maxvalue(node, NINF, PINF);
        Node<TreeNode<Type>*> * itr = node->children->getHead();
        while (itr != NULL) {
            if (itr->getNodeData()->value == v) {
                return itr->getNodeData();
            }
            itr = itr->getNext();
        }    
        return NULL;
    }
    
    ~LinkedTree() {
        delete root;
    }
   

};