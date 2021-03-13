using System;
using System.Collections.Generic;
using System.IO;

namespace shortPath
{
    public class Graph
    {
        const long maxCount = 1000000;

        public static long packEdge(int i, int w)
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

            public int _weight { get; set; }
            public VertexInfo()
            {
                _closed = false;
                _dist = -1;
                _weight = -1;
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

    public class Solve
    {
        Graph _graph;

        public Solve(Graph graph)
        {
            _graph = graph;
        }

        public int solve(int start, int end, int weightScale)
        {
            var first = _graph.vertex(start);
            var last = _graph.vertex(end);

            first._dist = 0;

            List<Graph.VertexInfo> minList = new List<Graph.VertexInfo>();
            minList.Add(first);

            foreach(var v in _graph._vertices)
            {
                if (v == null)
                    continue;
                v._weight = weightScale * v._edges.Count;
            }

            while (true)
            {
                Graph.VertexInfo min = null;

                foreach (var v in minList)
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

                    w += min._dist + min._weight;

                    if (v._dist < 0)
                    {
                        if (v != last)
                            minList.Add(v);
                        v._dist = w;
                    }
                    else if (v._dist > w)
                    {
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

            var firstBuf = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

            int n;
            int m;

            bool checkN = int.TryParse(firstBuf[0], out n);
            bool checkM = int.TryParse(firstBuf[1], out m);

            if (checkN && checkM)
            {
                if (n >= 1 && n <= 11000 && m >= 0 && m <= 100000)
                {
                    Graph graph = new Graph(n);

                    int vertexS, vertexE, weight;
                    for (int i = 0; i < m; ++i)
                    {
                        var buf = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);
                        bool checkS =int.TryParse(buf[0], out vertexS);
                        bool checkE = int.TryParse(buf[1], out vertexE);
                        bool checkW = int.TryParse(buf[2], out weight);

                        if (checkS && checkE && checkW)
                        {
                            if (vertexE >= 1 && vertexE <= n && vertexS >= 1 && vertexS <= n)
                            {
                                graph.addEdge(vertexS - 1, vertexE - 1, weight);
                            }
                        }
                        else
                        {
                            sw.Write("No");
                            sw.Close();
                            return;
                        }
                    }

                    var lastBuf = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                    int s;
                    int f; 
                    int q;
                    
                    bool chF = int.TryParse(lastBuf[1], out f);
                    bool chS = int.TryParse(lastBuf[0], out s);
                    bool chQ = int.TryParse(lastBuf[2], out q);

                    if (chF && chS && chQ)
                    {
                        if (s >= 1 && s <= n && f >= 1 && f <= n && q >= 0 && q <= 100)
                        {
                            Solve solve = new Solve(graph);

                            int res = solve.solve(s - 1, f - 1, q);

                            if (res >= 0)
                            {
                                sw.WriteLine("Yes");
                                sw.WriteLine(res);
                            }
                            else
                            {
                                sw.WriteLine("No");
                            }
                        }
                        else
                        {
                            sw.Write("No");
                        }
                    }
                    else
                    {
                        sw.Write("No");
                        sw.Close();
                        return;
                    }
                }
                else
                {
                    sw.Write("No");
                }
            }
            else
                sw.Write("No");

            sw.Close();
        }
    }
}
