#ifndef IPRO_H
#define IPRO_H

#include "lise.h"

typedef struct IPRO {
	int numAtoms;
	ATOM *atoms;
}IPRO;

typedef struct STATS {
	int min;
	int max;
	int range;
}STATS;

typedef struct IPRO_STATS {
    STATS X;
    STATS Y;
    STATS Z;
    int **dists;
}IPRO_STATS;

void createipro(int numLines, IPRO *restrict ipro) {
    ipro->numAtoms = numLines;
    ipro->atoms = (ATOM *)malloc(numLines * sizeof(ATOM));
}

int setipro(FILE *restrict file, IPRO *restrict ipro) {
    int ret = 0;
    for (int i = 0; i < ipro->numAtoms; i++) {
        if (makeatom(file, ipro->atoms+ret) != 1)
            return ret;
        ret++;
    }

    return ret;
}

void initstats(STATS *restrict s) {
    s->max = MAX;
    s->min = MIN;
    s->range = 0;
}
void setstats(int n, STATS *restrict s) {
    if (n > s->max) {
        s->max = n;
        return;
    } else if ((n < s->min)) {
        s->min = n;
        return;
    }
}

void finstats(STATS *restrict s) {
    s->max = floor(s->max + ast) + 1;
	s->min = floor(s->min - ast);
	s->range = s->max - s->min+1;
}

void createiprostats(int numLines, IPRO_STATS *restrict ipro_st) {
    initstats(&ipro_st->X);
    initstats(&ipro_st->Y);
    initstats(&ipro_st->Z);
    ipro_st->dists = (int **)malloc(numLines * sizeof(int *));
    for (int i = 0; i < numLines; i++) {
        ipro_st->dists[i] = (int *)malloc(numLines * sizeof(int));
    }
}

int setiprostats(const IPRO *restrict ipro, IPRO_STATS *restrict ipro_st) {
    int tmp;
    int ret = 0;

    for (int i = 0; i < ipro->numAtoms; i++) {
        setstats(ipro->atoms[i].x, &ipro_st->X);
        setstats(ipro->atoms[i].x, &ipro_st->Y);
        setstats(ipro->atoms[i].x, &ipro_st->Z);

        for (int j = i+1; j < ipro->numAtoms; j++) {
            tmp = sqrt(pow(ipro->atoms[i].x - ipro->atoms[j].x, 2) + pow(ipro->atoms[i].y - ipro->atoms[j].y, 2) + pow(ipro->atoms[i].z - ipro->atoms[j].z, 2));
            
            if (tmp < 0)
                return ret;
			if (tmp < 2)
				ipro_st->dists[i][j] = 0;
			else if (tmp > 13)
				ipro_st->dists[i][j] = 0;
			else if (tmp > 10)
				ipro_st->dists[i][j] = 2;
			else
				ipro_st->dists[i][j] = 1;
            
            ret++;
        }
    }

    finstats(&ipro_st->X);
    finstats(&ipro_st->Y);
    finstats(&ipro_st->Z);

    return ret;
}

#endif