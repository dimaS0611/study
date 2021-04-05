using System;
using System.Collections.Generic;

namespace lab2
{
    class Program
    {
        static double FindDispersion(List<double> sequence, double MathExpect)
        {
            int n = sequence.Count;
            double sum = 0;

            for (int i = 0; i < n; i++)
                sum += (sequence[i] - MathExpect) * (sequence[i] - MathExpect);

            return sum / (n - 1);
        }
        static double FindMathExpectation(List<double> sequence)
        {
            double sum = 0, n = sequence.Count;

            for (int i = 0; i < n; i++)
                sum += sequence[i];

            return sum / n;
        }

        static bool PearsonGeometric(List<double> sequence, double p)
        {
            int n = sequence.Count;
            double maxValue = 0;

            for (int i = 0; i < n; i++)
                if (sequence[i] > maxValue)
                    maxValue = sequence[i];

            List<double> valuesNum = new List<double>();

            for (int i = 0; i <= maxValue; i++)
                valuesNum.Add(0);

            List<double> probabilities = new List<double>();

            for (int i = 0; i <= maxValue; i++)
                probabilities.Add(Math.Pow(1 - p, i) * p);

            for (int i = 0; i < n; i++)
                valuesNum[(int)sequence[i]]++;

            double hi = 0;
            for (int i = 0; i <= maxValue; i++)
                hi += ((double)valuesNum[i] / n - probabilities[i]) * ((double)valuesNum[i] / n - probabilities[i]) /
                      probabilities[i];

            List<double> deltas = new List<double>() { 0.0039, 0.1026, 03518, 0.7107, 1.1455, 1.6354, 2.1673, 2.7326, 3.3251, 3.9403 };
            if (maxValue > 9)

                maxValue = 9;

            if (hi < deltas[(int)maxValue])
                return true;

            return false;
        }

        static List<double> GeometricModel(double p, int n)
        {
            List<double> sequence = new List<double>();
            Random rnd = new Random();

            for (int i = 0; i < n; i++)
                sequence.Add((int)Math.Log(rnd.NextDouble(), 1 - p) + 1);

            return sequence;
        }

        static List<double> PuassonModel(double lambda, int n)
        {
            double L = Math.Exp(-lambda), r, pr;
            List<double> sequence = new List<double>();
            Random random = new Random();

            for (int i = 0; i < n; i++)
            {
                r = random.NextDouble();
                pr = r;
                int k;
                for (k = 0; pr > L; k++)
                {
                    r = random.NextDouble();
                    pr *= r;
                }
                sequence.Add(k);
            }

            return sequence;
        }

        static bool PearsonPuasson(List<double> sequence, double lambda)
        {
            int n = sequence.Count;
            double maxValue = 0;

            for (int i = 0; i < n; i++)
                if (sequence[i] > maxValue)
                    maxValue = sequence[i];

            List<int> valuesNum = new List<int>();
            for (int i = 0; i <= maxValue; i++)
                valuesNum.Add(0);

            List<double> probabilities = new List<double>();
            double pr = Math.Exp(-lambda);
            probabilities.Add(pr);

            for (int i = 1; i <= maxValue; i++)
            {
                pr *= lambda / i;
                probabilities.Add(pr);
            }

            for (int i = 0; i < n; i++)
                valuesNum[(int)sequence[i]]++;
            double hi = 0;

            for (int i = 0; i <= maxValue; i++)
                hi += ((double)valuesNum[i] / n - probabilities[i]) * ((double)valuesNum[i] / n - probabilities[i]) /
                      probabilities[i];

            List<double> deltas = new List<double>() { 0.0039, 0.1026, 0.3518, 0.7107, 1.1455, 1.6354, 2.1673, 2.7326, 3.3251, 3.9403 };

            if (maxValue > 9)
                maxValue = 9;

            if (hi < deltas[(int)maxValue])
                return true;

            return false;
        }

        public static List<double> lkGen(int n)
        {
            int x0 = (int)(DateTime.Now.Millisecond % 2e31);
            int a = (int)(DateTime.Now.Millisecond % 2e31);
            List<double> nums = new List<double>(n);

            double el = x0;
            for (int i = 0; i < n; ++i)
            {
                el = (a * el) % 2e31;
                nums.Add(el / 2e31);
            }

            return nums;
        }

        private static int Cominations(double allNumbers, double perGroup)
        {
            return Factorial(allNumbers) / Factorial(allNumbers - perGroup);
        }

