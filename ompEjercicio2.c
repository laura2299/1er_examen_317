#include "stdio.h"
#include "omp.h"
#include <string.h>
//este es el 4 official
#define MAX_PALABRAS 9 // Tamaño máximo de palabras en cada lista

int main() {
    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolívar";
    char *palabra;
    char *delimitadores = " ";
    char lista1[MAX_PALABRAS][50]; // Tamaño suficiente para almacenar palabras
    char lista2[MAX_PALABRAS][50]; // Tamaño suficiente para almacenar palabras
    int i = 0;
    int sw=0;
    palabra = strtok(frase, delimitadores);
	
    #pragma omp parallel
    {
        int cantidad = omp_get_num_threads();
        int procesador = omp_get_thread_num();
        printf("Proceso cantidad de procesadores %d, procesador %d\n", cantidad, procesador);

        while (palabra != NULL) {
            // Asegura que solo un hilo modifique las listas a la vez
            #pragma omp critical
            {
                if (i < MAX_PALABRAS) {
                printf("hilo:  %d \n", omp_get_thread_num() );
                	printf("sw:   %d\n ",sw);
                    if (sw==0) {
                        strcpy(lista1[i], palabra);
                        printf("palabra1: %s\n",palabra);
                        
                        sw=1-sw;
        		
                        
                    } 
                    else {
                        strcpy(lista2[i], palabra);
                        printf("palabra2: %s\n",palabra);
                        
                        sw=1-sw;
                    }
                    i++;
                }
            }

            palabra = strtok(NULL, delimitadores);
        }
        
        
        
    }

    // Imprime las listas
    printf("Lista 1: ");
    for (int j = 0; j < i; j++) {
        printf("%s ", lista1[j]);
    }
    printf("\n");

    printf("Lista 2: ");
    for (int j = 0; j < i; j++) {
        printf("%s ", lista2[j]);
    }
    printf("\n");

    return 0;
}

