using System;
using System.Collections.Generic;
using System.IO;

namespace frog
{
    class Program
    {
        static void Main(string[] args)
        {
            int size = 0;
            List<int> array = new List<int>();
            StreamReader sr = new StreamReader("in.txt");
            StreamWriter sw = new StreamWriter("out.txt");

            size = int.Parse(sr.ReadLine());
            var result = new int[size];

            var buf = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

            for (int i = 0; i < size; ++i)
            {
                array.Add(int.Parse(buf[i]));
            }

            if (size == 2)
            {
                sw.Write(-1);
            }
            if (size == 1)
            {
                int res = array[0];
                sw.Write(res);
            }
            else if(size > 2)
            {
                result[0] = array[0];
                result[1] = -10000;
                result[2] = result[0] + array[2];

                for (int i = 3; i < array.Count; ++i)
                {
                    result[i] = Math.Max(result[i - 3], result[i - 2]) + array[i];
                }

                sw.Write(result[result.Length - 1]);

            }
            sw.Close();
        }
    }
}
