// #include "lise.h"


// ILIG *makeilig(FILE *restrict file) {

//     ILIG *ilig = (ILIG *)malloc(sizeof(ILIG));
//     ilig->len = 1;
// 	ilig->x = malloc((ilig->len * sizeof(float)));
// 	ilig->y = malloc((ilig->len * sizeof(float)));
// 	ilig->z = malloc((ilig->len * sizeof(float)));
//     int i;

//     while ((fscanf(file, "%*s %*d %*s %f %f %f",
//         (ilig->x + (ilig->len-1)), (ilig->y + (ilig->len-1)),
//         (ilig->z + (ilig->len-1)))) == 3) {

//         ilig->len++;
// 	    ilig->x = realloc(ilig->x, (ilig->len * sizeof(float)));
// 	    ilig->y = realloc(ilig->y, (ilig->len * sizeof(float)));
// 	    ilig->z  = realloc(ilig->z, (ilig->len * sizeof(float)));

//     }

//     return ilig;
// }