using System;
using System.IO;
using System.Collections.Generic;

namespace @string
{
    class Program
    {
        public static int oneByOne(List<char> str)
        {
            Dictionary<char, int> charMap = new Dictionary<char, int>();
            int singleCounter = 0;

            for(int  i =0; i < str.Count; ++i)
            {
                char ch = str[i];

                if(charMap.ContainsKey(ch))
                {
                    charMap[ch]++;
                    continue;
                }
                charMap.Add(ch, 1);
            }

            for(int i = 0; i < str.Count; ++i)
            {
                if(charMap[str[i]] == 1)
                {
                    singleCounter++;
                    str.RemoveAt(i);
                    i--;
                }
            }

            return singleCounter;
        }

        public static void inRow(List<char> str)
        {
            for (int i = 0; i + 1 < str.Count; ++i)
            {
                if (str[i] == str[i + 1])
                    str.RemoveAt(i);
            }
        }

        public static int solveMtx(List<char> str)
        {
            int size = str.Count;
            int[,] mtx = new int[size, size];

            for (int i = 0; i < size; i++)
                mtx[i, i] = 1;


            int st = 0;
            int kl1 = 1;
            int cl = 0;
            int vt = 0;
            bool flg = true;
            int min = 0;

            for (int i = 1; i <= size - 1; i++)
            {
                for (int kl = kl1; kl <= size - 1; kl++)
                {
                    if (str[st] != str[kl])
                    {

                        mtx[st, kl] = Math.Min(mtx[st, kl - 1], mtx[st + 1, kl]) + 1;

                        for (int line = st + 1; line <= kl; line++)
                        {
                            if (str[st] == str[line])
                            {
                                if (line != kl)
                                {
                                    cl = mtx[st + 1, line - 1] + mtx[line, kl];
                                    if (flg)
                                    {
                                        min = cl;
                                        flg = false;
                                    }
                                    if (cl < min)
                                        min = cl;
                                }
                            }
                        }

                        flg = true;

                        if (min > 0)
                            mtx[st, kl] = Math.Min(mtx[st, kl], min);
                    }
                    else
                    {
                        mtx[st, kl] = mtx[st + 1, kl - 1] + 1;

                        for (int line = st + 1; line <= kl; line++)
                        {
                            if (str[st] == str[line])
                            {
                                if (line != kl)
                                {
                                    vt = mtx[st + 1, line - 1] + mtx[line, kl];
                                    if (flg)
                                    {
                                        min = vt;
                                        flg = false;
                                    }
                                    if (vt < min)
                                    {
                                        min = vt;
                                    }
                                }
                            }
                        }

                        flg = true;

                        if (min > 0)
                            mtx[st, kl] = Math.Min(mtx[st, kl], min);

                    }
                    vt = 0;
                    st++;
                    flg = true;
                    min = 0;
                }
                st = 0;
                kl1++;
            }

            // верхний угол верхнего треугольника  - ответ
            return mtx[0, size - 1];
        }

        static void Main()
        {
            StreamReader sr = new StreamReader("input.txt");
            StreamWriter sw = new StreamWriter("output.txt");
            
            string input = sr.ReadLine();
            int strLen = input.Length;

            int counter = 0;

            List<char> line = new List<char>();
            
            for (int i = 0; i < strLen; i++)
            {
                line.Add(input[i]);
            }
            
            counter = oneByOne(line);
            inRow(line);


            if (line.Count != 0)
            {
                int resMtx = solveMtx(line);
                sw.WriteLine(resMtx + counter);
            }
            else
                sw.Write(counter);

            sw.Close();
        }
    }
}