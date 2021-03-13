using System.IO;
using System;
namespace lab1_1
{    
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader sr = new StreamReader("in.txt");
            StreamWriter sw = new StreamWriter("out.txt");

            string input = sr.ReadToEnd();
            int option = 0;

            Console.WriteLine("Choose chipher : \nSubstring - 1:\nVigenere - 2:\nAffine - 2:\nHill - 4:\n");
            option = int.Parse(Console.ReadLine());

            switch (option)
            {
                case 1:
                    {
                        SubstCipher subst = new SubstCipher();

                        int op = 0;
                        Console.WriteLine("Encript -'0'\n Decrypt - '1'");
                        op = int.Parse(Console.ReadLine());
                        if(op == 0)
                        {
                            subst.CreateKey();

                            string key = subst.ReadKey();
                            sw.Write(subst.Encrypt(input, key));
                        }
                        if(op == 1)
                        {
                            string key = subst.ReadKey();
                            sw.Write(subst.Decrypt(input, key));
                        }
                        else
                        {
                            Console.WriteLine("Invalid option!");
                        }
                        

                        break;
                    }
                case 2:
                    {
                        VigenereCipher vigenere = new VigenereCipher();

                        int op = 0;
                        Console.WriteLine("Encript -'0'\n Decrypt - '1'");
                        op = int.Parse(Console.ReadLine());

                        if (op == 0)
                        {
                            vigenere.CreateKey("abc"); 

                            string key = vigenere.ReadKey();
                            sw.Write(vigenere.Encrypt(input, key));
                        }
                        if (op == 1)
                        {
                            string key = vigenere.ReadKey();
                            sw.Write(vigenere.Decrypt(input, key));
                        }
                        else
                        {
                            Console.WriteLine("Invalid option!");
                        }
                        
                        break;
                    }
                case 3:
                    {
                        AffineCipher affine = new AffineCipher();

                        int op = 0;
                        Console.WriteLine("Encript -'0'\n Decrypt - '1'");
                        op = int.Parse(Console.ReadLine());
                        
                        if (op == 0)
                        {
                            affine.CreateKey();
                            int key = int.Parse(affine.ReadKey());

                            sw.WriteLine(affine.Encrypt(input, key, 2));
                        }
                        if (op == 1)
                        {
                            int key = int.Parse(affine.ReadKey());
                            sw.WriteLine(affine.Decrypt(input, key, 2));
                        }
                        else
                        {
                            Console.WriteLine("Invalid option!");
                        }
                        
                        break;
                    }
                case 4:
                    {
                        HillCipher hill = new HillCipher();

                        int op = 0;
                        Console.WriteLine("Encript -'0'\n Decrypt - '1'");
                        op = int.Parse(Console.ReadLine());
                        
                        if (op == 0)
                        {
                            hill.CreateKey("gybnqkurp");

                            string key = hill.ReadKey();

                            sw.WriteLine(hill.Encrypt(input, key));
                            break;
                        }
                        if (op == 1)
                        {
                            string key = hill.ReadKey();
                            sw.WriteLine(hill.Decrypt(input, key));
                            break;
                        }
                        else
                        {
                            Console.WriteLine("Invalid option!");
                            break;
                        }                       
                    }
                default:
                    Console.WriteLine("Invalid option");
                    break;

            }

            sr.Close();
            sw.Close();
        }
    }
}
