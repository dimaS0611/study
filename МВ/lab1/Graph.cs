using System;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace lab1
{
    public partial class Graph : Form
    {
        public Graph()
        {
            InitializeComponent();
        }

        private void Graph_Load(object sender, EventArgs e)
        {
            Test();
        }

        public void Test()
        {
            this.ClientSize = new System.Drawing.Size(1300, 400);
            chart.Parent = this;
            chart.Dock = DockStyle.Fill;

            chart.ChartAreas.Add(new ChartArea("Test"));

            chart.ChartAreas[0].AxisX.Title = "Time(sec)";
            chart.ChartAreas[0].AxisY.Title = "Size of matrix";


            Series series = new Series("Matrix");
            series.ChartType = SeriesChartType.Line;
            series.Color = Color.Red;
            
            Random rnd = new Random();
            
            Stopwatch stopwatch = new Stopwatch();

            int size = 1;
            while (stopwatch.ElapsedMilliseconds <= 60000)
            {
                double[,] m = new double[size, size];

                for (int i = 0; i < size; ++i)
                {
                    for (int j = 0; j < i + 1; ++j)
                    {
                        int num = rnd.Next(5, 50);

                        m[i, j] = num;
                        m[j, i] = num;
                    }
                }

                double[,] res1 = new double[size, size];
                stopwatch.Reset();

                stopwatch.Start();

                res1 = Program.inverse(m, size);

                stopwatch.Stop();

                series.Points.AddXY((double)stopwatch.ElapsedMilliseconds / 1000, size);

                Console.WriteLine("\n ********************\nTime = " + ((double)stopwatch.ElapsedMilliseconds / 1000));

                size += 5;
                Console.WriteLine("size = " + size + "\n**************\n");
            
            }

            chart.Series.Add(series);

            this.Controls.Add(chart);
        }
    }
}
