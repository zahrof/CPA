//
// Created by zahrof on 21/02/2020.
//

#ifndef FIFO_H_
#define FIFO_H_
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


typedef struct{
    unsigned long * tab;
    size_t allocsize;
    size_t begin;
    size_t sz;
}fifo;

void mkFifo(size_t maxsize, fifo * t);
int empty(fifo * f);
int full(fifo * f);
size_t size(fifo * t);
void printTapis(fifo *t);
void enfiler(fifo *t, unsigned long  p);
unsigned long  defiler(fifo * t);
#endif /* FIFO_H_ */