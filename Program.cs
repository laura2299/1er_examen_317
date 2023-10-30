using System;
using System.Collections.Generic;
using System.Threading;

class Program
{
	

	static double CalculoPi(object estado)
	{
    	var parametros = (Tuple<int, int, int>)estado;
    	int procesador = parametros.Item1;
    	int limite = parametros.Item2;
    	int procesadores = parametros.Item3;

    	double cpi = 0;
    	for (int i = procesador; i < limite; i += procesadores)
    	{
        	// Calcular pi
        	if (i != 0)
        	{
            	cpi += 1.0 / Math.Pow(i, 4);
        	}
    	}
    	return cpi;
	}

	static void Main()
	{
    	int limite = 1000000000;
    	int procesadores = Environment.ProcessorCount;
    	List<int> entradas = new List<int>();
    	for (int i = 0; i < procesadores; i++)
    	{
        	entradas.Add(i);
    	}

    	//Console.WriteLine(string.Join(", ", entradas));

    	double[] resultados = new double[procesadores];
    	AutoResetEvent[] eventos = new AutoResetEvent[procesadores];

    	for (int i = 0; i < procesadores; i++)
    	{   
        	eventos[i] = new AutoResetEvent(false);
        	ThreadPool.QueueUserWorkItem(state =>
        	{
                int indice;
                if (state is not null){
                    indice = (int)state;
                
            	
            	resultados[indice] = CalculoPi(Tuple.Create(indice, limite, procesadores));
            	eventos[indice].Set();
                }
            }, i);
    	}

    	WaitHandle.WaitAll(eventos);

    	double sumaResultado4 = 0;
    	foreach (var resultado in resultados)
    	{
        	sumaResultado4 += resultado;
    	}

    	double resultadoFinal = Math.Pow(sumaResultado4 * 90, 1.0 / 4);
    	Console.WriteLine($"Resultado final: {resultadoFinal}");
	}
}
