import org.apache.commons.math3.distribution.ChiSquaredDistribution;
import org.apache.commons.math3.special.Erf;

import java.util.Arrays;
import java.util.Random;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Main {
    final static double aVeib = 0.5;
    final static double bVeib = 1;

    final static double aKosh = -1;
    final static double bKosh = 1;

    final static double aLog = -1;
    final static double bLog = 2;

    final static double mNorm1 = 0;
    final static double s2Norm1 = 1;

    final static double mNorm2 = -1;
    final static double s2Norm2 = 4;

    final static double aExp = 0.25;

    static double FindDispersion(double[] sequence,double mathExpect)
    {
        double sum = 0;
        for (int i = 0; i<sequence.length; ++i) {
            sum += (sequence[i] - mathExpect) * (sequence[i] - mathExpect);
        }

        return  sum / (sequence.length-1);
    }

    static double  FindMathExpectation(double[] sequence)
    {
        return Arrays.stream(sequence).sum()/sequence.length;
    }

    public static double NormalDistribution(double value, Double[] p) {
        double m = p[0];
        double s = Math.sqrt(p[1]);
        return 0.5*(1.+ Erf.erf((value-m)/(s*Math.sqrt(2))));
    }

    static double VeibulDistribution(double value, Double[] p)
    {
        Double a = p[0];
        Double b = p[1];
        return 1 -Math.exp(-Math.pow(value/b,a));
    }

    static double KoshiDistribution(double value, Double[] p)
    {
        double a = p[0];
        return 0.5+1/Math.PI*Math.atan((value-a)/a);
    }

    static double LogisticDistribution(double value, Double[] p)
    {
        Double a = p[0];
        Double b = p[1];
        return 1/(1+Math.exp(-(value-a)/b));
    }

    public static double ExpDistribution(double value, Double[] p)
    {
        Double a = p[0];
        return 1 - Math.exp(-a * value);
    }

    static double[] VeibulModel(double a,double b, int n)
    {
        double[] sequence = new double[n];
        Random rnd = new Random();
        for (int i = 0; i < n; i++)
        {
            sequence[i] = b * Math.pow(-Math.log(1 - rnd.nextDouble()), 1 / a);
        }
        return sequence;
    }

    static double[] LogisticModel(double a, double b,int n)
    {
        double[] sequence = new double[n];
        Random rnd = new Random();
        for (int i=0;i<n;i++)
        {
            double y = rnd.nextDouble();
            sequence[i] = a + b * Math.log(y / (1 - y));
        }

        return sequence;
    }

    static double[] KoshiModel(double a, double b, int n)
    {
        double[] sequence = new double[n];
        Random rnd = new Random();
        for (int i=0;i<n;i++)
        {
            sequence[i] = a + b * Math.tan(Math.PI * (rnd.nextDouble() - 0.5));
        }

        return sequence;
    }

    static double[] NormalModel(double m, double s2, int n)
    {
        double[] sequence = new double[n];
        Random rnd = new Random();
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < 12; j++)
            {
                sum += rnd.nextDouble();
            }

            sequence[i] = m + (sum - 6) * Math.sqrt(s2);
        }

        return sequence;
    }

    public static double[] ExpModel(double a, int n)
    {
        double[] exps = new double[n];

        Random rnd = new Random();
        double[] sequence = new double[n];
        for (int i = 0; i < n; ++i) {
            sequence[i] = rnd.nextDouble();
        }

        for (int i = 0; i < n; i++) {
            exps[i] = -(1 / a) * Math.log(sequence[i]);
        }
        return exps;
    }

    public static boolean checkKolmogorov(double[] sequence, BiFunction<Double, Double[], Double> distribution, Double[] parameters)
    {
        var sorted = Arrays.stream(sequence).sorted().toArray();
        double k = 100; // number of segments
        double sup = 0;
        double start = sorted[0];
        double finish = sorted[sorted.length - 1];
        double step = (finish - start) / k;
        int enteredCount = 0;
        for (double x = start; x <= finish; x += step) {
            while (sorted[enteredCount] < x) {
                enteredCount++;
            }
            var f = Math.abs(((double) enteredCount) / sorted.length - distribution.apply(x, parameters));
            sup = Math.max(f, sup);
        }
        var critical = 1.36 / Math.sqrt(sequence.length);
        return sup < critical;
    }

    static boolean checkHiSquare(double[] values, BiFunction<Double, Double[], Double> p, Double[] parameters)
    {
        var unique = Arrays.stream(values).boxed().collect(
                Collectors.groupingBy(Function.identity(), Collectors.counting()));
        int K = 100;
        int[] frequences = new int[K];
        double[] prob = new double[K];
        var sorted = Arrays.stream(values).sorted().toArray();
        int j = 0;
        double pr = (sorted[sorted.length-1] - sorted[0]) / K;
        double prev = sorted[0];
        for (double i = sorted[0] + pr; i < sorted[sorted.length-1]; i += pr) {
            for (var sv : unique.entrySet()) {
                if (sv.getKey() >= prev && sv.getKey() < i)
                    frequences[j] += sv.getValue();
                prob[j] = p.apply(i, parameters) - p.apply(prev, parameters);
            }
            j++;
        }
        int n = values.length;
        double hiSquare = 0;
        for (int i = 0; i < K; i++) {
            hiSquare += Math.pow((frequences[i] - n * prob[i]), 2) / (n * prob[i]);
        }
        var critical = new ChiSquaredDistribution(unique.size() - 1)
                .inverseCumulativeProbability(1 - 0.05);
        return hiSquare <= critical;
    }


    public static void main(String[] args)
    {

        int n = 1000;

        double[] logistic = LogisticModel(aLog, bLog, n);
        double[] veibul = VeibulModel(aVeib, bVeib,n);
        double[] koshi = KoshiModel(aKosh, bKosh, n);
        double[] firstNormal = NormalModel(mNorm1, s2Norm1, n);
        double[] secondNormal = NormalModel(mNorm2, s2Norm2, n);
        double[] exp = ExpModel(aExp, n);

        double veibulExpect = FindMathExpectation(veibul);
        double logisticExpect = FindMathExpectation(logistic);
        double koshiExpect = FindMathExpectation(koshi);
        double firstNormalExpect = FindMathExpectation(firstNormal);
        double secondNormalExpect = FindMathExpectation(secondNormal);
        double expExpect = FindMathExpectation(exp);

        double veibulDispersion = FindDispersion(veibul, veibulExpect);
        double logisticDispersion = FindDispersion(logistic, logisticExpect);
        double koshiDispersion = FindDispersion(koshi, koshiExpect);
        double firstNormalDispersion = FindDispersion(firstNormal, firstNormalExpect);
        double secondNormalDispersion = FindDispersion(secondNormal, secondNormalExpect);
        double expDispersion = FindDispersion(exp, expExpect);

        var par = new Double[]{mNorm1, s2Norm1};
        System.out.println("\nМатематическое ожидание  первой нормальной последовательности: "+firstNormalExpect);
        System.out.println("Теоретическое математическое ожидание первой нормальной последовательности: "+mNorm1);
        System.out.println("Дисперсия первой нормальной последовательности: "+firstNormalDispersion);
        System.out.println("Теоретическая дисперсия первой нормальной последовательности: "+s2Norm1);
        System.out.println("Хи квадрат для первого нормального распределения: " + checkHiSquare(firstNormal, Main::NormalDistribution, par));
        System.out.println("Колмогоров для первого нормального распределения: "+ checkKolmogorov(firstNormal, Main::NormalDistribution, par));

        var par2 = new Double[]{mNorm2, s2Norm2};
        System.out.println("\nМатематическое ожидание  второй нормальной последовательности: "+secondNormalExpect);
        System.out.println("Теоретическое математическое ожидание второй нормальной последовательности: "+mNorm2);
        System.out.println("Дисперсия второй нормальной последовательности: "+secondNormalDispersion);
        System.out.println("Теоретическая дисперсия второй нормальной последовательности: "+s2Norm2);
        System.out.println("Хи квадрат для второго нормального распределения: " + checkHiSquare(secondNormal, Main::NormalDistribution, par2));
        System.out.println("Колмогоров для второго нормального распределения: "+ checkKolmogorov(secondNormal, Main::NormalDistribution, par2));

        var par3 = new Double[]{aKosh};
        System.out.println("\nМатематическое ожидание последовательности Коши: "+koshiExpect);
        System.out.println("Теоретическое математическое ожидание последовательности Коши не существует.");
        System.out.println("Дисперсия последовательности Коши: "+koshiDispersion);
        System.out.println("Теоретическая дисперсия последовательности Коши равна бесконечности");

        var par4 = new  Double[]{aLog, bLog};
        System.out.println("\nМатематическое ожидание логистической последовательности: "+logisticExpect);
        System.out.println("Теоретическое математическое ожидание логистической последовательности: "+aLog);
        System.out.println("Дисперсия логистической последовательности: "+logisticDispersion);
        System.out.println("Теоретическая дисперсия логистической последовательности: "+Math.PI*Math.PI*bLog*bLog/3);
        System.out.println("Хи квадрат для логистического распределения: " + checkHiSquare(logistic, Main::LogisticDistribution, par4));
        System.out.println("Колмогоров для логистического распределения: "+ checkKolmogorov(logistic, Main::LogisticDistribution, par4));

        var par5 = new Double[]{aVeib, bVeib};
        System.out.println("\nМатематическое ожидание  последовательности Вейбулла: "+veibulExpect);
        System.out.println("Теоретическое математическое ожидание  Вейбулла: "+0.5);
        System.out.println("Дисперсия  последовательности Вейбулла: "+veibulDispersion);
        System.out.println("Теоретическая дисперсия последовательности Вейбулла: "+0.25);
        System.out.println("Хи квадрат для распределения Вейбула: " + checkHiSquare(veibul, Main::VeibulDistribution, par5));
        System.out.println("Колмогоров для распределения Вейбула: "+ checkKolmogorov(veibul, Main::VeibulDistribution, par5));

        var par6 = new Double[]{aExp};
        System.out.println("\nМатематическое ожидание экспоненчиальной последовательности: " + expExpect);
        System.out.println("Теоретическое математическое ожидание экспоненчиальной последовательности:" + 1 / aExp);
        System.out.println("Дисперсия  последовательности экспоненчиальной последовательности: " + expDispersion);
        System.out.println("Дисперсия  последовательности экспоненчиальной последовательности:" + 1 / (aExp *aExp));
        System.out.println("Хи квадрат для экспоненциального распределения: " + checkHiSquare(exp, Main::ExpDistribution, par6));
        System.out.println("Колмогоров для экспоненциального распределения: " + checkKolmogorov(exp, Main::ExpDistribution, par6));
  }
}
