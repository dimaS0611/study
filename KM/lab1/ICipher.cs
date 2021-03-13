namespace lab1_1
{
    interface ICipher
    {
        string Encrypt(string text, string key);
        string Decrypt(string text, string key);
    }
}
