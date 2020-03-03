//
// Created by zahrof on 21/02/2020.
//

#include "FIFO.h"

void mkFifo(size_t maxsize, fifo * t){
    t->allocsize= maxsize;
    t->begin=0;
    t->sz=0;
    t->tab=calloc(maxsize,sizeof(unsigned long));
}


int empty(fifo * f){
    return (f->sz ==0);
}
int full(fifo * f){
    return (f->sz ==f->allocsize);
}
size_t size(fifo * t){
    return t->sz;
}
void printTapis(fifo *t){
    if(t->sz==0)printf("Le tapis est vide\n");
   // if(t->begin==t->sz) printf("%ld eme élément du tapis: %lu \n",t->begin, t->tab[t->begin]);
    else{
        for (int i=0; i<t->allocsize; i++)
            printf("%d eme élément du tapis: %ld\n",i, t->tab[i]);
    }
    printf("\n");
}

unsigned long  defiler(fifo * t){
    unsigned long  p = t->tab[t->begin];
    t->tab[t->begin]=NULL;
    t->sz--;
    t->begin=(t->begin+1)%t->allocsize;
    return p;
}

void enfiler(fifo *t, unsigned long  p){
    t->tab[(t->begin+t->sz)%t->allocsize]=p;
    t->sz++;
}