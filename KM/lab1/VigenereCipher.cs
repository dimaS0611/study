using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1_1
{
    class VigenereCipher : ICipher
    {
        string _alphabet = "abcdefghijklmnopqrstuvwxyz";

        string FillCode(string password, int textLength)
        {
            while(password.Length <= textLength)
            {
                password += password;
            }

            return password.Substring(0, textLength);
        }

        public string Decrypt(string text, string key)
        {
            text = text.ToLower();

            var fillCode = FillCode(key, text.Length);
            var decText = "";

            int decLetterIdx;

            for (int i = 0; i < text.Length; ++i)
            {
                var letterIdx = _alphabet.IndexOf(text[i]);
                var keyIdx = fillCode.IndexOf(fillCode[i]);

                decLetterIdx = letterIdx - keyIdx;

                if (decLetterIdx < 0)
                {
                    decLetterIdx = letterIdx + _alphabet.Length - keyIdx;
                }

                decText += _alphabet[decLetterIdx];
            }

            return decText;
        }

        public string Encrypt(string text, string key)
        {
            text = text.ToLower();

            var fillCode = FillCode(key, text.Length);
            var encText = "";

            int encLetterIdx;

            for (int i = 0; i < text.Length; ++i)
            {
                var letterIdx = _alphabet.IndexOf(text[i]);
                var keyIdx = fillCode.IndexOf(fillCode[i]);

                encLetterIdx = letterIdx + keyIdx;
                
                if(encLetterIdx >= _alphabet.Length)
                {
                    encLetterIdx = encLetterIdx - _alphabet.Length;
                }

                encText += _alphabet[encLetterIdx];
            }

            return encText;
        }

        public void CreateKey(string key)
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
