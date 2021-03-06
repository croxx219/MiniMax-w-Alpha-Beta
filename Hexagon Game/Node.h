#pragma once

// A node class for the linked list
template <class type> class Node{
private:
    type data;
    Node * next;
    template<class U> friend class SLinkedList;
    template<class M> friend class CyclicLinkedList;
public:
    Node(const type & data) :next(0) {
        this->data = data;

    }
   Node(const type & data, Node * next) {
        this->data = data;
        this->next = next;
    }
    type getNodeData() { return data; }
    Node * getNext() { return next; }
};
