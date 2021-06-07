import Jama.Matrix;

public class Main
{
    // Генерация ветора В = А * x
    public static double[][] generateB(double[][] a)
    {
        double[][] x = new double[a.length][1];
        for (int i = 0; i < x.length; ++i)
            x[i][0] = i + (double)1;

        Matrix mtx = new Matrix(a);
        return mtx.times(new Matrix(x)).getArray();
    }

    public static void main(String[] args)
    {
        double[][] A = {{ 5.756715842744740, -1.010534294645010, 0.179143472776699, -0.777826810527572, 2.150078778177510 },
                { -1.010534294645010, 7.255382826978440, -0.608525486543986, 0.914013615923265, 1.393256119606160 },
                { 0.179143472776699, -0.608525486543986, 6.677958320454920, 3.902085066011900, 1.333228802482270 },
                { -0.777826810527572, 0.914013615923265, 3.902085066011900, 4.264232839965460, 0.115465148485055 },
                { 2.150078778177510, 1.393256119606160, 1.333228802482270, 0.115465148485055, 6.045710169856440}};

        double[][] b = generateB(A);

        Gauss_Seidel mtx = new Gauss_Seidel(A);     // Иницилизация матрицы класса Gauss_Seidel
        mtx.solve(b);                               // Рещение СЛАУ

        double eigen = mtx.findEigenValue(mtx.findB()); // Поиск максимального по модулю собственного значения
                                                        // степенным методом

        System.out.println("Eigen value = " + eigen + "\n");

        double[][] A2 = { {350.726932255198000, -150.418258876414000, -141.381751875705000, 22.324917618691500, -192.460876793127000 },
        { -150.418258876414000, 614.835090129774000, -192.378645757147000, -27.296734402377300, -77.856101812775600 },
        {-141.381751875705000, -192.378645757147000, 510.579978629757000, -118.550626243563000, -185.433744113963000 },
        { 22.324917618691500, -27.296734402377300, -118.550626243563000, 513.920576673718000, 4.715276404967150 },
        { -192.460876793127000, -77.856101812775600, -185.433744113963000, 4.715276404967110, 516.937422311553000 } };

        double[][] b2 = generateB(A2);

        Gauss_Seidel mtx2 = new Gauss_Seidel(A2);
        mtx2.solve(b2);

        double eigen2 = mtx.findEigenValue(mtx2.findB());

        System.out.println("Eigen value = " + eigen2);

        double[][] B = mtx.findB();
        double[][] B1 = mtx2.findB();

        System.out.println("B1 = ");
        for(int i = 0; i < 5; ++i)
        {
            System.out.print("[ ");
            for(int j = 0; j < 5; ++j)
            {
                System.out.print(B[i][j] + " ");
            }
            System.out.print(" ]\n");
        }

        System.out.println("B2 = ");
        for(int i = 0; i < 5; ++i)
        {
            System.out.print("[ ");
            for(int j = 0; j < 5; ++j)
            {
                System.out.print(B1[i][j] + " ");
            }
            System.out.print(" ]\n");
        }




        double[][] k = {{6,-1,0}, {0,5,0}, {0,-22,-6}};
        Gauss_Seidel g = new Gauss_Seidel(k);
        double r = g.findEigenValue(k);

        System.out.println(r);
    }
}
