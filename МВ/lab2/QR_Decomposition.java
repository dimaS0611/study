import Jama.Matrix;
import Jama.util.*;

public class QR_Decomposition {

    /** Двумерный массив хранящий QR разложение
     */
    private double[][] QR;

    /** Количество строк и столбцов
     */
    private int m, n;

    /** Массив для хранения диагонали R.
     */
    private double[] Rdiag;


    /** QR-разложение, вычисляемая по методу отражений.
     Конструктор инициализирует структуру для доступа к R и векторам отражений, и вычисления Q.
     */

    public QR_Decomposition (Matrix A) {
        QR = A.getArrayCopy();
        m = A.getRowDimension();
        n = A.getColumnDimension();
        Rdiag = new double[n];

        for (int k = 0; k < n; k++) {
            // Вычисление 2-нормы для К-ой столбца
            double nrm = 0;
            for (int i = k; i < m; i++) {
                nrm = Maths.hypot(nrm, QR[i][k]);
            }

            if (nrm == 0.0)
                continue;

            // Нормирование К-ого cтолюца
            
            // Примените преобразования к нижнему правому треугольнику
            for (int j = k + 1; j < n; j++) {
                // Вычисляем сумму произведений элементов к-ой и j-ой строки
                double v = 0.0;
                for (int i = k; i < m; i++) {
                    v += QR[i][k] * QR[i][j];
                }
                // Нормируем сумму на диагональный элемент
                v = -v / QR[k][k];
                // Добовляем к j-й строке к-ю строку умноженную на нормированный вектор
                for (int i = k; i < m; i++) {
                    QR[i][j] += v * QR[i][k];
                }
            }


            Rdiag[k] = -nrm;
        }
    }

    /** Метод находит Евклидову норму матрицы
     */
    public double FindNorm(Matrix mtx)
    {
        double norm = 0;

        for(int i = 0; i < mtx.getRowDimension(); i++)
            for(int j = 0; j < mtx.getColumnDimension(); j++)
                norm += Math.pow(mtx.get(i,j), 2);


        return Math.sqrt(norm);
    }

    /** Решение наименьших квадратов A*X = B
     X вектор, который минимизирует две нормы Q*R*X-B. */

    public Matrix solve (Matrix B) throws Exception {
        if (B.getRowDimension() != m) {
            throw new Exception("Matrix row dimensions must agree!");
        }

        int nx = B.getColumnDimension();
        double[][] X = B.getArrayCopy();

        // Y = Q^T * B
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < nx; j++) {
                double v = 0.0;
                for (int i = k; i < m; i++) {
                    v += QR[i][k]*X[i][j];
                }
                v = -v/QR[k][k];
                for (int i = k; i < m; i++) {
                    X[i][j] += v*QR[i][k];
                }
            }
        }

        // R*X = Y;
        for (int k = n-1; k >= 0; k--) {
            for (int j = 0; j < nx; j++) {
                X[k][j] /= Rdiag[k];
            }
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < nx; j++) {
                    X[i][j] -= X[k][j]*QR[i][k];
                }
            }
        }
        return (new Matrix(X,n,nx).getMatrix(0,n-1,0,nx-1));
    }

}
