using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
namespace BinomHeap
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader sr = new StreamReader("input.txt");
            StreamWriter sw = new StreamWriter("output.txt");
            List<int> res = new List<int>();

            int size = int.Parse(sr.ReadLine());

            if (size < 1 && size > Math.Pow(10, 18))
                sw.WriteLine(-1);

            int countVer = 0;
            while(size > 0)
            {
                int k = 0;
                k = (int)Math.Floor(Math.Log(size, 2));
                countVer = (int)Math.Pow(2, k);
                res.Add(k);
                size -= countVer;
            }

            for(int i = res.Count - 1; i >= 0; --i)
            {
                sw.WriteLine(res[i]);
            }

            if (res.Count == 0)
                sw.WriteLine(-1);

            sw.Close();

        }
    }
}
