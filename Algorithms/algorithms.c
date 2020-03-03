//
// Created by zahrof on 22/02/2020.
//

#include <time.h>
#include "algorithms.h"
#include"../Structures/minHeap.h"




void BFS(adjlist *g, fifo *f, int *marked, unsigned long s, int * size, FILE * fp) {
    //(*size)++;
    enfiler(f, s);
    marked[s] = 1;

    while (!empty(f)) {
        unsigned long u = defiler(f);

        printf(" Node: %lu \n", u);
        fprintf(fp," Node: %lu \n", u);
        for (int i = g->cd[u]; i < g->cd[u + 1]; i++) {
            unsigned long v = g->adj[i];
            if (marked[v] == 0) {
               // (*size)++;
                enfiler(f, v);
                marked[v] = 1;
            }
        }
    }

}
//https://cs.stackexchange.com/questions/194/the-time-complexity-of-finding-the-diameter-of-a-graph
void  BFSdiam(adjlist *g, unsigned long s, FILE *fp, int * depth, unsigned long * depthNode) {
    int *marked = (int *) calloc(g->n, sizeof(int));

    fifo f;
    mkFifo((size_t) g->n, &f);

    enfiler(&f, s);
    marked[s] = 1;
    unsigned long *dist = (unsigned long *) calloc(g->n, sizeof(unsigned long));
    dist[s]=0;

    while (!empty(&f)) {
        unsigned long u = defiler(&f);
        fprintf(fp," Node: %lu \n", u);
        for (int i = g->cd[u]; i <g->cd[u + 1]; i++) {
            unsigned long v = g->adj[i];
            if (marked[v] != 1 ) {
                dist[v]=dist[u]+1;
                if (dist[v]>(*depth)){
                    *depth = dist[v];
                    (*depthNode)=v;
                }
                enfiler(&f, v);
                marked[v] = 1;
            }
        }
    }
    free (dist);
    free(f.tab);
    free(marked);

    //printf("depth %d %lu", *depth, *depthNode);

}

void breadthFirstSearch(adjlist *g, FILE *fp) {
    /** Initializing the fifo  **/
    fifo f;
    mkFifo((size_t) g->n, &f);
    /** Initializing the marked array  **/
    int *marked = (int *) calloc(g->n, sizeof(int));
    int max=0;
    int components=0;
    int scanned = 0;
    while (!scanned) {
        scanned = 1;
        for (int j = 0; j < g->n; j++) {
            if (!marked[j]) {
                marked[j] = 1;
                //dernier degre?, il se passe quoi?
                unsigned long degree = g->cd[j + 1] - g->cd[j];
                if (degree != 0) {
                    int size=0;
                    components++;
                    scanned = 0;
                    fprintf(fp,"\nBFS for the %d° component : \n", components);
                    BFS(g, &f, marked, j, &size,fp);
                    fprintf(fp,"Number of nodes of the connected component: %d \n", size);
                    if(max<size)max = size;
                }
            }
        }
    }
    free(marked);
    free(f.tab);
    fprintf(fp,"\nThe largest component has a size of : %d \n", max);
}

void diameter(adjlist *g, FILE *fp) {
    int alpha =5;
    time_t t;
    srand((unsigned) time(&t));

    unsigned long * u = (unsigned long  *) calloc(1, sizeof(unsigned long));
    unsigned long * v = (unsigned long  *) calloc(1, sizeof(unsigned long));
    int * depth2= (int *) calloc(1, sizeof(int));
    int * depth= (int *) calloc(1, sizeof(int));

    int max=0;
    for (int i=0; i<alpha; i++){
        int j = (rand()%g->n)+1;

        unsigned long w = g->adj[j];
        unsigned long degree = g->cd[w + 1] - g->cd[w];
       if (degree == 0) continue;
        BFSdiam(g, w, fp, depth, u);
        BFSdiam(g, *u, fp, depth2, v);
        if(*depth2 > max)max = *depth2;
    }

    printf("\ntest %d ", max);
    free(u);
    free(v);
    free(depth);
    free(depth2);

}


void triangles(adjlist * g, FILE *fp){
   MinHeap min;
   makeMinHeap(&min, g->n);
    FILE * fTri = fopen("triangles.txt","w");

    for(int i=0; i< g->n; i++){
        Pair p;
        unsigned long degree = g->cd[i + 1] - g->cd[i];
        p.node=i;
        p.degree = degree;
        if (degree != 0) {
            printf("inserting node: %lu, with degree %lu \n", p.node, p.degree);
            insertKey(&min, p);
        }
    }
    int size = min.heap_size;
    for(int i=0; i<size ;i++){
        //Pair p = extractMin(&min);
        printf("extracting node: %lu, with degree %lu, id: %d \n", min.array[i].node, min.array[i].degree, getIndex(&min,&min.array[i]));

    }

/*   maxHeap  max = initMaxHeap(g->n);

    for(int i=0; i< g->n; i++){
        Pair p;
        unsigned long degree = g->cd[i + 1] - g->cd[i];
        p.node=i;
        p.degree = degree;
        if (degree != 0) {
            printf("inserting node: %lu, with degree %lu \n", p.node, p.degree, p.id);
            insertKey(&min, p);
        }
    }
    int size = min.heap_size;
    for(int i=0; i<size ;i++){
        Pair p = extractMin(&min);
        printf("extracting node: %lu, with degree %lu, id: %d \n", p.node, p.degree, getIndex(&min,&p));

    }*/


}
