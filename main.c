#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "Structures/adjarray.h"
#include "Algorithms/algorithms.h"

char **convertToNameFile(char **name_file);

char** str_split(char* a_str, const char a_delim)
{
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    return strtok(last_comma, delim);;
}

char **convertToNameFile(char **name_file) {
    char * res="";
    char * ptr = name_file;
    while(*ptr !="."&&(ptr++=="t")){
        res += *ptr;
    }res +='\n';
    return res;
}

int main(int argc,char** argv){
    adjlist* g;
    time_t t1,t2;
    FILE * results = fopen("toto.txt","w");
    t1=time(NULL);

    printf( "Reading edgelist from file %s\n",argv[1]);
    g= readadjlist(argv[1]);

    fprintf(results,"Value of the node max: %lu\n",g->n);
    fprintf(results,"Number of edges: %lu\n",g->e);

    printf("Building the adjacency list\n");
    mkadjlist(g, argv[1]);

    char** tokens;




    // algorithm to implement
//   breadthFirstSearch(g,fp);
//    diameter(g, fp);
    triangles(g, argv[1],results);

    t2=time(NULL);

    fprintf(results,"- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

    free(tokens);
    free(results);
    free_adjlist(g);
    fclose(results);
    return 0;
}


