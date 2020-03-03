//
// Created by zahrof on 22/02/2020.
//

#ifndef TEST_CPA_MINHEAP_H
#define TEST_CPA_MINHEAP_H

#include "adjarray.h"



typedef struct{
    unsigned long  node;
    unsigned long  degree;
    unsigned long id;
}Pair;

typedef struct{
    Pair * array; //pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
}MinHeap;

/*void swap(Pair *x, Pair *y);*/

void makePair(adjlist * g, unsigned long  node, Pair * p, unsigned long  degree);

int equalPair(Pair * p1, Pair *  p2);

int getIndex(MinHeap * mh, Pair * p);

/*void swap(int *x, int *y);

void makePair(adjlist * g, int node, Pair * p, int degree);*/

void makeMinHeap(MinHeap * mh, int capacity);
// to get index of left child of node at index i
int left(int i) ;

// to get index of right child of node at index i
int right(int i) ;

// to heapify a subtree with the root at given index
void MinHeapify(MinHeap * mh,int i);

int parent(int i) ;



/**
 * Removes the minimum element from MinHeap. Time Complexity of this Operation is O(Logn)
 * as this operation needs to maintain the heap property (by calling heapify()) after removing root.
 * @param mh
 * @return
 */
Pair extractMin(MinHeap * mh);

Pair getPair(MinHeap * mh, Pair * p);

/**
 * Decreases value of key. The time complexity of this operation is O(Logn).
 * If the decreases key value of a node is greater than the parent of the node,
 * then we don’t need to do anything. Otherwise, we need to traverse up to fix the violated heap property.
 * @param mh
 * @param i
 * @param new_val
 */
void decreaseKey(MinHeap * mh, int i, Pair new_val);

/**
 * It returns the root element of Min Heap. Time Complexity of this operation is O(1).
 * @param mh
 * @return
 */
Pair getMin(MinHeap * mh) ;

/**
 * Deleting a key also takes O(Logn) time.
 * We replace the key to be deleted with minum infinite by calling decreaseKey().
 * After decreaseKey(), the minus infinite value must reach root,
 * so we call extractMin() to remove the key.
 * @param mh
 * @param i
 */
void deleteKey(MinHeap * mh,int i);

/**
 * Inserting a new key takes O(Logn) time. We add a new key at the end of the tree.
 * IF new key is greater than its parent, then we don’t need to do anything.
 * Otherwise, we need to traverse up to fix the violated heap property.
 * @param mh
 * @param k
 */
void insertKey(MinHeap * mh, Pair k);
#endif //TEST_CPA_MINHEAP_H
