using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Castles
{
    public class CellIndex
    {
        public int _x;
        public int _y;

        public CellIndex(int x = -1, int y = -1)
        {
            _x = x;
            _y = y;
        }

        public bool empty()
        {
            return (_x < 0 || _y < 0);
        }
    }

    public class CheesBoard
    {
        int[,] _board;
        int _rows;
        int _cols;
        public CheesBoard(int[,] board, int sizeN, int sizeM)
        {
            _board = board;
            _rows = sizeN;
            _cols = sizeM;
        }

        public int getCountRow() { return _rows; }
        public int getCountCol() { return _cols; }
        
        public int getValue(int x, int y)
        {
            return _board[x ,y];
        }

        public void setValue(int i , int j, int value)
        {
            _board[i,j] = value;
        }
    }

    class Program
    {

        public static int Solver(CheesBoard board)
        {
            int result = 0;

            for (int i = 0; i < board.getCountRow(); ++i)

                for (int j = 0; j < board.getCountCol(); ++j)
                {
                    if (board.getValue(i,j) != -1)
                    {
                        LinkedList<CellIndex> squares = new LinkedList<CellIndex>();

                        CellIndex square = new CellIndex(i, j);
                        squares.AddLast(square);

                        board.setValue(i,j,-1);

                        while (squares.Count != 0)
                        {
                            CellIndex sq = squares.Last();
                            squares.RemoveLast();

                            if (sq._x > 0)
                            {
                                if (board.getValue(sq._x - 1, sq._y) != -1)
                                {
                                    board.setValue(sq._x - 1, sq._y, -1);
                                    squares.AddLast(new CellIndex(sq._x - 1, sq._y));
                                }
                            }

                            if (sq._x < board.getCountRow() - 1)
                            {
                                if (board.getValue(sq._x + 1, sq._y) != -1)
                                {
                                    board.setValue(sq._x + 1, sq._y, -1);
                                    squares.AddLast(new CellIndex(sq._x + 1, sq._y));
                                }
                            }

                            if (sq._y > 0)
                            {
                                if (board.getValue(sq._x, sq._y - 1) != -1)
                                {
                                    board.setValue(sq._x, sq._y - 1, -1);
                                    squares.AddLast(new CellIndex(sq._x, sq._y - 1));
                                }
                            }

                            if (sq._y < board.getCountCol() - 1)
                            {
                                if (board.getValue(sq._x, sq._y + 1) != -1)
                                {
                                    board.setValue(sq._x, sq._y + 1, -1);
                                    squares.AddLast(new CellIndex(sq._x, sq._y + 1));
                                }
                            }

                        }

                        result++;
                    }


                }


            return result;
        }

        static void Main(string[] args)
        {
            StreamReader sr = new StreamReader("in.txt");
            StreamWriter sw = new StreamWriter("out.txt");

            var tmp = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

            int sizeN = int.Parse(tmp[0]);
            int sizeM = int.Parse(tmp[1]);


            int[,] mtx = new int [sizeN + 2,sizeM + 2];

            for (int i = 0; i < sizeM+ 2; ++i)
            {
                mtx[0, i] = -1;
                mtx[sizeN + 1, i] = -1;
            }
            
            for (int i = 0; i < sizeN + 2; ++i)
            {
                mtx[i, 0] = -1;
                mtx[i,sizeM + 1] = -1;
            }
            

            for (int i = 0; i < sizeN; ++i)
            {
                var mtxLine = sr.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                for (int j = 0; j < sizeM; ++j)
                {
                    mtx[i + 1,j + 1] = int.Parse(mtxLine[j]);
                }
            }

            CheesBoard board = new CheesBoard(mtx, sizeN, sizeM);

            int result = Solver(board);

            sw.WriteLine(result);

            sr.Close();
            sw.Close();
        }
    }
}
