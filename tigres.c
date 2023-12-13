#include <stdio.h>
#include <string.h>
#include "mpi.h"

#define MAX_PALABRAS 9 // Tamaño máximo de palabras en cada lista

void concatenar(char c, char *cadena) {
    char cadT[1];
    cadT[0] = c;
   
    strcat(cadena, cadT);
}

int main(int argc, char *argv[]) {
    int procesador, nprocesador, i, sw = 0;
    int envio = 0, vrecepcion;
    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    int n = strlen(frase);
    char lista1[MAX_PALABRAS][50];
    char lista2[MAX_PALABRAS][50];

    char a[50] = "";
    char b[50] = "";

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocesador);

    int f = n / nprocesador;

    // Divide la carga de trabajo entre los procesos MPI
    MPI_Scatter(frase, f, MPI_CHAR, a, f, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (i = 0; i < f; i++) {
        if (a[i] == ' ') {
            if (envio % 2 == 0) {
                concatenar(' ', lista1[i]);
            } else {
                concatenar(' ', lista2[i]);
            }
            envio += 1;
        } else {
            if (envio % 2 == 0) {
                concatenar(a[i], lista1[i]);
            } else {
                concatenar(a[i], lista2[i]);
            }
        }
    }

    // Combina los resultados de cada proceso MPI
    char lista1_total[nprocesador][50];
    char lista2_total[nprocesador][50];

    MPI_Gather(lista1, f, MPI_CHAR, lista1_total, f, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Gather(lista2, f, MPI_CHAR, lista2_total, f, MPI_CHAR, 0, MPI_COMM_WORLD);
	
    MPI_Finalize();

    // Proceso 0 imprime las listas
    if (procesador == 0) {
        printf("Lista 1: ");
        for (int j = 0; j < n; j++) {
            printf("%s ", lista1_total[j]);
        }
        printf("\n");

        printf("Lista 2: ");
        for (int j = 0; j < n; j++) {
            printf("%s ", lista2_total[j]);
        }
        printf("\n");
    }

    return 0;
}
