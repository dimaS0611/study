using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace lab1
{
    class Program
    {
        public static double[,] fillMtxU(double[,] mtx, int size)
        {
            double[,] U = new double[size, size];

            U[0, 0] = Math.Sqrt(mtx[0, 0]);

            for (int i = 1; i < size; ++i)
                U[0, i] = mtx[0, i] / U[0, 0];


            for (int i = 1; i < size; ++i)
            {
                for (int j = i; j < size; ++j)
                {
                    if (i == j)
                    {
                        double sum = 0.0;

                        for (int k = 0; k <= i - 1; ++k)
                            sum += Math.Pow(U[k, i], 2);

                        U[i, j] = Math.Sqrt(Math.Abs(mtx[i, j] - sum));

                    }
                    else
                    {
                        double sum = 0.0;

                        for (int k = 0; k <= i - 1; ++k)
                            sum += (U[k, i] * U[k, j]);

                        U[i, j] = (mtx[i, j] - sum) / U[i, i];
                    }
                }
            }
            
            Console.Write("\nMatrix U = \n");
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    Console.Write(U[i, j] + "  ");
                }
                Console.Write("\n");
            }
            
            return U;
        }

        static void swap<T>(ref T lhs, ref T rhs)
        {
            T temp;
            temp = lhs;
            lhs = rhs;
            rhs = temp;
        }
        static T[,] Copy<T>(T[,] array)
        {
            T[,] newArray = new T[array.GetLength(0), array.GetLength(1)];
            for (int i = 0; i < array.GetLength(0); i++)
                for (int j = 0; j < array.GetLength(1); j++)
                    newArray[i, j] = array[i, j];
            return newArray;
        }
        public static double[] solveEquation(double[,] mtx, double[] b, int size)
        {
            double[,] a = Copy(mtx);
            double[] x = new double[size];
            b.CopyTo(x, 0);

            int[] js = new int[size];

            bool ok = true;
            int n1 = size - 1;

            double d = 0.0;

            for (int k = 0; k <= size - 2; ++k)
            {
                int _i = 0;
                d = 0.0;
                for (int i = k; i <= size - 1; ++i)
                {
                    for (int j = k; j <= size - 1; ++j)
                    {
                        double t = Math.Abs(a[i, j]);
                        if (t > d) {
                            d = t;
                            js[k] = j;
                            _i = i;
                        }
                    }
                }

                if (Math.Abs(d) < 1e-151)
                    return null;


                if (js[k] != k)
                {
                    for (int i = 0; i <= size - 1; ++i)
                    {
                        swap<double>(ref a[i, k], ref a[i, js[k]]);
                    }
                }

                if (_i != k)
                {
                    for (int j = k; j <= size - 1; ++j)
                    {
                        swap(ref a[k, j], ref a[_i, j]);
                    }

                    swap(ref x[k], ref x[_i]);
                }

                d = a[k, k];

                for (int j = k + 1; j <= size - 1; ++j)
                {
                    a[k, j] /= d;
                }

                x[k] /= d;

                for (int i = k + 1; i <= size - 1; ++i)
                {
                    for (int j = k + 1; j <= size - 1; ++j)
                    {
                        a[i, j] -= a[i, k] * a[k, j];
                    }

                    x[i] -= a[i, k] * x[k];
                }
            }

            if (!ok)
                return null;

            d = a[size - 1, size - 1];
            if (Math.Abs(d) < 1e-151)
                return null;

            x[size - 1] /= d;

            for (int i = size - 2; i >= 0; --i)
            {
                double t = 0;

                for (int j = i + 1; j <= size - 1; ++j)
                {
                    t += a[i, j] * x[j];
                    x[i] -= t;
                }
            }

            js[size - 1] = size - 1;

            for (int k = size - 1; k >= 0; --k)
            {
                if (js[k] != k)
                {
                    swap(ref x[k], ref x[js[k]]);
                }
            }
              
            return x;
        }

        public static double[,] inverse(double[,] mtx, int size)
        {
            double[,] inverse = new double[size, size];
            
            double[,] U = fillMtxU(mtx, size);
            double[,] UT = new double[size, size];

            for(int i = 0; i < size; ++i)
            {
                for(int j = 0; j < size; ++j)
                {
                    if (i < j)
                        UT[i, j] = 0;
                    else
                        UT[i, j] = U[j,i];
                }
            }

            int[,] E = new int[size, size];

            for (int i = 0; i < size; ++i)
                E[i, i] = 1;

            double[][] vectorsY = new double[size][];
            
            for(int i = 0; i < size; ++i)
            {
                double[] vectorE = new double[size];
                vectorE[i] = 1;

                vectorsY[i] = solveEquation(UT, vectorE, size);
            }

            double[][] vectorsX = new double[size][];
            for(int i = 0; i < size; ++i)
            {
                vectorsX[i] = solveEquation(U, vectorsY[i], size);
            }

            double[,] result = new double[size, size];
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    result[i, j] = vectorsX[j][i];
                }
            }

            return result;
        }


        public static double maxNorm(double[,] mtx, int size)
        {
            double max = 0;
            double sum = 0;

            for(int i =0; i < size; ++i)
            {
                for(int j = 0; j < size; ++j){
                    sum += Math.Abs((double)mtx[i, j]);
                }

                if(sum > max){
                    max = sum;
                }

                sum = 0;
            }

            return max;
        }

        public static void printA(double[,] mtx, int size)
        {
            Console.Write("\n\nMatrix A = \n");
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    Console.Write(mtx[i, j] + "  ");
                }
                Console.Write("\n\n");
            }
        }
       
        public static void printD(double[,] mtx, int size)
        {
            Console.Write("\n\nMatrix D = \n");
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    if (i == j)
                        Console.Write(mtx[i, j] + "  ");
                    else
                        Console.Write("0  ");
                }
                Console.Write("\n\n");
            }
        }

        static void Main(string[] args)
        { 
            double[,] A3 = { { 81 ,   -3240 ,  41580 ,  -249480, 810810 , -1513512   , 1621620, -926640, 218790},
                            {-3240 , 172800  ,-2494800  ,  15966720   , -54054000   ,103783680  , -113513400  ,65894400   , -15752880 },
                            { 41580 ,-2494800 ,   38419920   , -256132800 , 891891000  , -1748106360 ,1942340400 , -1141620480, 275675400},
                            {-249480  ,  15966720   , -256132800 , 1756339200 , -6243237000, 12430978560, -13984850880   , 8302694400 , -2021619600},
                            { 810810 ,   -54054000 ,  891891000 ,  -6243237000 ,22545022500 ,-45450765360   , 51648597000 ,-30918888000 ,   7581073500},
                            {-1513512  , 103783680 ,  -1748106360 ,12430978560, -45450765360  ,  92554285824, -106051785840   ,63930746880 ,-15768632880 },
                            { 1621620 ,  -113513400,  1942340400 , -13984850880  ,  51648597000 ,-106051785840 ,  122367445200   , -74205331200  ,  18396738360},
                            { -926640  , 65894400   , -1141620480, 8302694400 , -30918888000  ,  63930746880 ,-74205331200 ,   45229916160, -11263309200},
                            {218790 ,-15752880,   275675400 ,  -2021619600 ,7581073500 , -15768632880   , 18396738360 ,-11263309200    ,2815827300 }
                          };

            double[,] A2 = { {25 ,0 ,-5, 5, 25 ,-10 ,-10 ,-20 ,5 },
                              {0 ,9 ,-6, 3 ,-6 ,9 ,3 ,9 ,6 },
                              {-5 ,-6 ,21 ,-15 ,19 ,-20 ,-8 ,18 ,-9 },
                              {5 ,3 ,-15 ,12 ,-8 ,12, 1 ,-20 ,7 },
                              { 25 ,-6, 19 ,-8 ,34 ,-58 ,-38 ,-11 ,-12},
                              {-10 ,9 ,-20 ,12 ,-58 ,-15 ,43 ,10 ,-5 },
                              {-10 ,3 ,-8 ,1 ,-38 ,43 ,-7, 13 ,-10 },
                              { -20 ,9 ,18 ,-20 ,-11 ,10 ,13 ,100 ,8},
                              {5 ,6 ,-9 ,7 ,-12 ,-5 ,-10 ,8 ,-3 }
                            };

            double[,] A = { {9, 9 ,-12 ,12, 15},
                        { 9 ,18 ,-27, 0, 30},
                         {-12 ,-27, 25 ,-8 ,-57 },
                        {12 ,0 ,-8 ,19 ,-9 },
                        {15, 30 ,-57, -9 ,66 }
                       };


            double[,] test = { { 1,2,-1,1 },
                                { 2,8,2,2},
                                { -1,2,6,0},
                                { 1,2,0,6}
            };

            printA(test, 4);

            printD(test, 4);

            double norm = maxNorm(test, 4);

            double[,] inverse = Program.inverse(test, 4);

            double normInvA = maxNorm(inverse, 4);

            Console.WriteLine("\nMatrix A^1 = ");

            for (int i = 0; i < 4; ++i)
            {
                for(int j =0; j < 4; ++j)
                {
                    Console.Write(inverse[i, j] + " | ");
                }
                Console.Write("\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }

            Console.WriteLine("Conditionality number = " + norm * normInvA);

            Console.ReadLine();
        /*
            Graph graph = new Graph();
            graph.ShowDialog();

         */
        }
    }
}
