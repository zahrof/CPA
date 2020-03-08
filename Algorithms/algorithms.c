//
// Created by zahrof on 22/02/2020.
//

#include <time.h>
#include "algorithms.h"
#include"../Structures/minHeap.h"
#include "../Structures/adjarray.h"

#define NLINKS 100000000


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
        unsigned long j = (rand()%g->n)+1;

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
adjlist * g_global;

static int compare (const void * first, const void * second){
    unsigned long dF= (g_global->cd[*(unsigned long*)first+1])-(g_global->cd[*(unsigned long*)first]);
    unsigned long dS= (g_global->cd[*(unsigned long*)second+1])-(g_global->cd[*(unsigned long*)second]);
    return (dF)-(dS);
}


int sizeIntersection  ( unsigned long * U,int sizeU, unsigned long * V, int sizeV){
    int sizeW=0;

    for (int i=0; i< sizeU; i++ ){
        for (int j=0; j < sizeV; j++){
            if (U[i]==V[j]){
                sizeW++;
            }
        }
    }
    return sizeW;
}

unsigned long * intersection ( unsigned long * U,int sizeU, unsigned long * V, int sizeV){

    int size = sizeIntersection(U,sizeU,V, sizeV);
    unsigned long * W = malloc (size * sizeof(unsigned long));

    int curW=0;
    for (int i=0; i< sizeU; i++ ){
        for (int j=0; j < sizeV; j++){
            if (U[i]==V[j]){
                W[curW]=U[i];
                curW++;
            }
        }
    }

    return W;
}

void triangles(adjlist * g, char  *fp) {
    // il y a une autre méthode aussi, à expliquer dans le rapport et si temps à implementer
    /*********** ORDERING DEGREES  ***************/
    unsigned long *ordered = (unsigned long *) calloc(g->n, sizeof(unsigned long));
    for (unsigned long j = 0; j < g->n; j++)  ordered[j] = j;

    g_global = g;
    qsort(ordered, g->n, sizeof(unsigned long), compare);

    for (unsigned long j = 0; j < g->n; j++) {
        printf("ordered : %lu\n", ordered[j]);
    }
    /*********** REINDEXING DEGREES  ***************/
    FILE *file = fopen(fp, "r"); // file to read
    FILE * f = fopen ("aux-triangle.txt","w"); // file to write
    unsigned long *x = malloc(sizeof(unsigned long));
    unsigned long *w = malloc(sizeof(unsigned long));

    unsigned long *aux = (unsigned long *) calloc(g->n, sizeof(unsigned long));
    while (fscanf(file, "%lu %lu", &x, &w) == 2){
        printf("x: %lu, w: %lu\n", x, w);
        for (int i = 0; i < g->n; i++){
            if (ordered[i]==w) aux[ordered[i]]=i;
            if (ordered[i]==x)aux[ordered[i]]=i;
        }
        // faire le fprintf d'une traite pour gagner du temps?
        fprintf(f, "%lu %lu\n", aux[(unsigned long)x], aux[(unsigned long)w]);
    }
    fclose(f);

    free(g);
    free(ordered);
    free(aux);
    /*********** RECREATING GRAPH  ***************/
    FILE * f2 = fopen ("aux-triangle.txt","a");
    g_global= readadjlist("aux-triangle.txt");

    printf("Building the adjacency list\n");
    mkadjlist(g_global, "aux-triangle.txt");

    fclose(f2);

    /*********** STOCKING NEIGHBORD OF ..  ***************/
    unsigned long * neighbors = malloc(NLINKS * sizeof(unsigned long));
    unsigned long * cdAux = calloc (g_global->n, sizeof(unsigned long));
    edgelist elist;
    initalize_edgelist(&elist,g_global->n);
    fifo fifo;
    mkFifo((size_t) g_global->n, &fifo);
    cdAux[0]=0;
    unsigned long sizeFifo =0;

    for ( unsigned long i =1; i < g_global->n; i++){
        for (int j = g_global->cd[i]; j < g_global->cd[i+1]; j++){
            if (g_global->adj[j]> i) {
                enfiler(&fifo, g_global->adj[j]);
                add_edge(&elist, i,  g_global->adj[j]);
            }
        }
        cdAux[i]= cdAux[i-1]+fifo.sz;
        sizeFifo = sizeFifo + size(&fifo);
        for(unsigned long j=cdAux[i-1]; j < cdAux[i]; j++) neighbors[j]=*defiler(&fifo);

        mkFifo((size_t) g_global->n, &fifo);
    }
    for (unsigned long i =1; i < g_global->n; i ++)
        printf("cdAux[%d]:%lu\n", i, cdAux[i]);
    neighbors=realloc(neighbors, sizeFifo * sizeof(unsigned long));
    unsigned long * p = neighbors;

    for (unsigned long i =1; i < g_global->n; i ++){
        qsort(p,cdAux[i]-cdAux[i-1], sizeof(unsigned long), compare);
       for(int j=cdAux[i-1]; j < cdAux[i]; j++) p++;
    }
    for (unsigned long i =1; i < sizeFifo; i ++){
        for(unsigned long j = cdAux[i-1]; j <cdAux[i]; j++){
           // printf("voisin de %d: %lu \n", i, neighbors[j]);
        }
    }

    for(unsigned long i =0 ; i < elist.e; i++){
            for(unsigned long j = cdAux[elist.edges[i].s-1]; j <cdAux[elist.edges[i].s]; j++){
                for(unsigned long k = cdAux[(elist.edges[i].t)-1]; k <cdAux[elist.edges[i].t]; k++){
                  if(neighbors[k]==neighbors[j]) printf ("triangle %lu %lu %lu", neighbors[j], elist.edges[i].t, elist.edges[i].s);
                }
            }
            printf("\n\n");
    }
}


