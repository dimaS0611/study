namespace lab1_1
{
    public class VectorD
    {
        double[] _M;
        int _Cols;
        public double[] M { get { return _M; } set { _M = M; } }
        public int Cols { get { return _Cols; } }
        public VectorD(int cols)
        {
            _M = new double[cols];
            _Cols = cols;
        }
    }

    public class MatrixD
    {
        double[,] _M;
        int _Rows;
        int _Cols;

        public int Rows { get { return _Rows; }  }
        public int Cols { get { return _Cols; }  }        
        public double[,] M { get { return _M; } }
        public MatrixD(int rows, int cols)
        {
            _M = new double[rows, cols];
            _Rows = rows;
            _Cols = cols;
        }

        public static VectorD operator *(MatrixD m, VectorD v)
        {
            VectorD r = new VectorD(v.Cols);

            for (int i = 0; i < r.Cols; ++i)
            {
                double s = 0.0;
                for (int j = 0; j < m.Rows; ++j)
                {
                    s += m.M[j, i] * v.M[i];
                }
                r.M[i] = s;
            }

            return r;
        }

        public MatrixD InversM2()
        {
            MatrixD r = new MatrixD(this.Rows, this.Cols);

            double oneOverDeterminant = (1) / (this.M[0, 0] * this.M[1, 1]
                                - this.M[0, 1] * this.M[1, 0]);

            r.M[0, 0] = (this.M[1, 1] * oneOverDeterminant);
            r.M[0, 1] = -(this.M[0, 1] * oneOverDeterminant);
            r.M[1, 0] = -(this.M[1, 0] * oneOverDeterminant);
            r.M[1, 1] = (this.M[0, 0] * oneOverDeterminant);

            return r;
        }

        public MatrixD InversM3()
        {
            MatrixD r = new MatrixD(this.Rows, this.Cols);

            double oneOverDeterminant = (1) / (
                this.M[0, 0] * (this.M[1, 1] * this.M[2, 2] - this.M[2, 1] * this.M[1, 2])
                - this.M[1, 0] * (this.M[0, 1] * this.M[2, 2] - this.M[2, 1] * this.M[0, 2])
                + this.M[2, 0] * (this.M[0, 1] * this.M[1, 2] - this.M[1, 1] * this.M[0, 2]));

            r.M[0, 0] = (this.M[1, 1] * this.M[2, 2] - this.M[2, 1] * this.M[1, 2]) * oneOverDeterminant;
            r.M[1, 0] = -(this.M[1, 0] * this.M[2, 2] - this.M[2, 0] * this.M[1, 2]) * oneOverDeterminant;
            r.M[2, 0] = (this.M[1, 0] * this.M[2, 1] - this.M[2, 0] * this.M[1, 1]) * oneOverDeterminant;
            r.M[0, 1] = -(this.M[0, 1] * this.M[2, 2] - this.M[2, 1] * this.M[0, 2]) * oneOverDeterminant;
            r.M[1, 1] = (this.M[0, 0] * this.M[2, 2] - this.M[2, 0] * this.M[0, 2]) * oneOverDeterminant;
            r.M[2, 1] = -(this.M[0, 0] * this.M[2, 1] - this.M[2, 0] * this.M[0, 1]) * oneOverDeterminant;
            r.M[0, 1] = (this.M[0, 1] * this.M[1, 2] - this.M[1, 1] * this.M[0, 2]) * oneOverDeterminant;
            r.M[1, 2] = -(this.M[0, 0] * this.M[1, 2] - this.M[1, 0] * this.M[0, 2]) * oneOverDeterminant;
            r.M[2, 2] = (this.M[0, 0] * this.M[1, 1] - this.M[1, 0] * this.M[0, 1]) * oneOverDeterminant;

            return r;
        }
    }
    
    
}
