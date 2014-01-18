//
//  minHeap.h
//  Project4
//
//  Created by Joseph Pecoraro on 4/15/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#ifndef __Project4__minHeap__
#define __Project4__minHeap__

#include <iostream>
#include <vector>

//minHeap data structure used for storing Nodes
template <class T>
class minHeap {
public:
    minHeap();
    int size() { return heapSize; }
    T top();
    void heapify();
    void pop();
    void push(T element);
    
private:
    std::vector<T> heap;
    int heapSize;
};

#endif /* defined(__Project4__minHeap__) */
