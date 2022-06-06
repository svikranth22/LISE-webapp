#ifndef ATOM_H
#define ATOM_H

#include "lise.h"

typedef struct ATOM {
	char* aa; //amino acid name-3 letter
	int rno; //residue serial number
	char* nom; //atom name
	float x; //x coordinates
	float y; //y coordinates
	float z; //z coordinates
	float r; //r radius
	int at; // atom type
}ATOM;

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
#endif