        private static int Factorial(double number)
        {
            int n = 1;

            for (int i = 1; i < number; i++)
            {
                n *= i;
            }

            return n; 
        }

        public static List<double> NegBinomialModel(int n, double r, double p)
        {
            List<double> nums = new List<double>();
            //List<double> bsv = lkGen(n);
            double k = 0;
            double m = r;
            double q = 1 - p;
            for (int i = 0; i < n; i++)
            {
                k += Math.Pow(q, i) * Cominations(i + m - 1, i);
                nums.Add(k * Math.Pow(p, m));
                /*
                double c = 1 / (Math.Log(1 - p));
                double z = 0;
                int i = 0;
                do
                {
                    i++;
                    r = bsv[k++ % n];
                    double x = Math.Floor(c * Math.Log(r));
                    z = z + x;
                } while (i < m);

                nums.Add(z);
                */
            }

            return nums;
        }

        static void Main(string[] args)
        {
            const double pGeom = 0.8;
            const double pGeom2 = 0.4;
            const double lambda = 0.3;
            const double rNegBinom = 7;
            const double pNegBinom = 0.2;
            int n = 1000;

            List<double> geometric = GeometricModel(pGeom, n);
            List<double> geometric2 = GeometricModel(pGeom2, n);
            List<double> puasson = PuassonModel(lambda, n);
            List<double> negBinom = NegBinomialModel(n, rNegBinom, pNegBinom);

            double geometricExpect = FindMathExpectation(geometric);
            double geometricExpect2 = FindMathExpectation(geometric2);
            double puassonExpect = FindMathExpectation(puasson);
            double negBinomExpecrt = FindMathExpectation(negBinom);

            double geometricDispersion = FindDispersion(geometric, geometricExpect);
            double geometricDispersion2 = FindDispersion(geometric2, geometricExpect2);
            double puassonDispersion = FindDispersion(puasson, puassonExpect);
            double negBinomDispersion = FindDispersion(negBinom, negBinomExpecrt);

            bool pearsonGeom = PearsonGeometric(geometric, pGeom);
            bool pearsonGeom2 = PearsonGeometric(geometric2, pGeom2);
            bool pearsonPuasson = PearsonPuasson(puasson, lambda);

            Console.WriteLine("Математическое ожидание геометрической последовательности: " + geometricExpect);
            Console.WriteLine("Теоретическое математическое ожидание геометрической последовательности: " + 1 / pGeom);
            Console.WriteLine("Дисперсия геометрической последовательности: " + geometricDispersion);
            Console.WriteLine("Теоретическая дисперсия геометрической последовательности: " + (1 - pGeom) / (pGeom * pGeom));
            Console.WriteLine("Тест пирсона геометрической последовательности = " + pearsonGeom);

            Console.WriteLine("\nМатематическое ожидание 2-ой геометрической последовательности: " + geometricExpect2);
            Console.WriteLine("Теоретическое математическое ожидание 2-ой геометрической последовательности: " + 1 / pGeom2);
            Console.WriteLine("Дисперсия 2-ой геометрической последовательности: " + geometricDispersion2);
            Console.WriteLine("Теоретическая дисперсия2-ой геометрической последовательности: " + (1 - pGeom2) / (pGeom2 * pGeom2));
            Console.WriteLine("Тест пирсона 2-ой геометрической последовательности = " + pearsonGeom2);

            Console.WriteLine("\nМатематическое ожидание  последовательности пуассона: " + puassonExpect);
            Console.WriteLine("Теоретическое математическое ожидание  пуассона: " + lambda);
            Console.WriteLine("Дисперсия  последовательности пуассона: " + puassonDispersion);
            Console.WriteLine("Теоретическая дисперсия последовательности пуассона: " + lambda);
            Console.WriteLine("Тест пирсона распределение Пуассона = " + pearsonPuasson);
            
            Console.WriteLine("\nМатематическое ожидание отрицательной биномиальной последовательности: " + negBinomExpecrt);
            Console.WriteLine("Теоретическое математическое ожидание отрицательной биномиальной: " + rNegBinom * (1 -pNegBinom)/ pNegBinom);
            Console.WriteLine("Дисперсия  последовательности отрицательной биномиальной: " + negBinomDispersion);
            Console.WriteLine("Теоретическая дисперсия последовательности отрицательной биномиальной: " + rNegBinom * (1 - pNegBinom) / (pNegBinom * pNegBinom));
            Console.WriteLine("Тест пирсона распределение отрицательной биномиальной = " + pearsonGeom2);

            Console.ReadLine();
        }
    }
}
