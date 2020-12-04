package lab2;

import java.util.Random;
import java.util.Scanner;

public class v22 {
    public static int localMin(int[][] matrix)
    {
        int counter = 0;
        for(int i = 1; i < matrix.length - 1; i++)
        {
            for(int j = 1; j < matrix.length - 1; j++)
            {
                if(matrix[i - 1][j] > matrix[i][j] && matrix[i + 1][j] > matrix[i][j])
                    if(matrix[i][j - 1] > matrix[i][j] && matrix[i][j + 1] > matrix[i][j])
                    {
                        counter++;
                    }
            }
        }
        return counter;
    }
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter n: ");
        int n = in.nextInt();

        if ( n <= 1 ) {
            System.err.println("Invalid n value (require: n > 1");
            System.exit( 1 );
        }

        int[][] matrix = new int [n][n];

        Random rnd = new Random();

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                matrix[i][j] = -n + rnd.nextInt(n - (-n));
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }

        System.out.println("Number of local minima :" + localMin(matrix));

    }
}
