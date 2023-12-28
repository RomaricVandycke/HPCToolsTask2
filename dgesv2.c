#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void afficherMatrice(double** matriceA, double** matriceB, int n, int nrhs) {
       for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", matriceA[i][j]);
        }
        printf("| ");
        for (int j = 0; j < nrhs; j++) {
            printf("%.2f\t", matriceB[i][j]);
        }
        printf("\n");
    }
}

void eliminationGauss(double** matriceA, double** matriceB, int n, int nrhs) {
    for (int col = 0; col < n - 1; col++) {
        // recherche du pivot maximal dans la colonne actuelle
        int max_row = col;
        for (int i = col + 1; i < n; i++) {
            if (fabs(matriceA[i][col]) > fabs(matriceA[max_row][col])) {
                max_row = i;
            }
        }
        // échange des lignes pour mettre le pivot maximal en haut
        for (int j = 0; j < n; j++) {
            double temponA = matriceA[col][j];
            matriceA[col][j] = matriceA[max_row][j];
            matriceA[max_row][j] = temponA;
        }
        for (int j = 0; j < nrhs; j++) {
            double temponB = matriceB[col][j];
            matriceB[col][j] = matriceB[max_row][j];
            matriceB[max_row][j] = temponB;
        }
        // échelonnement des lignes
        for (int i = col + 1; i < n; i++) {
            double factor = matriceA[i][col] / matriceA[col][col];
            for (int j = col; j < n; j++) {
                matriceA[i][j] -= factor * matriceA[col][j];
            }
            for (int j = 0; j < nrhs; j++) {
                matriceB[i][j] -= factor * matriceB[col][j];
            }
        }
    }
}

void substitutionArriere(double** matriceA, double** matriceB, double* solutions, int n, int nrhs) {
    for (int k = 0; k < nrhs; k++) {
        for (int i = n - 1; i >= 0; i--) {
            solutions[i] = matriceB[i][k];
            for (int j = i + 1; j < n; j++) {
                solutions[i] -= matriceA[i][j] * solutions[j];
            }
            solutions[i] /= matriceA[i][i];
        }
    }
}

int my_dgesv(int n, int nrhs, double** matriceA, double** matriceB) {
    srand(time(NULL));

    eliminationGauss(matriceA, matriceB, n, nrhs);

    double* solutions = (double*)malloc(n * sizeof(double));

    substitutionArriere(matriceA, matriceB, solutions, n, nrhs);

    printf("\nMatrice A après élimination de Gauss :\n");
    afficherMatrice(matriceA, matriceB, n, nrhs);

    printf("\nSolutions :\n");
    for (int i = 0; i < n; i++) {
        printf("X%d = %.2f\n", i + 1, solutions[i]);
    }

    free(solutions);  // N'oubliez pas de libérer la mémoire allouée

    return 0;
}