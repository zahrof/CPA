/*
Maximilien Danisch
September 2017
http://bit.ly/danisch
maximilien.danisch@gmail.com

Info:
Feel free to use these lines as you wish. This program loads a graph in main memory.

To compile:
"gcc adjlist.c -O9 -o adjlist".

To execute:
"./adjlist edgelist.txt".
"edgelist.txt" should contain the graph: one edge on each line (two unsigned long (nodes' ID)) separated by a space.
The prograph will load the graph in main memory and then terminate.

Note:
If the graph is directed (and weighted) with selfloops and you want to make it undirected unweighted without selfloops, use the following linux command line.
awk '{if ($1<$2) print $1" "$2;else if ($2<$1) print $2" "$1}' net.txt | sort -n -k1,2 -u > net2.txt

Performance:
Up to 200 million edges on my laptop with 8G of RAM: takes more or less 4G of RAM and 30 seconds (I have an SSD hardrive) for 100M edges.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
#include "adjarray.h"
#include <string.h>

#define NLINKS 100000000 //maximum number of edges for memory allocation, will increase if needed


//compute the maximum of three unsigned long
unsigned long max3(unsigned long a,unsigned long b,unsigned long c){
    a=(a>b) ? a : b;
    return (a>c) ? a : c;
}

//reading the edgelist from file
adjlist* readedgelist(char* input){
    unsigned long e1=NLINKS;
    FILE *file=fopen(input,"r");
    FILE *results=fopen("bfs-RESULTS.txt","a");
    fprintf(results, "A graph where each line is of the form u v : \n");


    adjlist *g=malloc(sizeof(adjlist));
    g->n=0;
    g->e=0;
    g->edges=malloc(e1*sizeof(edge));//allocate some RAM to store edges
    unsigned long lines =0;

    while (fscanf(file,"%lu %lu", &(g->edges[g->e].s), &(g->edges[g->e].t))==2) {
        g->n=max3(g->n,g->edges[g->e].s,g->edges[g->e].t);
        fprintf(results,"%d %d\n",(int) g->edges[g->e].s,(int)g->edges[g->e].t);
        if (++(g->e)==e1) {//increase allocated RAM if needed
            e1+=NLINKS;
            g->edges=realloc(g->edges,e1*sizeof(edge));
        }
        lines ++;
    }
    printf("lines %lu", lines);
    fclose(file);
    fclose(results);

    g->n++;

    g->edges=realloc(g->edges,g->e*sizeof(edge));

    return g;
}

//building the adjacency matrix
void mkadjlist(adjlist* g, char* input){
    unsigned long i,u,v;
    unsigned long *d=calloc(g->n,sizeof(unsigned long));

    g->t=0;

    for (i=0;i<g->e;i++) {
        d[g->edges[i].s]++;
        d[g->edges[i].t]++;
    }

    g->cd=malloc((g->n+1)*sizeof(unsigned long));
    g->cd[0]=0;
    for (i=1;i<g->n+1;i++) {
        g->cd[i]=g->cd[i-1]+d[i-1];
        d[i-1]=0;
    }

    g->adj=malloc(2*g->e*sizeof(unsigned long));

    for (i=0;i<g->e;i++) {
        u=g->edges[i].s;
        v=g->edges[i].t;
        g->adj[ g->cd[u] + d[u]++ ]=v;
        g->adj[ g->cd[v] + d[v]++ ]=u;
    }

    /** COUNTING THE NUMBER OF NODES **//*
    FILE *fp;
    char path[1035];
    *//* Open the command for reading. *//*
    char str[500];
    strcpy(str, "wc -l ");
    strcat(str, input);

    fp = popen(str, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    *//* Read the output a line at a time - output it.*//*
    const char * str2 = fgets(path, sizeof(path), fp);
   g->k = (unsigned long )atoi(str2);*/

/*
    *//* close *//*
    pclose(fp);*/

    free(d);
    //free(g->edges);
}


//freeing memory
void free_adjlist(adjlist *g){
    free(g->edges);
    free(g->cd);
    free(g->adj);
    free(g);
}
void print_graph_cd(adjlist * g){
    printf("/******* CUMULATIVE DEGREE ********/ \n");
    for(int i = 0; i <=g->n; i++){
        printf("cd[%d]: %ld \n", i, g->cd[i]);
    }
}

void print_graph_adj(adjlist * g){
    printf("/******* ADJACENCE LIST ********/ \n");
    for (int i =0; i < g->n; i ++){
        //printf("voisin de %d: %ld \n", i, g->adj[g->cd[i]]);
        for(int j = g->cd[i]; j <g->cd[i+1]; j++){
            printf("voisin de %d: %ld \n", i, g->adj[j]);
        }
    }


}


