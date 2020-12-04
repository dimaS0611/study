using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace reliabilityMatrix
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader sr = new StreamReader("input.txt");
            StreamWriter sw = new StreamWriter("output.txt");


            List<int> input = new List<int>();
            int size = 0;
            int countE = 0;
            var tmp = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

            size = int.Parse(tmp[0]);
            countE = int.Parse(tmp[1]);


            while (!sr.EndOfStream)
            {
                var line = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                int i = int.Parse(line[0]);
                int j = int.Parse(line[1]);

                input.Add(i);
                input.Add(j);            
            }

            int[,] mtx = new int[size, size];

            for(int i = 0; i < input.Count - 1; ++i)
            {
                mtx[input[i] - 1, input[i + 1] - 1] = 1;
                mtx[input[i + 1] - 1, input[i] - 1] = 1;

                i++;
            }


            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    sw.Write(mtx[i, j] + " ");
                }

                sw.Write("\n");
            }

            sw.Close();
        }
    }
}
