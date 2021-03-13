using System;
using System.Collections.Generic;
using System.IO;

namespace Dijkstra
{

    public class Graph
    {
        const long maxCount = 1000000;

        public static long packEdge(int i,int w)
        {
            long result = w;
            return result * maxCount + i;
        }

        public static int unpackEdge(long e, out int w)
        {
            w = (int)(e / maxCount);
            return (int)(e % maxCount);
        }

        public class VertexInfo
        {
            public List<long> _edges { get; }
            public bool _closed { get; set; }
            public int _dist { get; set; }
            public VertexInfo()
            {
                _closed = false;
                _dist = -1;
                _edges = new List<long>();
            }

            public void addEdge(int i, int w)
            {
                _edges.Add(packEdge(i, w));
            }
        }

        public List<VertexInfo> _vertices { get; }
        public Graph(int vertCount)
        {
            _vertices = new List<VertexInfo>(vertCount);
            
            for (int i = 0; i < vertCount; ++i)
            {
                _vertices.Add(null);
            }
        }

        public void addEdge(int startV, int endV, int weight)
        {
            var v1 = vertex(startV);
            var v2 = vertex(endV);
         
            v1.addEdge(endV, weight);
            v2.addEdge(startV, weight);
        }

        public VertexInfo vertex(int index)
        {
            var result = _vertices[index];
            if (result == null)
            {
                result = new VertexInfo();
                _vertices[index] = result;
            }

            return result;
        }
    }

    public class Dijkstra
    {
        Graph _graph;

        public Dijkstra(Graph graph)
        {
            _graph = graph;
        }

        public int solve(int start, int end)
        {             
            var first = _graph.vertex(start);
            var last = _graph.vertex(end);

            first._dist = 0;

            List<Graph.VertexInfo> minList = new List<Graph.VertexInfo>();
            minList.Add(first);

            while (true)
            {
                Graph.VertexInfo min = null;

                foreach(var v in minList)
                {
                    if (min == null || min._dist > v._dist)
                        min = v;
                }

                if (min == null)
                    break;

                min._closed = true;
                minList.Remove(min);

                foreach (var e in min._edges)
                {
                    int w = 0;
                    int i = Graph.unpackEdge(e, out w);

                    var v = _graph._vertices[i];
                    if (v == null || v._closed)
                        continue;

                    w += min._dist;

                    if (v._dist < 0)
                    {
                        if (v != last)
                            minList.Add(v);
                        v._dist = w;
                    }
                    else if (v._dist > w) {
                        v._dist = w;
                    }
                }
            }

            return last._dist;
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            StreamReader sr = new StreamReader("input.txt");
            StreamWriter sw = new StreamWriter("output.txt");

            var tmp = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

            int n = int.Parse(tmp[0]);
            int m = int.Parse(tmp[1]);

            Graph graph = new Graph(n);

            int vertexS, vertexE, weight;
            while(!sr.EndOfStream)
            {
                var buf = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);
                vertexS = int.Parse(buf[0]);
                vertexE = int.Parse(buf[1]);
                weight = int.Parse(buf[2]);

                graph.addEdge(vertexS - 1, vertexE - 1, weight);
            }

            if (graph._vertices.Count == 0)
                sw.Write(0);
            else
            {
                Dijkstra dijkstra = new Dijkstra(graph);

                int res = dijkstra.solve(0, n - 1);

                sw.Write(res);
            }

            sw.Close();
        }
    }
}
