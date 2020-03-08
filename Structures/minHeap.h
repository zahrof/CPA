//
// Created by zahrof on 22/02/2020.
//

#ifndef TEST_CPA_MINHEAP_H
#define TEST_CPA_MINHEAP_H





typedef struct{
    unsigned long  node;
    unsigned long  degree;
}Pair;

typedef struct{
    Pair * array; //pointer to array of elements in heap
    unsigned long capacity; // maximum possible size of min heap
    unsigned long heap_size; // Current number of elements in min heap
}MinHeap;

/*void swap(Pair *x, Pair *y);*/

Pair * makePair(unsigned long  node, unsigned long  degree);

int equalPair(Pair * p1, Pair *  p2);

void makeMinHeap(MinHeap * mh, int capacity);
// to get index of left child of node at index i
int left(int i) ;

// to get index of right child of node at index i
int right(int i) ;

// to heapify a subtree with the root at given index
void MinHeapify(MinHeap * mh,int i);

int parent(int i) ;

void deleteMinHeap(MinHeap * mh) ;



/**
 * Removes the minimum element from MinHeap. Time Complexity of this Operation is O(Logn)
 * as this operation needs to maintain the heap property (by calling heapify()) after removing root.
 * @param mh
 * @return
 */
unsigned long extractMin(MinHeap * mh);


/**
 * Inserting a new key takes O(Logn) time. We add a new key at the end of the tree.
 * IF new key is greater than its parent, then we don’t need to do anything.
 * Otherwise, we need to traverse up to fix the violated heap property.
 * @param mh
 * @param k
 */
void insertKey(MinHeap * mh, unsigned long degree, unsigned long node);
#endif //TEST_CPA_MINHEAP_H
