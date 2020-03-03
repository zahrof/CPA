#include <stdio.h>
#include <time.h>
#include "Structures/adjarray.h"
#include "Algorithms/algorithms.h"

int main(int argc,char** argv){
    adjlist* g;
    time_t t1,t2;
    FILE * fp = fopen("toto.txt","w");
    t1=time(NULL);

    printf( "Reading edgelist from file %s\n",argv[1]);
    g=readedgelist(argv[1]);

    fprintf(fp,"Value of the node max: %lu\n",g->n);
    fprintf(fp,"Number of edges: %lu\n",g->e);

    printf("Building the adjacency list\n");
    mkadjlist(g, argv[1]);

    // algorithm to implement
//   breadthFirstSearch(g,fp);
    diameter(g, fp);
    //triangles(g, argv[1]);

    t2=time(NULL);

    fprintf(fp,"- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));


    free(fp);
    free_adjlist(g);
    fclose(fp);
    return 0;
}