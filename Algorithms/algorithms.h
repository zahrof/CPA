//
// Created by zahrof on 22/02/2020.
//

#ifndef CPA_TRUE_ALGORITHMS_H
#define CPA_TRUE_ALGORITHMS_H

#include "../Structures/adjarray.h"
#include "../Structures/FIFO.h"
//https://www.geeksforgeeks.org/shortest-path-unweighted-graph/

// https://cs.stackexchange.com/questions/194/the-time-complexity-of-finding-the-diameter-of-a-graph

//In general, if you want to guarantee the diameter of a graph you need to do a BFS (Dijkstra in a weighted graph) from every state and then take the maximum over all searches. (Or compute the all-pairs shortest-path information and find the longest shortest path from that data.)
void BFS(adjlist *g, fifo *f, int *marked, unsigned long s, int * size, FILE * fp);
void breadthFirstSearch(adjlist * g,FILE *fp);
void diameter(adjlist *g, FILE *fp);

void triangles(adjlist * g, char * fp);


#endif //CPA_TRUE_ALGORITHMS_H
