using System;
using System.Collections.Generic;
using System.IO;

namespace lab4
{
    class Program
    {
        private const string FileNameText = "text.txt";

        public static void Main()
        {
            // преобразование данных в битвоый вид
            var text = new List<byte>(File.ReadAllBytes(FileNameText));
            WriteFile(Hash(text));
        }

        private static byte[] Hash(List<byte> text)
        {
            for (var i = 0; i < text.Count % 4; i++)
                text.Add(0);
            
            var length = text.Count;
            for (int i = 0; i < 4; ++i)
            {
                text.Add((byte) length);
                length >>= 8;
            }
            
            var y = new byte[] {100, 134, 78, 9};
            for (var i = 0; i < text.Count; i += 4)
            {
                var x = new[] {text[i], text[i + 1], text[i + 2], text[i + 3]};
                y = sigma(x, y);
            }

            return y;
        }

        private static byte[] sigma(byte[] x, byte[] y) => Xor(F(y, x), y);

        private static byte[] F(byte[] input, byte[] key)
        {
            var output = new byte[input.Length];
            input.CopyTo(output, 0);
            for (var j = 0; j < 8; j++)
            for (var i = 0; i < input.Length; i += 2)
            {
                var (x1, x2) = (output[i], output[i + 1]);
                var tmp = x2 ^ key[j % 4];
                var (s1, s2) = (SBox1(tmp >> 4 & 0xF) << 4, SBox2(tmp & 0xF));
                tmp = s1 | s2;
                tmp = CycleShiftLeft(tmp, 3);
                tmp ^= x1;
                (output[i], output[i + 1]) = (x2, (byte) tmp);
            }

            return output;
        }

        private static int CycleShiftLeft(int a, int s) => ((a << s) & 0xFF) | (a >> 8 - s);
        private static int SBox1(int x) => (int) (Math.Pow(3, x) % 17 + 2) % 16;
        private static int SBox2(int x) => (int) (Math.Pow(5, x) % 17 + 7) % 16;

        private static byte[] Xor(byte[] a, byte[] b)
        {
            var output = new byte[a.Length];
            for (var i = 0; i < a.Length; ++i)
                output[i] = (byte) (a[i] ^ b[i]);
            return output;
        }

        private static void WriteFile(byte[] hash)
        {
            using var writer = new StreamWriter("Hash.txt", true);
            foreach (var b in hash)
                writer.Write(BitFormat(b));
            writer.Write("\n");
        }

        private static string BitFormat(byte b) => $"{Convert.ToString(b, 2).PadLeft(8, '0')} ";
    }
}
