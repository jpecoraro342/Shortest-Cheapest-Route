//
//  minHeap.cpp
//  Project4
//
//  Created by Joseph Pecoraro on 4/15/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#include "minHeap.h"

template <class T>
minHeap<T>::minHeap() {
    heap = *new std::vector<T>(200);
    heapSize = 0;
}

//adds element to heap in the correct place
template <class T>
void minHeap<T>::push(T element) {
    if (heapSize == heap.size() -1) {
        heap.resize(heapSize*2, NULL);
    }
    
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2]->compare(element) > 0)
    {
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;                          
    }
    
    heap[currentNode] = element;
}

//removes the top item from heap (min value), and restructures;
template <class T>
void minHeap<T>::pop() {
    if (heapSize == 0)   // heap empty
        std::cerr << "error, heap is empty" << std::endl;
    
    T lastElement = heap[heapSize--];

    int currentNode = 1,
    child = 2;     
    while (child <= heapSize)
    {
        if (child < heapSize && heap[child]->compare(heap[child + 1]) > 0)
            child++;
        
        if (lastElement->compare(heap[child]) <= 0)
            break;  

        heap[currentNode] = heap[child]; 
        currentNode = child;             
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

//returns the top item of the heap (min value)
template <class T>
T minHeap<T>::top() {
    return heap[1];
}

//unused - restructures from top down
template <class T>
void minHeap<T>::heapify() {
    for (int root = heapSize/2; root >=1; root--) {
        T rootElement = heap[root];
        
        int child = 2*root;
        
        while (child<= heapSize) {
            if (child < heapSize && heap[child]->compare(heap[child+1]) > 0)
                child ++;
            if (rootElement <= heap[child])
                break;
            
            heap[child/2] = heap[child];
            child *=2;
        }
        heap[child/2] = rootElement;
    }
}