using System;
using System.Collections.Generic;

using System.IO;

namespace listReliability
{
    public class Graph
    {
        public static int _countE;
        public static LinkedList<int>[] _list { get; set; }

        StreamWriter sw = new StreamWriter("output.txt");

        public Graph(int countE)
        {
            _countE = countE;
            _list = new LinkedList<int>[countE];

            for(int i =0; i < countE; ++i)
            {
                _list[i] = new LinkedList<int>();
            }
        }

        public void addEdge(int startE, int endE)
        {
            _list[startE - 1].AddLast(endE);
            _list[endE - 1].AddLast(startE);
        }

        public void print()
        {
            for (int i = 0; i < _countE; ++i)
            {
                sw.Write(_list[i].Count + " ");
                for (int j = 0; _list[i].Count != 0; ++j) 
                {
                    var v = _list[i].Last.Value;
                    sw.Write(v + " ");
                    _list[i].RemoveLast();
                }
                sw.Write("\n");
            }

            sw.Close();
        }
    }


    class Program
    {
        static void Main(string[] args)
        {

            StreamReader sr = new StreamReader("input.txt");



            List<int> input = new List<int>();
            int size = 0;
            int countW = 0;
            var tmp = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

            size = int.Parse(tmp[0]);
            countW = int.Parse(tmp[1]);


            while (!sr.EndOfStream)
            {
                var line = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                int i = int.Parse(line[0]);
                int j = int.Parse(line[1]);

                input.Add(i);
                input.Add(j);
            }

            Graph graph = new Graph(size);

            for(int i =0; i < input.Count; ++i)
            {
                graph.addEdge(input[i], input[i + 1]);
                i++;
            }


            graph.print();
        }
    }
}
