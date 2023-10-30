using System;
using System.Collections.Generic;
using System.Threading.Tasks;
//ejercicio 5 seerie con .net
class Program
{
    static List<int> GenerateSeries(int n)
    {
        List<int> series = new List<int>();

        if (n == 1)
        {
            series.Add(2);
        }
        else if (n == 0)
        {
            series.Add(0);
        }
        else if (n % 2 == 0)
        {
            int numThreads = n / 2;
            int maxThreads = Math.Min(4, numThreads);

            Parallel.For(1, maxThreads + 1, i =>
            {
                int index = i;
                series.Add(index * index + 1);
                series.Add(index + index);
            });

            for (int i = maxThreads + 1; i <= numThreads; i++)
            {
                int index = i;
                lock (series)
                {
                    series.Add(index * index + 1);
                    series.Add(index + index);
                }
            }
        }
        else
        {
            int numThreads = n / 2 +1;
            int maxThreads = Math.Min(4, numThreads);

            Parallel.For(1, maxThreads, i =>
            {
                int index = i;
                series.Add(index * index + 1);
                series.Add(index + index);
            });

            for (int i = maxThreads + 1; i <= numThreads; i++)
            {
                int index = i;
                lock (series)
                {
                    series.Add(index * index + 1);
                    series.Add(index + index);
                }
            }

            series.Add(numThreads * numThreads + 1);
        }

        return series;
    }

    static void Main()
    {
        int n = 5;
        List<int> resultingSeries = GenerateSeries(n);

        foreach (int number in resultingSeries)
        {
            Console.WriteLine(number);
        }
    }
}
