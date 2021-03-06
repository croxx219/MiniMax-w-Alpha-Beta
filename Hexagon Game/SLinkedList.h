#pragma once
#include "Node.h"
#include <iostream>
#include <string>
#include <cstddef>
#include <cassert>
using namespace std;

template<class T> 
class SLinkedList{
protected:
    Node<T> * head;
    int sz;
public:
    SLinkedList():head(NULL), sz(0){
    }
    bool empty() const{
        return head == NULL;
    }
   
    Node<T> *  getHead() { return head; }
   
    void push_back(const T & data){
        Node<T> *tmp_node = new Node<T>(data);
        Node<T> *ptr = head;
        if (ptr == NULL){
            head = tmp_node;
            sz++;
        }
        else{
            while(ptr->next != NULL){
                ptr = ptr->next;
            }
            ptr->next = tmp_node;
            sz++;
        }
    }
    
    int clear() {
        int count = 0;
        Node<T> *ptr = head;
        Node<T> * prev = head;
        while (ptr != NULL) {
            ptr = ptr->next;
            delete prev;
            prev = ptr;
            count++;
        }
        head = NULL;
        return count;
    }
};
