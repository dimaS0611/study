using System;

namespace BinarySearch
{
    class Program
    {
        static int BinarySearch(int[] array, int searchedEl, out int upperIndx)
        {
            int first = 0;
            int last = array.Length - 1;
            int i = 0;
            
            while(first <= last)
            {
                int middle = (last + first) / 2;
                if(searchedEl == array[i])
                {
                    upperIndx = first;
                    return i;
                }
                if (searchedEl < array[middle])
                {
                    last = middle - 1;
                }
                else if(searchedEl > array[middle])
                {
                    first = middle + 1;
                }
                i++;
            }

            upperIndx = first;
            return -1;

        }

        static void Main(string[] args)
        {
            int sizeOFArr = Convert.ToInt32(Console.ReadLine());
            var s = Console.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);
            var array = new int[sizeOFArr];
            
            for(int i = 0; i < sizeOFArr; ++i)
            {
                array[i] = Convert.ToInt32(s[i]);
            }

            Array.Sort(array);

            int sizeOfArrFind = Convert.ToInt32(Console.ReadLine());
            var searchEl = new int[sizeOfArrFind];
            var el = Console.ReadLine().Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);
            
            for (int i = 0; i < sizeOfArrFind; ++i)
            {
                searchEl[i] = Convert.ToInt32(el[i]);
            }

            int res1 = 0;
            int res2 = 0;
            int res3 = 0;

            for (int i = 0; i < searchEl.Length; ++i)
            {
                int upperIndx;
                var searchRes = BinarySearch(array, searchEl[i],out upperIndx);

                res1 = 0;
                res2 = 0;
                res3 = 0;

                if (searchRes >= 0)
                {
                    res1 = 1;
                    res2 = searchRes;
                    res3 = upperIndx + 1;
                }
                else
                {
                    res1 = 0;
                    res3 = upperIndx;

                    if(searchEl[i] < array[0])
                    {
                        res2 = 0;
                    }
                    else if(searchEl[i] > array[array.Length - 1])
                    {
                        res2 = upperIndx;
                    }
                    else
                    {
                        res2 = upperIndx;
                    }
                }
                
                Console.Write(res1 + " " + res2 + " " + res3 + "\n");
            }
        }
    }
}
