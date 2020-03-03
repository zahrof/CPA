//
// Created by zahrof on 22/02/2020.
//
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <zconf.h>
#include "minHeap.h"


void makeMinHeap(MinHeap * mh, int capacity){
    mh->heap_size = 0;
    mh->capacity = capacity;
    mh->array = malloc(capacity * sizeof(Pair));
}
void swap(Pair *x, Pair *y)
{
    Pair temp = *x;
    *x = *y;
    *y = temp;
    int tempId= x->id;
    x->id=y->id;
    y->id=tempId;
}

void makePair(adjlist * g, unsigned long  node, Pair * p, unsigned long  degree){
    p->degree= degree;
    p->node = node;
}

int equalPair(Pair * p1, Pair *  p2){
    if ((p1->degree==p2->degree && p2->node==p1->node)) return 1;
    return 0;
}

// to get index of left child of node at index i
int left(int i) { return (2*i + 1); }

// to get index of right child of node at index i
int right(int i) { return (2*i + 2); }

// to heapify a subtree with the root at given index
void MinHeapify(MinHeap * mh,int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < mh->heap_size && mh->array[l].degree < mh->array[i].degree)
        smallest = l;
    if (r < mh->heap_size && mh->array[r].degree < mh->array[smallest].degree)
        smallest = r;
    if (smallest != i)
    {
        swap(&mh->array[i], &mh->array[smallest]);
        MinHeapify(mh, smallest);
    }
}

int parent(int i) { return (i-1)/2; }

Pair getPair(MinHeap * mh, Pair * p){
    for (int i =0; i<mh->heap_size; i++){
        if(equalPair(&mh->array[i],p)) return mh->array[i];
    }
}

int getIndex(MinHeap * mh, Pair * p){
    for (int i =1; i<=mh->heap_size; i++){
        if(equalPair(&mh->array[i],p)){
            printf("potatoe");
            return i;
        }
    }
}



// to extract the root which is the minimum element
Pair extractMin(MinHeap * mh){
    if (mh->heap_size <= 0) {
        Pair p;
        p.degree=-1;
        p.node=-1;
        return p;
    }
    if (mh->heap_size == 1)
    {
        mh->heap_size--;
        return mh->array[0];
    }

    // Store the minimum value, and remove it from heap
    Pair root = mh->array[0];
    mh->array[0] = mh->array[mh->heap_size-1];
    mh->heap_size--;
    MinHeapify(mh, 0);

    return root;
}

// Decreases key value of key at index i to new_val
void decreaseKey(MinHeap * mh, int i, Pair new_val){
    mh->array[i] = new_val;
    while (i != 0 && mh->array[parent(i)].degree > mh->array[i].degree)
    {
        swap(&mh->array[i], &mh->array[parent(i)]);
        i = parent(i);
    }
}

// Returns the minimum key (key at root) from min heap
Pair getMin(MinHeap * mh) { return mh->array[0]; }

// Deletes a key stored at index i
void deleteKey(MinHeap * mh,int i){
   // decreaseKey(mh, i, );
    extractMin(mh);
}

// Inserts a new key 'k'
void insertKey(MinHeap * mh, Pair k){
    if (mh->heap_size == mh->capacity)
    {
        puts("\nOverflow: Could not insertKey\n");
        return;
    }

    // First insert the new key at the end
    mh->heap_size++;
    int i = mh->heap_size - 1;
    mh->array[i] = k;

    // Fix the min heap property if it is violated
    while (i != 0 && mh->array[parent(i)].degree > mh->array[i].degree)
    {
        swap(&mh->array[i], &mh->array[parent(i)]);
        i = parent(i);
    }mh->array[i].id=i;
}