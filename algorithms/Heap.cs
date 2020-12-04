using System;
using System.Collections.Generic;
using System.IO;

namespace Heap
{
    class Program
    {
        static void Insert(List<int> arr, int key)
        {
            arr.Add(key);

            int i = arr.Count - 1;
            int j = (i - 1) / 2;
            while (i > 0 && arr[j] > arr[i])
            {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;

                i = j;
                j = (i - 1) / 2;
            }

        }

        static void Main(string[] args)
        {
            StreamReader sr = new StreamReader("input.txt");
            StreamWriter sw = new StreamWriter("output.txt");
            List<int> read = new List<int>();

            int size = 0;
            size = int.Parse(sr.ReadLine());
            var buf = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

            for(int i =0; i < size; ++i)
            {
                read.Add(int.Parse(buf[i]));
            }

            List<int> arrayCheck = new List<int>();
            
            for(int i = 0; i < size;++i)
            {
                Insert(arrayCheck, read[i]);
            }

            int counter = 0;
            for (int i = 0; i < size; ++i)
            {   
                if (arrayCheck[i] == read[i])
                    counter++;
            }

            if (counter == size)
                sw.Write("Yes");
            else
                sw.Write("No");

            sw.Close();
        }
    }
}
