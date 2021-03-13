using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1_1
{
    class AffineCipher
    {
        string _alphabet = "abcdefghijklmnopqrstuvwxyz";
        int[] possibleKeys = { 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25 };
        public string Decrypt(string text, int k1, int k2)
        {
            if (!checkKey(k1))
                return "invalid key";

            int multpair = getMultPair(k1);
            string decText = "";

            foreach(var ch in text)
            {
                char c = Convert.ToChar(ch);
                decText += (char)((((Convert.ToInt32(ch) + 'A' - k2) * multpair) % 26) + 'A') ;
            }

            return decText.ToLower();
        }

        public string Encrypt(string text, int k1, int k2)
        {
            if (!checkKey(k1))
                return "invalid key";
            text = text.ToUpper();
            string enctext = "";

            foreach(var ch in text)
            {
                char c = Convert.ToChar(ch);
                enctext += (char)((((k1 * (Convert.ToInt32(c) - 'A')) + k2) % 26) + 'A');
            }

            return enctext;
        }

        public Dictionary<int,int> MultiplierPairs(int mod)
        {
            Dictionary<int, int> pairs = new Dictionary<int, int>();
            for(int i = 0; i < mod; ++i)
            {
                for(int j = 0; j < mod; ++j)
                {
                    if((i*j) % mod ==1)
                    {
                        pairs.Add(i, j);
                    }
                }
            }

            return pairs;
        }

        public int getMultPair(int key)
        {
            Dictionary<int, int> pairs = MultiplierPairs(26);
            return pairs[key];
        }

        public void printPossibleKeys()
        {
            Console.WriteLine("Possible keys:\n");
            foreach(var ch in possibleKeys)
            {
                Console.WriteLine(ch);
            }
        }

        public bool checkKey(int key)
        {
            if (possibleKeys.Contains(key))
                return true;

            return false;
        }
        public void CreateKey()
        {
            Random rnd = new Random();
            int pos = rnd.Next(0, 11); 
         
            using (var sw = new StreamWriter("key.txt"))
            {
                sw.Write(possibleKeys[pos]);
            }
        }
        public void CreateKey(int key)
        { 
            using (var sw = new StreamWriter("key.txt"))
            {
                sw.Write(key);
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
