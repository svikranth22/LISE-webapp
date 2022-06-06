#ifndef GRID_H
#define GRID_H

#include "lise.h"

typedef struct GRID {
	char ***occ; //grid occupied
	float ***score; //grid score
	float loc[10][10][10];

	struct Sphere {
		float max;
		float ***score;
	}s;

}GRID;

void creategrid(const IPRO_STATS *restrict ipro_st, GRID *restrict grid) {

    grid->occ = (char ***)calloc(ipro_st->X.range, sizeof(char**));
    grid->score = (float ***)calloc(ipro_st->X.range, sizeof(float**));
    grid->s.score = (float ***)calloc(ipro_st->X.range, sizeof(float**));

    for (int i = 0; i < ipro_st->X.range; i++) {
        grid->occ[i] = (char **)calloc(ipro_st->Y.range, sizeof(char*));
        grid->score[i] = (float **)calloc(ipro_st->Y.range, sizeof(float*));
        grid->s.score[i] = (float **)calloc(ipro_st->Y.range, sizeof(float*));
        for (int j = 0; j < ipro_st->Y.range; j++) {
            grid->occ[i][j] = (char **)calloc(ipro_st->Z.range, sizeof(char*));
            grid->score[i][j] = (float **)calloc(ipro_st->Z.range, sizeof(float*));
            grid->s.score[i][j] = (float **)calloc(ipro_st->Z.range, sizeof(float*));
        }
    }
}

int setgocc(const IPRO *restrict ipro, const IPRO_STATS *restrict ipro_st, GRID *restrict grid) {
    int xu, yu, zu, xl, yl, zl, tmp;
    float x,y,z;
    int ret = 0;
    for (int l = 0; l < ipro->numAtoms; l++) {
        x = ipro->atoms[l].x, y = ipro->atoms[l].y, z = ipro->atoms[l].z; 
		xu = floor(x + ot) + 1, xl = floor(x - ot);
		yu = floor(y + ot) + 1, yl = floor(y - ot);
		zu = floor(z + ot) + 1, zl = floor(z - ot);
		for (int i = xl; i <= xu; i++) {
			for (int j = yl; j <= yu; j++) {
				for (int k = zl; k <= zu; k++) {
					tmp = sqrt(pow(x - (float)i, 2) + pow(y - (float)j, 2) + pow(z - (float)k, 2));
                    
                    if (tmp < 0)
                        return ret;
                    if (tmp <= ot)
                        grid->occ[i - ipro_st->X.min][j - ipro_st->Y.min][k - ipro_st->Z.min] = 1;
                    
                    ret++;
				}
			}
		}
	}
    return ret;
}

int setgscore(const IPRO *restrict ipro, const IPRO_STATS *restrict ipro_st, GRID *restrict grid) {
    int xu, yu, zu, xl, yl, zl;
	float ts, cx, cy, cz, tmp; //ts: triangle score
    int ret = 0;
	for (int i = 0; i < ipro->numAtoms; i++) {
		for (int j = i + 1; j < ipro->numAtoms; j++) {
			if (ipro_st->dists[i][j] >= 1) {
                for (int k = j + 1; k < ipro->numAtoms; k++) {
                    if (ipro_st->dists[i][k] >= 1 && ipro_st->dists[j][k] >= 1 && ipro_st->dists[i][j] + ipro_st->dists[i][k] + ipro_st->dists[j][k] <= 4) {
                        int t[3] = { ipro->atoms[i].at, ipro->atoms[j].at, ipro->atoms[k].at};
                        sort(t, t + 3);
                        if (Fb[t[0]][t[1]][t[2]] > Eft) {
                            ts = Fb[t[0]][t[1]][t[2]];
                            cx = (ipro->atoms[i].x + ipro->atoms[j].x + ipro->atoms[k].x) / 3;
                            cx = (ipro->atoms[i].y + ipro->atoms[j].y + ipro->atoms[k].y) / 3;
                            cx = (ipro->atoms[i].z + ipro->atoms[j].z + ipro->atoms[k].z) / 3;
                            xu = floor(cx + ast) + 1, xl = floor(cx - ast);
                            yu = floor(cy + ast) + 1, yl = floor(cy - ast);
                            zu = floor(cz + ast) + 1, zl = floor(cz - ast);
                            if (xu > ipro_st->X.max) xu = ipro_st->X.max;
                            if (yu > ipro_st->Y.max) yu = ipro_st->Y.max;
                            if (zu > ipro_st->Z.max) xu = ipro_st->Z.max;
                            for (int a = xl; a <= xu; a++) {
                                for (int b = yl; b <= yu; b++) {
                                    for (int c = zl; c <= zu; c++) {
                                        if (grid->occ[a - ipro_st->X.min][b - ipro_st->Y.min][c - ipro_st->Z.min] == 0) {
                                            tmp = sqrt(pow(cx - (float)a, 2) + pow(cy - (float)b, 2) + pow(cz - (float)c, 2));
                                            
                                            if (tmp < 0)
                                                return ret;
                                            if (tmp <= ast)
                                                grid->score[a - ipro_st->X.min][b - ipro_st->Y.min][c - ipro_st->Z.min] += ts;

                                            ret++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
		}
	}//end triangle
    return ret;
}

void setgloc(GRID *restrict grid) {
    int tmp;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				tmp = sqrt(pow((float)i, 2) + pow((float)j, 2) + pow((float)k, 2));
				grid->loc[i][j][k] = tmp;
				//printf("%d,%d,%d,%4.2f\n",i,j,k,tmp3);    
			}
		}
	}
}

int setsscore(const IPRO_STATS *restrict ipro_st, GRID *restrict grid) {
	int iu, ju, ku, il, kl, jl;
    int ret = 0;
    for (int i = 0; i < ipro_st->X.range; i++) {
		for (int j = 0; j < ipro_st->Y.range; j++) {
			for (int k = 0; k < ipro_st->Z.range; k++) {
				if (grid->occ[i][j][k]) {
                    if (grid->score[i][j][k] > grid->s.max) grid->s.max = grid->score[i][j][k];
                    iu = floor(i + st) + 1, il = floor(i - st);
                    ju = floor(j + st) + 1, jl = floor(j - st);
                    ku = floor(k + st) + 1, kl = floor(k - st);
                    if (iu > ipro_st->X.range - 1) iu = ipro_st->X.range - 1;
                    if (ju > ipro_st->Y.range - 1) ju = ipro_st->Y.range - 1;
                    if (ku > ipro_st->Z.range - 1) ku = ipro_st->Z.range - 1;
                    if (il < 0) il = 0;
                    if (jl < 0) jl = 0;
                    if (kl < 0) kl = 0;
                    for (int a = il; a <= iu; a++) {
                        for (int b = jl; b <= ju; b++) {
                            for (int c = kl; c <= ku; c++) {
                                if (grid->occ[a][b][c]) {
                                    if (grid->loc[abs(i - a)][abs(j - b)][abs(k - c)] > st)
                                        grid->s.score[i][j][k] += grid->score[a][b][c];
                                        ret++;
                                }
                                //if (i == x_range-1) printf("dist %d,%d,%d,%d,%d,%d,%5.2f,%d,%7.3f,%12.2f,\n",i+xmn,j+ymn,k+zmn,a+xmn,b+ymn,c+zmn,loc[abs(i-a)][abs(j-b)][abs(k-c)],gd[a][b][c],gs[a][b][c],ss[i][j][k]);//tmp3,gd[a-xmn][b-ymn][c-zmn],gs[a-xmn][b-ymn][c-zmn]);
                            }
                        }
                    }
                }
			}
		}
	}
    return ret;
}

#endif