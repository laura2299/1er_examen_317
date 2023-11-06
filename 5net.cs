using System;
using System.Threading;

class Program
{
    static int n = 10;
    static int[] serie = new int[n];
    static ManualResetEvent[] waitHandles = new ManualResetEvent[n]; // Arreglo de ManualResetEvent para sincronización
    static object lockObject = new object(); // Objeto de bloqueo para garantizar la seguridad de subprocesos
    static int currentIndex = 0; // Índice actual para el procesamiento en hilos

    static void Main()
    {
        // Inicializa los ManualResetEvent para la sincronización
        for (int i = 0; i < n; i++)
        {
            waitHandles[i] = new ManualResetEvent(false);
        }

        // Inicia 4 hilos para generar los valores de la serie
        for (int i = 0; i < 4; i++)
        {
            ThreadPool.QueueUserWorkItem(GenerateSeriesValues);
        }

        // Espera a que todas las tareas en ThreadPool se completen
        WaitHandle.WaitAll(waitHandles);

        // Imprime los valores de la serie
        for (int i = 0; i < n; i++)
        {
            Console.WriteLine(serie[i]);
        }
    }

    static void GenerateSeriesValues(object state)
    {
        int index;
        while ((index = Interlocked.Increment(ref currentIndex) - 1) < n)
        {
            // Calcula los valores de la serie y almacénalos en el arreglo
            if (index % 2 == 0)
            {
                serie[index] = (int)Math.Pow((index / 2 + 1), 2) + 1;
            }
            else
            {
                serie[index] = index + 1;
            }
            waitHandles[index].Set(); // Indica que este índice ha sido procesado
        }
    }
}
