#include <stdio.h>
#include <mpi.h>
//ejercicio 6 mpi
void generarSerie(int n, int vector[]) {
    int contador = 0;
    for (int i = 1; i <= n; i++) {
        vector[contador++] = i * i + 1;
        if (contador >= n)
            break;
        vector[contador++] = 2 * i;
    }
}

int main(int argc, char *argv[]) {
    int n = 1000;
    int vector[n];
    
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elementos_por_proceso = n / size;
    int inicio = rank * elementos_por_proceso;

    generarSerie(n, vector);

    int vectorResultado[n];

    // Reúne los resultados de todos los procesos en el proceso raíz (rango 0)
    MPI_Gather(vector + inicio, elementos_por_proceso, MPI_INT, vectorResultado, elementos_por_proceso, MPI_INT, 0, MPI_COMM_WORLD);

    // El proceso raíz imprime el vector resultante
    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            printf("%d\n", vectorResultado[i]);
        }
    }

    MPI_Finalize();

    return 0;
}
