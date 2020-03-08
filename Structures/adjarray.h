/*
 * adjarrayTRI.h
 *
 *  Created on: Feb 19, 2020
 *      Author: zahrof
 */

#ifndef ADJARRAY_H_
#define ADJARRAY_H_


#include "edgelist.h"

//edge list structure:
typedef struct {
    unsigned long n;
    unsigned long e;//number of edges
    edge *edges;//list of edges we should nout use it for the exercices
    unsigned long *cd;//cumulative degree cd[0]=0 length=n+1
    unsigned long *adj;//concatenated lists of neighbors of all nodes
} adjlist;

//compute the maximum of three unsigned long
unsigned long maxadjarray(unsigned long a, unsigned long b, unsigned long c);

//reading the edgelist from file
adjlist* readadjlist(char* input);

//building the adjacency matrix
void mkadjlist(adjlist* g, char* input);

//freeing memory
void free_adjlist(adjlist *g);

void print_graph_cd(adjlist * g);

void print_graph_adj(adjlist * g);

#endif /* ADJARRAY_H_ */