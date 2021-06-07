import java.util.List;
import java.util.Random;
import java.util.Vector;

public class Main {
    static long M = Long.parseUnsignedLong("2147483648");
    static int K = 128;
    static int alpha0 = 131075;
    static int beta = 131075;
    static int alpha = alpha0;
    static List<Double> V = new Vector<Double>(128);

    static double generateElement_MultiplicativeCongruence() {
        alpha = (int) ((beta * alpha) % M);
        return ((double) alpha / M);
    }

    static double generateElement_McLarenMarseille() {
        long index = (long) Math.abs((generateElement_MultiplicativeCongruence() * M) % K);
        double x = (V.get(Math.abs((int) index)));
        V.set(Math.abs((int) index), generateElement_MultiplicativeCongruence());

        return Math.abs(x);
    }

    static double expectation(double[] a, int n) {
        double s = 0;
        for (int i = 0; i < n; i++)
            s += a[i];
        return s / n;
    }

    static double dispersion(double[] a, int n) {
        double s = 0, s2 = 0;
        for (int i = 0; i < n; i++) {
            s += a[i];
            s2 += a[i] * a[i];
        }
        return (s2 - s * s / n) / (n - 1);
    }

    static void firstIntegral(double[] x, double[] A, int n) {
        for (int i = 0; i < n; i++) {
            do {
                x[i] = 4 * generateElement_McLarenMarseille();
            } while (x[i] < 1 || x[i] > 3);

            A[i] = 4 * Math.log(x[i]) * Math.exp(x[i]) * Math.sin(x[i]);
        }

        System.out.println("Integral  = E  = 17.7594");
        System.out.println("Integral* = E* = " + expectation(A, n));
        System.out.println("D = " + dispersion(A, n) );
        System.out.println("Delta = " + 0.6745 * Math.sqrt(dispersion(A, n) / n) );
    }

    static void secondIntegral(double[] x, double[] y, double[] A, int n) {
        double sign = 1.0;
        double sqrt1on3 = Math.sqrt((double)1 / 3);
        Random rnd = new Random();
        double tmp = 0;

        for (int i = 0; i < n; i++) {
            do {

                sign = Math.pow(-1, -(rnd.nextInt() % 2));
                x[i] = sign * Math.sqrt(generateElement_McLarenMarseille()) * sqrt1on3;
                sign = Math.pow(-1, -(rnd.nextInt() % 2));
                y[i] = sign * Math.sqrt(generateElement_McLarenMarseille()) * sqrt1on3;

            } while (Math.abs(x[i]) + Math.abs(y[i]) >= 1);

            A[i] = (x[i] / 3 + y[i] / x[i]) * Math.exp(y[i]);
        }

        System.out.println("Integral  = E  = 0");
        System.out.println("Integral* = E* = " + expectation(A, n));
        System.out.println("D = " + dispersion(A, n));
        System.out.println("Delta = " + 0.6745 * Math.sqrt(dispersion(A, n) / n) );
    }


    public static void main(String[] args) {
        int n;

        for (int i = 0; i < K; i++)
            V.add(generateElement_MultiplicativeCongruence());
        System.out.println("\n************\n1st integral\n**************\n");
        for (n = 20; n < 5000; n += 50) {

            double[] A = new double[n];
            double[] x = new double[n];
         //   double[] y = new double[n];

            System.out.println("N = " + n );
            firstIntegral(x, A, n);
        }

        System.out.println("\n************\n2nd integral\n***************\n");
        for (n = 20; n < 5000; n += 50) {

            double[] A = new double[n];
            double[] x = new double[n];
            double[] y = new double[n];

            System.out.println("N = " + n + "\n");
            secondIntegral(x, y, A, n);
        }
    }
}
