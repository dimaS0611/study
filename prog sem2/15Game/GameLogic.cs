using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game15
{
    class GameLogic
    {
        int size;
        int[,] map;
        int spaceX;
        int spaceY;
        static Random rand = new Random();

        public GameLogic(int size)
        {
            size = Math.Max(2, size);
            size = Math.Min(size, 5);
            this.size = size;
            map = new int[size, size];
        }
        
        public void Start()
        {
            for (int x = 0; x < size; x++)
                for (int y = 0; y < size; y++)
                    map[x, y] = CordsToPosition(x, y) + 1;

            spaceX = size - 1;
            spaceY = size - 1;

            map[spaceX, spaceY] = 0;
        }

        public void Shift(int pos)
        {
            int x, y;
           
            PositionToCords(pos, out x, out y);

            if (Math.Abs(spaceX - x) + Math.Abs(spaceY - y) != 1)
                return;

            map[spaceX, spaceY] = map[x, y];
            map[x, y] = 0;

            spaceX = x;
            spaceY = y;
        }

        public void ShiftRandom()
        {

            //Shift(rand.Next(object, size * size));
            int randNum = rand.Next(0, 4);
            int x = spaceX;
            int y = spaceY;
            
            switch (randNum)
            {
                case 0: x--; break;
                case 1: x++; break;
                case 2: y--; break;
                case 3: y++; break;
            }

            Shift(CordsToPosition(x, y));
        }

        public bool CheckNum()
        {
            if (!(spaceX == size - 1 && spaceY == size - 1))
                return false;
            
            for (int x = 0; x < size; x++)
                for (int y = 0; y < size; y++)
                {
                    if (!(x == size - 1 && y == size - 1))
                        if (map[x, y] != CordsToPosition(x, y) + 1)
                        return false;
                }
            return true;
        }

        public int GetNum(int pos)
        {
            int x, y;
            PositionToCords(pos, out x, out y);
            
            if (x < 0 || x >= size)
                return 0;
            if (y < 0 || y >= size)
                return 0;

            return map[x, y];
        }

        private int CordsToPosition (int x, int y)
        {
            if (x < 0)
                x = 0;
            if (x > size - 1)
                x = size - 1;
            if (y < 0)
                y = 0;
            if (y > size - 1)
                y = size - 1;
            return y * size + x;
        }

        private void PositionToCords(int pos, out int x, out int y)
        {
            if (pos < 0)
                pos = 0;
            if (pos > size * size - 1)
                pos = size * size - 1;
            
            x = pos % size;
            y = pos / size;
        }

    }
}
