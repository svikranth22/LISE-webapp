#include <stdio.h>
#include <stdlib.h>
#include "lise.h"


int main(int argc, char *agrv[]) {
    
    int numLines;
    if (fscanf(stdin, "%d", &numLines) != 1) {
        return EXIT_FAILURE;
    }

    IPRO ipro;
    IPRO_STATS ipro_st;
    int **dists;

    
    GRID grid;

    createipro(numLines, &ipro);
    setipro(stdin, &ipro);

    createiprostats(numLines, &ipro_st);
    setiprostats(&ipro, &ipro_st);

    creategrid(&ipro_st, &grid);
    setgocc(&ipro, &ipro_st, &grid);
    setgscore(&ipro, &ipro_st, &grid);
    setgloc(&grid);
    setsscore(&ipro_st, &grid);

}

