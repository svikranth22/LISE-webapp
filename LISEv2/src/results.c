#include "lise.h"

	const int rank = 10;
	float record[rank];
	int lx[rank], ly[rank], lz[rank];
	bool success[rank];
	ofstream ofs("./results/1a6w_top10.pdb", ios::out);

void printtop10(const IPRO_STATS *restrict ipro_st, const GRID *restrict grid, FILE *restrict file) {
    int tmp;
    char tooClose = 0;
    for (int l = 0; l < rank; l++) {
		record[l] = 0;
		lx[l] = 0;
		ly[l] = 0;
		lz[l] = 0;

		for (int i = 0; i < ipro_st->X.range; i++) {
			for (int j = 0; j < ipro_st->Y.range; j++) {
				for (int k = 0; k < ipro_st->Z.range; k++) {
					if (grid->occ[i][j][k] == 0) {
                        if (grid->S.score[i][j][k] > record[l]) {
                            tooClose = 0;
                            for (int m = 0; m < l && tooClose == 0; m++) {
                                tmp = sqrt(pow((float)lx[m] - (float)(i + ipro_st->X.min), 2) + pow((float)ly[m] - (float)(j + ipro_st->Y.min), 2) + pow((float)lz[m] - (float)(k + ipro_st->Z.min), 2));
                                
                                if (tmp < bw2) {
                                    tooClose = 1;
                                }
                            }

                            if (tooClose == 0) {
                                record[l] = grid->S.score[i][j][k];
                                lx[l] = i + ipro_st->X.min;
                                ly[l] = j + ipro_st->Y.min;
                                lz[l] = k + ipro_st->Z.min;
                            }
					    }
                    }
				}
			}
		}
    }
}