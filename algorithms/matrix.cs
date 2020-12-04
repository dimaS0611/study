using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace matrix
{
    class Program
    {
        static int multip_mtx(int[] m)
        {
            int len = m.Length - 1;
            int[,] mtx = new int[len, len];

            for (int i = 0; i < len; ++i)
            {
                mtx[i, i] = 0;
            }

            for (int l = 1; l < len; ++l)
            {
                for (int i = 0; i < len - l; ++i)
                {
                    int j = i + l;
                    mtx[i, j] = int.MaxValue;

                    for (int k = i; k < j; ++k)
                    {
                        mtx[i, j] = Math.Min(mtx[i, j], mtx[i, k] + mtx[k + 1, j] + m[i] * m[k + 1] * m[j + 1]);
                    }
                }
            }

            return mtx[0, len - 1];
        }

        static void Main(string[] args)
        {
            StreamReader sr = new StreamReader("input.txt");
            StreamWriter sw = new StreamWriter("output.txt");

            int countMtx = int.Parse(sr.ReadLine());
            int[] mtx = new int[countMtx * 2];

            List<string> buf = new List<string>();
            while (!sr.EndOfStream)
            {
                var str = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);
                buf.Add(str[0]);
                buf.Add(str[1]);
            }

            for (int i = 0; i < buf.Count; ++i)
            {
                mtx[i] = int.Parse(buf[i]);
            }

            int res = multip_mtx(mtx);

            Console.WriteLine(res);
        }
    }
}
