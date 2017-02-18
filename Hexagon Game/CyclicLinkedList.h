#pragma once
#include <iostream>
#include <stdexcept>
#include "Node.h"

using namespace std;

template <class myType>
class CyclicLinkedList
{
private:
    Node<myType> *head;
    Node<myType> *tail;
    int sizeList;
public:
    CyclicLinkedList(): sizeList(0), head(nullptr), tail(nullptr) {
    };

    bool empty() const { return sizeList == 0; };
    Node<myType> *  getHead() { return head; }

    void push_back(myType const & data) {
        Node<myType> *newNode = new Node<myType>(data, head);
        if (this->empty()) {
            head = newNode;
            tail = head;
        }
        tail->next = newNode;   // Tail is now the newNode
        tail = newNode;
        sizeList++;
        
    };

    ~CyclicLinkedList() {
        Node<myType> *curr = head;
        Node<myType> *prev = head;
        while(curr->next!=head)
        {
            curr = curr->next;
            delete prev;
            prev = curr;    
        }
        head = nullptr;
    };
};


