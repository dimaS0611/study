import java.util.Arrays;
import java.util.Vector;

import Jama.*;

public class Gauss_Seidel {
    private double[][] _mtx;
    private int size = 0;                           // Размер матрицы
    private static final int ITERATIONS = 3300;      // Максимальное колличество итераций
    private static final double eps = 1e-5;        // Точность вычислений
    private double[][] mtx_B;

    public Gauss_Seidel(double[][] mtx)
    {
        _mtx = mtx;
        size = mtx.length;
        mtx_B = new double[ITERATIONS][size];
    }

    public void solve(double[][] b)
    {
        double residual = 0.0;
        Vector<Double> residualArr = new Vector<Double>();

        final double[] checkX = new double[b.length];

        for(int i = 0; i < checkX.length; ++i)
            checkX[i] = (double)i + 1;

        double[] X = new double[size];                          // Вектор Х
        double[] prev_vec = new double[size];                   // Вектор Х с предыдущей итерации

        int iterations = 0;

        Arrays.fill(X, 2);                                  // Заполняем Х начальными значениями

        while (true)
        {
            for(int i = 0; i < size; ++i)
            {
                double b_i = b[i][0];
                for(int j = 0; j < size; ++j)
                {
                    if(j == i) continue;

                    b_i -= _mtx[i][j] * X[j];             // Вычисляем Х-i
                                                        // По формуле из конспекта
                    X[i] = b_i / _mtx[i][i];
                }
            }

            System.out.print("X_" + iterations + " = [ ");      // Выводим на печать
                                                                // Х-i вектор
            for(int i = 0; i < size; ++i)
            {
                System.out.print(X[i] + " , ");
            }
            System.out.print(" ]\n");

            iterations++;


            for(int i = 0; i < size; ++i) {
                residual += Math.pow(X[i] - checkX[i], 2);      // Вычисление невязки
            }
            residualArr.add(Math.sqrt(residual));

            boolean flg = true;
            for(int i = 0; i < size && flg; ++i)
            {
                if(Math.abs(X[i] - checkX[i]) <= 0.000001)      // Проверяем точность вычислений
                    flg = false;
            }

            if(!flg ||  iterations == ITERATIONS)             // Проверяем был ли достигнут предел колличества иттераций
                break;

            mtx_B[iterations] = X;
            prev_vec = (double[])X.clone();                 // Записываем вектор Х в вектор
                                                            // предыдущей итерации
        }

        System.out.println("Residual = " + residualArr);
    }

    // Поиск матрицы В
    public double[][] findB()
    {
        int rows = _mtx.length;
        int cols = _mtx[0].length;

        double[][] D = new double[rows][cols];          // Диагональ матрицы А
        double[][] L = new double[rows][cols];          // Нижний треугольник матрицы А
        double[][] R = new double[rows][cols];          // Верхний треугольник матрицы А

        // Иницилизация матриц D, L, R
        for(int i = 0; i < rows; ++i)
        {
            D[i][i] = _mtx[i][i];
            for(int j = 0; j < cols; ++j)
            {
                if(j < i)
                    L[i][j] = _mtx[i][j];
                if(j > i)
                    R[i][j] = _mtx[i][j];
            }
        }

        Matrix d = new Matrix(D);
        Matrix l = new Matrix(L);
        Matrix r = new Matrix(R);

        // Вычисление матрицы В по формуле B = -(D + L)^-1 * R
        Matrix b = d.plus(l).inverse();
        b = b.times(r);
        b = b.uminus();

        return b.getArray();
    }

    // Вычисление максимального по модулю собственное значение
    public double findEigenValue(double[][] m)
    {
        double eigenValLast = 0;
        double eigenValNew = 0;
        double[][] vec = new double[size][1];

        // Иницилизация начального собстенного вектора
        for(int i = 0; i < size; ++i)
            vec[i][0] = 1;

        Matrix mtx = new Matrix(m);
        Matrix initVector = new Matrix(vec);

        // Нормировка собственного вектора
        Matrix eigenVec = initVector.times(1.0/ initVector.norm2());

        for(int i = 0; Math.abs(eigenValNew - eigenValLast) > eps || i == 0; ++i)
        {
            eigenValLast = eigenValNew;
            Matrix Y = mtx.times(eigenVec);                 // Вычисление вектора Y = A * u
            eigenVec = Y.times(1.0/Y.norm2());              // Вычисление собственного вектора u = Y / ||Y||_2
            eigenValNew = eigenVec.transpose().times(mtx).times(eigenVec).get(0,0); // Собственное значение l = (u, Au)
        }

        return eigenValNew;
    }

}


