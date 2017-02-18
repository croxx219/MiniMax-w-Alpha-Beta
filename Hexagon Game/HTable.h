#pragma once
#include <string>
#include "SLinkedList.h"


// Hash table implemented using an array of linked lists
template <typename kType, class myType>
class HTable {
private:
    int capacity;
    SLinkedList<myType> *listArray;
  
    // This is the hash function. It takes a string, converts it to int and then
    // mod it with the total capacity of the table.
    int getIndex(const string & key) {
        int pos = (int)key.find(',');
        string sub = key.substr(0, pos);
        string remain = key.substr(++pos);
        int first = stoi(sub);
        int second = stoi(remain);
        int idx = 0;
        switch (first) { // input[0] is vertex origin
            case 1: idx = second - 2;
                break;
            case 2: idx = second + first;
                break;
            case 3: idx = second + first + 2;
                break;
            case 4:
            case 5: idx = second + first + 3;
        }
        return idx;
    }

public:  
    HTable() {
        this->capacity = 15;     // The capacity was chosen to be 15 since there are a maximum of 15 edges.
        listArray = new SLinkedList<myType>[capacity];
    }

    bool isEmpty(const kType & key) {
        int idx = HTable::getIndex(key);
        return listArray[idx].empty();
    }
    
    // Since the push_back function is being used for insertion, collision treatment happens automatically.
    bool insert(const kType & key, const myType & value) {
        int idx = HTable::getIndex(key);
        
        if (!this->isEmpty(key)) // Avoid adding duplicates vertices to the hash table
            return false;

        listArray[idx].push_back(value);
        return true;
    }

    myType search(const kType & key) {
        int i = HTable::getIndex(key);
        if (!HTable::isEmpty(key)) {
            return listArray[i].getHead()->getNodeData();
        }
        else
            return NULL;
           //throw underflow_error("Edge not found");
    }

    ~HTable() {
        delete[] listArray;
    }
};


