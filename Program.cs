using System;
using System.Threading;

class Program
{
    // Función para calcular la parte de PI en el rango asignado a un procesador específico
    static double CalculoPi(int procesador, int limite, int procesadores)
    {
        double cpi = 0;
        for (int i = procesador; i < limite; i += procesadores)
        {
            // Calcular pi utilizando la fórmula matemática
            if (i != 0)
            {
                cpi += 1.0 / Math.Pow(i, 4);
            }
        }
        return cpi;
    }

    // Función que realiza el cálculo de PI y establece un evento al finalizar
    static void CalcularPiYSetEvent(int indice, int limite, int procesadores, double[] resultados, AutoResetEvent[] eventos)
    {
        // Llama a la función CalculoPi para calcular la parte de PI y almacénala en el arreglo de resultados
        resultados[indice] = CalculoPi(indice, limite, procesadores);
        // Establece el evento correspondiente para indicar que el cálculo ha terminado
        eventos[indice].Set();
    }

    static void Main()
    {
        int limite = 1000000; // Establece el límite de cálculo
        int procesadores = 4; // Utilizamos solo 4 hilos

        double[] resultados = new double[procesadores]; // Arreglo para almacenar los resultados parciales
        AutoResetEvent[] eventos = new AutoResetEvent[procesadores]; // Arreglo de eventos para sincronización

        for (int i = 0; i < procesadores; i++)
        {
            int indice = i; // Almacena el índice localmente para usarlo en el hilo
            eventos[i] = new AutoResetEvent(false); // Inicializa un evento para el hilo actual
            ThreadPool.QueueUserWorkItem(_ =>
            {
                // Llama a la función para calcular PI y establecer el evento correspondiente
                CalcularPiYSetEvent(indice, limite, procesadores, resultados, eventos);
            });
        }

        WaitHandle.WaitAll(eventos); // Espera a que todos los eventos se activen

        double sumaResultado4 = 0;
        foreach (var resultado in resultados)
        {
            sumaResultado4 += resultado; // Suma los resultados parciales
        }

        double resultadoFinal = Math.Pow(sumaResultado4 * 90, 1.0 / 4); // Calcula el resultado final de PI
        Console.WriteLine($"Resultado final: {resultadoFinal}");
    }
}
