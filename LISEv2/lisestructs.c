#include "lisestructs.h"


int makeatom(FILE *restrict file, ATOM *restrict atom) {
    char str1[4];
    char str2[4];
    if ((fscanf(file, "%s %d %s %f %f %f %f %d",
        str1, &atom->rno, str2, &atom->x, &atom->y, &atom->z, &atom->r, &atom->at)) == 8) {
        
        atom->aa = malloc(strlen(str1)+1);
        strcpy(atom->aa, str1);
        atom->aa[strlen(str1)] = '\0';
        atom->nom = malloc(strlen(str2)+1);
        strcpy(atom->nom, str2);
        atom->nom[strlen(str1)] = '\0';
        
        return 1;
    }
    return 0;
}
void statminmax(const float n, STAT *restrict stat) {
    if (n > stat->max) {
        stat->max = n;
        return;
    } else if ((n < stat->min)) {
        stat->min = n;
        return;
    }
}
void setinitstats(STAT *restrict stat) {
    stat->max = MAX;
	stat->min = MIN;
	stat->range = 0;
}

void setfinalstats(STAT *restrict stat) {
    stat->max = floor(stat->max + ast) + 1;
	stat->min = floor(stat->min - ast);
	stat->range = stat->max - stat->min+1;
}

int makeipro(FILE *restrict file, IPRO *restrict ipro) {
    int num = 0;
    
    if (fscanf(file, "%d", &(ipro->num)) != 1)
        return num;
    
    setinitstats(&ipro->X);
    setinitstats(&ipro->Y);
    setinitstats(&ipro->Z);

    ATOM *atomptr = (ATOM *)malloc(sizeof(ATOM) * ipro->num);
    ipro->dists = (int **)calloc(ipro->num, sizeof(int *));
    //ipro->go = (char ***)calloc(ipro->num, sizeof(char **));
    //ipro->gs = (float ***)calloc(ipro->num, sizeof(float **));
    //ipro->ss = (float ***)calloc(ipro->num, sizeof(float **));
    

    while(makeatom(file, atomptr+num) == 1) {
        statminmax(atomptr->x, &ipro->X);
        statminmax(atomptr->y, &ipro->Y);
        statminmax(atomptr->z, &ipro->Z);

        ipro->dists[num] = calloc(ipro->num, sizeof(int));
        //ipro->go = (char **)calloc(ipro->num, sizeof(char *));
        //ipro->gs = (float **)calloc(ipro->num, sizeof(float *));
        //ipro->ss = (float **)calloc(ipro->num, sizeof(float *));

        //for (int c = 0; c < ipro->num; c++) {
            //ipro->go = (char *)calloc(ipro->num, sizeof(char));
            //ipro->gs = (float *)calloc(ipro->num, sizeof(float));
            //ipro->ss = (float *)calloc(ipro->num, sizeof(float));
        //}
        num++;
    }

    setfinalstats(&ipro->X);
    setfinalstats(&ipro->Y);
    setfinalstats(&ipro->Z);
    ipro->atoms = atomptr;
    
    return num;
}

int setiprodists(IPRO *restrict ipro) {
    int tmp;
    int num = 0;
    for (int i = 0; i < ipro->num; i++) {
        for (int j = i+1; j < ipro->num; j++) {
            tmp = sqrt(pow(ipro->atoms[i].x - ipro->atoms[j].x, 2) + pow(ipro->atoms[i].y - ipro->atoms[j].y, 2) + pow(ipro->atoms[i].z - ipro->atoms[j].z, 2));
			if (tmp < 2)
				ipro->dists[i][j] = 0;
			else if (tmp > 13)
				ipro->dists[i][j] = 0;
			else if (tmp > 10)
				ipro->dists[i][j] = 2;
			else
				ipro->dists[i][j] = 1;
            
            num++;
        }
    }
    return num;
}
int setgridocc(IPRO *restrict ipro, Grids *restrict grid) {
    int xu, yu, zu, xl, yl, zl, xmin, ymin, zmin;
    float x,y,z;
    xmin = ipro->X.min, ymin = ipro->Y.min, zmin = ipro->Z.min;
    int num = 0;
    for (int l = 0; l < ipro->num; l++) {
        x = ipro->atoms[l].x, y = ipro->atoms[l].y, z = ipro->atoms[l].z; 
		xu = floor(x + ot) + 1, xl = floor(x - ot);
		yu = floor(y + ot) + 1, yl = floor(y - ot);
		zu = floor(z + ot) + 1, zl = floor(z - ot);
		for (int i = xl; i <= xu; i++) {
			for (int j = yl; j <= yu; j++) {
				for (int k = zl; k <= zu; k++) {
					if (sqrt(pow(x - (float)i, 2) + pow(y - (float)j, 2) + pow(z - (float)k, 2)) <= ot) {
                        grid->occ[i - xmin][j - ymin][k - zmin] = 1;
                        num++;
                    }
				}
			}
		}
	}
    return num;
}

int setgridscore(IPRO *restrict ipro, Grids *restrict grid) {
    int xu, yu, zu, xl, yl, zl;
	float ts, cx, cy, cz, tmp; //ts: triangle score
	for (int i = 0; i < ipro->num; i++) {
		for (int j = i + 1; j < ipro->num; j++) {
			if (ipro->dists[i][j] >= 1) {
                for (int k = j + 1; k < ipro->num; k++) {
                    if (ipro->dists[i][k] >= 1 && ipro->dists[j][k] >= 1 && ipro->dists[i][j] + ipro->dists[i][k] + ipro->dists[j][k] <= 4) {
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
                            if (xu > ipro->X.max) xu = ipro->X.max;
                            if (yu > ipro->Y.max) yu = ipro->Y.max;
                            if (zu > ipro->Z.max) xu = ipro->Z.max;
                            for (int a = xl; a <= xu; a++) {
                                for (int b = yl; b <= yu; b++) {
                                    for (int c = zl; c <= zu; c++) {
                                        if (grid->occ[a - ipro->X.min][b - ipro->Y.min][c - ipro->Z.min] == 0) {
                                            tmp = sqrt(pow(cx - (float)a, 2) + pow(cy - (float)b, 2) + pow(cz - (float)c, 2));
                                            if (tmp <= ast) {
                                                grid->score[a - ipro->X.min][b - ipro->Y.min][c - ipro->Z.min] += ts;
                                            }
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
}

ILIG *makeilig(FILE *restrict file) {

    ILIG *ilig = (ILIG *)malloc(sizeof(ILIG));
    ilig->len = 1;
	ilig->x = malloc((ilig->len * sizeof(float)));
	ilig->y = malloc((ilig->len * sizeof(float)));
	ilig->z = malloc((ilig->len * sizeof(float)));
    int i;

    while ((fscanf(file, "%*s %*d %*s %f %f %f",
        (ilig->x + (ilig->len-1)), (ilig->y + (ilig->len-1)),
        (ilig->z + (ilig->len-1)))) == 3) {

        ilig->len++;
	    ilig->x = realloc(ilig->x, (ilig->len * sizeof(float)));
	    ilig->y = realloc(ilig->y, (ilig->len * sizeof(float)));
	    ilig->z  = realloc(ilig->z, (ilig->len * sizeof(float)));

    }

    return ilig;
}

int main(void) {
    IPRO ipro;
    printf("%d\n",makeipro(stdin, &ipro));
    setiprodists(&ipro);
}