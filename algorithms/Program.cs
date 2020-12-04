using System;
using System.IO;
using System.Collections.Generic;

namespace BFS
{
    class Program
    {
        public static int[] bfs(int[,] mtx,int size, int startV)
        {
            Queue<int> queue = new Queue<int>();
            int[] listFlg = new int[size];
            int flg = 1;
            

            queue.Enqueue(startV);
            listFlg[startV] = flg;

            while(queue.Count != 0)
            {
                int cur = queue.Dequeue();

                for(int i= 0; i < size; ++i)
                {
                    if(mtx[cur, i] == 1 && listFlg[i] == 0)
                    {
                        flg++;
                        queue.Enqueue(i);
                        listFlg[i] = flg;
                    }
                }
            }

            for(int i=0; i < size; ++i)
            {
                if(listFlg[i] == 0)
                {
                    listFlg[i] = ++flg;
                }
            }

            return listFlg;
        }

        static void Main(string[] args)
        {
            StreamWriter sw = new StreamWriter("output.txt");
            StreamReader sr = new StreamReader("input.txt");

            int size = int.Parse(sr.ReadLine());
            
            int[,] mtx = new int[size, size];

            for (int i =0; !sr.EndOfStream; ++i)
            {
                var tmp = sr.ReadLine().Split(new[] { " ", "," }, StringSplitOptions.RemoveEmptyEntries);

                for(int j =0; j < size; ++j)
                {
                    mtx[i, j] = int.Parse(tmp[j]);
                }
            }

            int[] res = bfs(mtx, size, 0);

            for(int i=0; i < size; ++i)
            {
                sw.Write(res[i] + " ");
            }
            sw.Close();
        }
    }
}
    
