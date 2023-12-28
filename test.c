#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3 //taille de la matrice

void afficherMatrice(double matrice[N][N + 1]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            printf("%.2f\t", matrice[i][j]);
        }
        printf("\n");
    }
}

void eliminationGauss(double matrice[N][N + 1]) {
    for (int col = 0; col < N - 1; col++) {
        // Recherche du pivot maximal dans la colonne actuelle
        int max_row = col;
        for (int i = col + 1; i < N; i++) {
            if (fabs(matrice[i][col]) > fabs(matrice[max_row][col])) { //"fabs" permet de calculer la valeur absolue d'un nombre en virgule flottante en C.
                max_row = i;
            }
        }
        // Échange des lignes pour mettre le pivot maximal en haut, pour avoir une plus grande stabilité
        for (int j = 0; j < N + 1; j++) {
            double tempon = matrice[col][j]; 
            matrice[col][j] = matrice[max_row][j];
            matrice[max_row][j] = tempon;
        }
        // Échelonnement des lignes
        for (int i = col + 1; i < N; i++) {
            double factor = matrice[i][col] / matrice[col][col]; //en gros permet d'échelonné avec la diagonale de la matrice (dur à expliquer)
            for (int j = col; j < N + 1; j++) {
                matrice[i][j] -= factor * matrice[col][j];
            }
        }
    }
}

//résolution du système du bas vers le haut
void substitutionArriere(double matrice[N][N + 1], double solutions[N]) {
    for (int i = N - 1; i >= 0; i--) {
        solutions[i] = matrice[i][N];
        for (int j = i + 1; j < N; j++) {
            solutions[i] -= matrice[i][j] * solutions[j];
        }
        solutions[i] /= matrice[i][i];
    }
}

int main() {
    double matrice[N][N + 1];
    double solutions[N];
    srand(time(NULL));

    // Remplissage de la matrice avec des valeurs aléatoires
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
        	matrice[i][j] = (rand() % 100) /10; //permet de générer des nombres aléatoires réels entre 0 et 9.9
        }
    }

    printf("Matrice initiale :\n");
    afficherMatrice(matrice);

    eliminationGauss(matrice);
    substitutionArriere(matrice, solutions);

    printf("\nMatrice après élimination de Gauss :\n");
    afficherMatrice(matrice);

    printf("\nSolutions :\n");
    for (int i = 0; i < N; i++) {
        printf("X%d = %.2f\n", i + 1, solutions[i]);
    }

    return 0;
}


