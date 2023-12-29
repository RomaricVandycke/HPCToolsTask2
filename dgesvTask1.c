#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void eliminationGauss(double* matriceA, double* matriceB, int n, int nrhs) {
    for (int col = 0; col < n - 1; col++) {
        // recherche du pivot maximal dans la colonne actuelle
        int max_row = col;
        for (int i = col + 1; i < n; i++) {
            if (fabs(matriceA[i* n+col]) > fabs(matriceA[max_row* n+col])) {
                max_row = i;
            }
        }
        // échange des lignes pour mettre le pivot maximal en haut
        for (int j = 0; j < n; j++) {
            double temponA = matriceA[col*n+j];
            matriceA[col*n+j] = matriceA[max_row*n+j];
            matriceA[max_row*n+j] = temponA;
        }
        for (int j = 0; j < nrhs; j++) {
            double temponB = matriceB[col*nrhs+j];
            matriceB[col*nrhs+j] = matriceB[max_row*nrhs+j];
            matriceB[max_row*nrhs+j] = temponB;
        }
        // échelonnement des lignes
        for (int i = col + 1; i < n; i++) {
            double factor = matriceA[i*n+col] / matriceA[col*n+col];
            for (int j = col; j < n; j++) {
                matriceA[i*n+j] -= factor * matriceA[col*n+j];
            }
            for (int j = 0; j < nrhs; j++) {
                matriceB[i*nrhs+j] -= factor * matriceB[col*nrhs+j];
            }
        }
    }
}

void substitutionArriere(double* matriceA, double* matriceB, double* solutions, int n, int nrhs) {
    for (int k = 0; k < nrhs; k++) {
        for (int i = n - 1; i >= 0; i--) {
            solutions[i] = matriceB[i* nrhs+k];
            for (int j = i + 1; j < n; j++) {
                solutions[i] -= matriceA[i*n+j] * solutions[j];
            }
            solutions[i] /= matriceA[i*n+i];
        }
    }
}

int my_dgesv(int n, int nrhs, double* matriceA, double* matriceB) {
    srand(time(NULL));

    eliminationGauss(matriceA, matriceB, n, nrhs);

    double* solutions = (double*)malloc(n * sizeof(double));

    substitutionArriere(matriceA, matriceB, solutions, n, nrhs);


    printf("\nSolutions :\n");
    for (int i = 0; i < n; i++) {
        printf("X%d = %.2f\n", i + 1, solutions[i]);
    }

    free(solutions);  // N'oubliez pas de libérer la mémoire allouée

    return 0;
}
