using System;
using System.Threading;

class Program
{
    static int numIterations = 1000000;
    static int numThreads = 8;
    static double sum = 0.0;
    static object lockObject = new object();

    static void CalculatePi(object threadIndex)
    {
        int index = (int)threadIndex;
        double step = 1.0 / numIterations;

        for (int i = index; i < numIterations; i += numThreads)
        {
            double x = (i + 0.5) * step;
            double partialSum = 4.0 / (1.0 + x * x);

            lock (lockObject)
            {
                sum += partialSum;
            }
        }
    }

    static void Main(string[] args)
    {
        Thread[] threads = new Thread[numThreads];

        for (int i = 0; i < numThreads; i++)
        {
            threads[i] = new Thread(CalculatePi);
            threads[i].Start(i);
        }

        for (int i = 0; i < numThreads; i++)
        {
            threads[i].Join();
        }

        double pi = sum * (1.0 / numIterations);
        Console.WriteLine("Przyblizona wartosc pi to: " + pi);
    }
}
