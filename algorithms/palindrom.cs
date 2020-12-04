using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;

namespace palindrom
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader sr = new StreamReader("in.txt");
            StreamWriter sw = new StreamWriter("out.txt");

            String str;

            str = sr.ReadLine();
            int size = str.Length;

            int[,] mtx = new int[size, size];

            for (int i = 0; i < size; ++i)
            {
                mtx[i, i] = 1;

                for (int j = size - 1; j > i; --j)
                {

                    if (str[i] == str[i + 1])
                        mtx[i, i + 1] = 2;
                    if (str[i] != str[i + 1])
                        mtx[i, i + 1] = 1;

                    if (str[i] == str[j])
                        mtx[i, j] = mtx[i + 1, j - 1] + 2;
                    if (str[i] != str[j])
                        Math.Max(mtx[i + 1, j], mtx[i, j - 1]);
                   
                }
            }

            Console.WriteLine(str);

            for(int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                    Console.Write(mtx[i,j] + " ");

                Console.Write("\n");
            }
            




        }
    }
}
