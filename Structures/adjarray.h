/*
 * adjarrayTRI.h
 *
 *  Created on: Feb 19, 2020
 *      Author: zahrof
 */

#ifndef ADJARRAY_H_
#define ADJARRAY_H_

typedef struct {
    unsigned long s;
    unsigned long t;
} edge;


//edge list structure:
typedef struct {
    unsigned long n;
    unsigned long e;//number of edges
    unsigned long t;// number of triangles t from 0 to t-1
    edge *edges;//list of edges
    unsigned long *cd;//cumulative degree cd[0]=0 length=n+1
    unsigned long *adj;//concatenated lists of neighbors of all nodes
} adjlist;

//compute the maximum of three unsigned long
unsigned long max3(unsigned long a,unsigned long b,unsigned long c);

//reading the edgelist from file
adjlist* readedgelist(char* input);

//building the adjacency matrix
void mkadjlist(adjlist* g, char* input);

//freeing memory
void free_adjlist(adjlist *g);

void print_graph_cd(adjlist * g);

void print_graph_adj(adjlist * g);

#endif /* ADJARRAY_H_ */