//
// Created by zahrof on 21/02/2020.
//

#ifndef FIFO_H_
#define FIFO_H_
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


typedef struct{
    unsigned long ** tab;
    unsigned long allocsize;
    unsigned long begin;
    unsigned long sz;
}fifo;

void mkFifo(unsigned long maxsize, fifo * t);
int empty(fifo * f);
int full(fifo * f);

unsigned long size(fifo * t);
void printTapis(fifo *t);
void enfiler(fifo *t, unsigned long p);
unsigned long * defiler(fifo * t);
#endif /* FIFO_H_ */