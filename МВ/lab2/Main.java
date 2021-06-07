import Jama.Matrix;

public class Main {
    public static void main(String[] args) throws Exception {
        double mtxA[][] = { {5 ,-1 ,1, 9 ,-5 ,9, 1 ,-7 ,-9, -3},
                { -1, 2 ,-3 ,7 ,-4 ,-2, 9 ,10 ,10 ,-7},
                {6 ,-8 ,-4 ,-9 ,-9 ,-9 ,6, 3 ,-9 ,4},
                {8 ,2 ,-8 ,-8 ,10 ,3 ,-9, -2 ,5, 1},
                {9 ,5 ,8 ,-5,-5,-3,-1, 9 ,-2, 8},
                {-10,7 ,-6,-3,8,10,1,-5,-3,-2},
                {-1, 4 ,0 ,6 ,-7 ,-7, 2 ,2 ,8 ,-5},
                {8 ,-10,-10,-8,-7,8 ,8 ,4 ,4 ,-3},
                {-10,-5 ,-3,-3,4,6,1,8,-2,4},
                { 7 ,-2, -9 ,10 ,-9 ,4 ,-9 ,4 ,0 ,-5} };

        double mtxB[][] = { { 0}, {21} ,{ -29},{ 2},{ 23}, {-3}, {2}, {-6}, {0}, {-9} };

        Matrix B = new Matrix(mtxB);

        for(int i = 0; i < mtxA[0].length; i++)
        {
            double[][] mtxAk = new double[mtxA.length][i+1];

            for(int k = 0; k < mtxA[0].length; k++)
            {
                for(int m = 0; m <= i; m++)
                {
                    mtxAk[k][m] = mtxA[k][m];
                }
            }

            Matrix A = new Matrix(mtxAk);

            QR_Decomposition Ak = new QR_Decomposition(new Matrix(mtxAk));

            Matrix Xk = Ak.solve(B);

            System.out.println("\nx^" + (i + 1) + " = \n");
            Xk.print(i, mtxA[0].length);

            Matrix rk = A.times(Xk);
            rk = rk.minus(B);

            System.out.println("\n||r|| = "+ Ak.FindNorm(rk) +"\n");

        }

        double[][] m = new double[mtxA.length][mtxA.length + 1];

        for(int i = 0 ; i < m.length; ++i)
        {
            for(int j = 0; j < m.length; ++j)
            {
                m[i][j] = mtxA[i][j];
                m[i][m.length - 1] = mtxB[i][0];
            }
        }


        QR_Decomposition qr = new QR_Decomposition(new Matrix(mtxA));


    }

}
