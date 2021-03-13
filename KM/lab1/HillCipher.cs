using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1_1
{
    class HillCipher : ICipher
    {
        string _alphabet = "abcdefghijklmnopqrstuvwxyz";

        public string Decrypt(string text, string key)
        {
            string decText = "";
            int textLen = text.Length;
            List<double> encIdx = new List<double>();
            MatrixD keyMtx = KeyToMatrix(key);
            int blockSize = (int)Math.Sqrt(key.Length);

            if (text.Length % blockSize != 0)
            {
                while (text.Length % blockSize != 0)
                {
                    text += "a";
                }
            }

            int blockCount = (int)text.Length / blockSize;

            MatrixD invertKeyMtx = new MatrixD(blockSize, blockSize);
            if (blockSize == 2)
            {
                 invertKeyMtx = keyMtx.InversM2();
            }
            if(blockSize == 3)
            {
                invertKeyMtx = keyMtx.InversM3();
            }
            for (int i = 0; i < blockCount; ++i)
            {
                for (int j = 0; j < blockSize; ++j)
                {
                    double sum = 0;
                    for (int k = 0; k < blockSize; ++k)
                    {
                        sum += _alphabet.IndexOf(text[i * blockSize + k]) * invertKeyMtx.M[j, k];
                    }
                    encIdx.Add(sum);
                }

            }

            foreach (var i in encIdx)
            {
                decText += (char)(Convert.ToChar(Math.Abs((int)i % 26)) + 'a');
            }

            return decText.Substring(0, textLen);
        }

        public string Encrypt(string text, string key)
        {
            string encText = "";
            int textLen = text.Length;
            List<int> encIdx = new List<int>();
            MatrixD keyMtx = KeyToMatrix(key);

            int blockSize = (int)Math.Sqrt(key.Length);

            if (text.Length % blockSize != 0)
            {
                while (text.Length % blockSize != 0)
                {
                    text += "a";
                }
            }

            int blockCount = (int)text.Length / blockSize;

            for (int i = 0; i < blockCount; ++i)
            {
                for (int j = 0; j < blockSize; ++j)
                {
                    int sum = 0;
                    for (int k = 0; k < blockSize; ++k)
                    {
                        sum += _alphabet.IndexOf(text[i * blockSize + k]) * (int)keyMtx.M[j, k];
                    }
                    encIdx.Add(sum);
                }

            }

            foreach (var i in encIdx)
            {
                encText += (char)(Convert.ToChar(i % 26) + 'a');  //_alphabet[i % 26];
            }

            return encText.Substring(0, textLen);
        }

        public MatrixD KeyToMatrix(string key)
        {
            int mtxCount = (int)Math.Sqrt(key.Length);
            MatrixD mtx = new MatrixD(mtxCount, mtxCount);
            
            for (int i = 0; i < mtxCount; ++i)
            {
                for (int j = 0; j < mtxCount; ++j)
                {
                    mtx.M[i, j] = _alphabet.IndexOf(key[i * mtxCount + j]);
                }
            }

            return mtx;
        }

        public void CreateKey(string key)
        {
            double checkKey = Math.Sqrt(key.Length);
            
            if(Math.Pow(checkKey,2) == key.Length)
            {
                using (var sw = new StreamWriter("key.txt"))
                {
                    sw.Write(key);
                }
            }
            else
            {
                Console.WriteLine("Key length must be the square of some number");
            }
        }

        public string ReadKey()
        {
            using (var sr = new StreamReader("key.txt"))
            {
                return sr.ReadToEnd();
            }
        }
    }
}
