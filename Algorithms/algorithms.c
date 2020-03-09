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


void triangles(adjlist * g, char  *fp, char * results) {
   g_global = g;
    unsigned long numberTriangles=0;
    /*********** ORDERING DEGREES  ***************/
/*    unsigned long *ordered = (unsigned long *) calloc(g->n, sizeof(unsigned long));

    MinHeap min;
    makeMinHeap(&min, g->n);
    for (unsigned long i = 0; i < g->n; i++) {
        unsigned long degree = g_global->cd[i + 1] - g_global->cd[i];
        if (degree == 0) continue;
        insertKey(&min, degree, i);
    }
    unsigned long compteur = 1;
    unsigned long size_heap = min.heap_size;
    for (unsigned long i = 0; i < size_heap; i++) {
        unsigned long u = extractMin(&min);
       printf(" ordered[%lu]: %lu is %lu \n", i, u, compteur);
        ordered[u] = compteur;
        compteur++;
    }
    deleteMinHeap(&min);*/

    //*********** REINDEXING DEGREES  ***************//
/*   FILE *file = fopen(fp, "r"); // file to read
    FILE *f = fopen("aux-triangle.txt", "w"); // file to write
    unsigned long *x = malloc(sizeof(unsigned long));
    unsigned long *w = malloc(sizeof(unsigned long));

    while (fscanf(file, "%lu %lu", &x, &w) == 2) {
        printf("x: %lu, w: %lu is %lu and %lu \n", x, w, ordered[(unsigned long) x],ordered[(unsigned long) w]);
        // faire le fprintf d'une traite pour gagner du temps?
        fprintf(f, "%lu %lu\n", ordered[(unsigned long) x], ordered[(unsigned long) w]);
    }
    fclose(f);
    free(ordered);*/
    //*********** RECREATING GRAPH  ***************//
/*    FILE *f2 = fopen("aux-triangle.txt", "a");
    g_global = readadjlist("aux-triangle.txt");
    mkadjlist(g_global, "aux-triangle.txt");
    fclose(f2);*/

    //*********** STOCKING NEIGHBORD OF ..  ***************//

    //unsigned long *neighbors = malloc(NLINKS * sizeof(unsigned long));
   // unsigned long *cdAux = calloc(g_global->n+1, sizeof(unsigned long));
    edgelist elist;
    initalize_edgelist(&elist, 925900);
    fifo fifo;
    mkFifo((size_t) g_global->n, &fifo);
    g_global->cd[0]=0;
   // cdAux[0] = 0;
    unsigned long sizeFifo = 0;

    // Truncate the neighbors
    printf("g_global->n : %lu \n", g_global->n);
    for (unsigned long i = 1; i <=g_global->n; i++) {
        for (unsigned long j = g_global->cd[i]; j < g_global->cd[i + 1]; j++) {
            if (g_global->adj[j] > i) {
               // printf("noeud %lu -> voisin %lu \n", i, g_global->adj[j]);

                enfiler(&fifo, g_global->adj[j]);
                add_edge(&elist, i, g_global->adj[j]);
            }
        }
        g_global->cd[i] = g_global->cd[i - 1] + fifo.sz;
        sizeFifo = sizeFifo + size(&fifo);
        for (unsigned long j = g_global->cd[i - 1]; j < g_global->cd[i]; j++){
            g_global->adj[j] = *defiler(&fifo);
        }
        mkFifo((size_t) g_global->n, &fifo);
    }
    free(fifo.tab);
    g_global->adj = realloc(g_global->adj, sizeFifo * sizeof(unsigned long));
    unsigned long *p = g_global->adj;

    // Ordering the neigbors
    for (unsigned long i = 1; i <=g_global->n; i++) {
        qsort(p, g_global->cd[i] - g_global->cd[i - 1], sizeof(unsigned long), compare);
        for (unsigned long j = g_global->cd[i - 1]; j < g_global->cd[i]; j++) p++;
    }
   for (unsigned long i = 1; i <= g_global->n; i++) {
       printf("voisin : %lu \n", i );
        //printf("cdAux[%lu] : %lu \n", i, g_global->cd[i] );
        for(unsigned long j = g_global->cd[i-1]; j <  g_global->cd[i]; j++){
            printf("voising de %lu is %lu \n", i , g->adj[j]);
        }

    }

    for (unsigned long i = 0; i < elist.e; i++) {
        for (unsigned long j = g_global->cd[elist.edges[i].s - 1]; j < g_global->cd[elist.edges[i].s]; j++) {
            for (unsigned long k = g_global->cd[(elist.edges[i].t) - 1]; k < g_global->cd[elist.edges[i].t]; k++) {
                if(((elist.edges[i].t==elist.edges[i].s)||(elist.edges[i].t==g_global->adj[j]))||(elist.edges[i].s==g_global->adj[j])) continue;
               // printf("triangle %lu %lu %lu neighbors [k] %lu \n", neighbors[j], elist.edges[i].t, elist.edges[i].s, neighbors[k]);
                if (g_global->adj[k] == g_global->adj[j]) {
                    printf("tata triangle %lu %lu %lu neighbors [k] %lu \n", g_global->adj[j], elist.edges[i].t, elist.edges[i].s,g_global->adj[k]);
                    numberTriangles++;
                }
            }
        }
    }
    printf("Number triangles %lu ", numberTriangles);
    free(elist.edges);
    //free(neighbors);
    //free(g_global->cd);
}

