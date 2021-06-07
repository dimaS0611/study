import java.io.IOException;
import java.lang.reflect.Array;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

public class Main {
    final static int M = 3;
    public static byte[] _text;
    public static byte[] _keys = new byte[8];
    static String FileNameKey = "key.txt";

    public static String FileNameText = "Криптографические методы 6. Блочные шифры.pdf";
    public static String FileNameCipher = "1Криптографические методы 6. Блочные шифры.pdf";

    public static String FileNameDText = "1Криптографические методы 6. Блочные шифры.pdf";
    public static String FileNameDCipher = "2Криптографические методы 6. Блочные шифры.pdf";

    public static void Main() throws IOException {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Choose option");
        System.out.println("1 - Encrypt\n2 - Decrypt");
        var choose = scanner.next().equals("1");
        Path path = Paths.get("Криптографические методы 6. Блочные шифры.pdf");
        _text = Files.readAllBytes(path);
        if (_text != null && _text.length % 2 != 0)
        {
            Array.Resize(ref _text, _text.Length + 1);
            _text[^1] = (byte)'_';
        }

        var theta = Files.readAllBytes(FileNameKey);
        for (var i = 0; i < 8; i++)
            _keys[i] = theta[i % 4];

        if (choose)
        {
            for (var i = 0; i < 8; i++)
            {
                EncryptOneRound(i);
                System.out.println(i);
                SerialTest(_text);
            }
        }
        else
        {
            for (var i = 7; i >= 0; i--)
            {
                DecryptOneRound(i);
                System.out.println(i);
            }
        }

        Files.write(Path.of(choose ? FileNameCipher : FileNameDCipher), _text);
    }

    private static void SerialTest(IEnumerable<byte> bytes)
    {
        var text = String.Join("", bytes.Select(x => Convert.ToString(x, 2)));
        var psi1 = GetPsi(text, M - 2);
        var psi2 = GetPsi(text + "0", M - 1);
        var psi3 = GetPsi(text + "00", M);
        var deltaPsi = psi3 - psi2;
        var deltaSquarePsi = psi3 - 2 * psi2 + psi1;
        var pValue1 = SpecialFunction.igamc(Math.pow(2, M - 2), deltaPsi / 2);
        var pValue2 = SpecialFunction.igamc(Math.pow(2, M - 3), deltaSquarePsi / 2);
        System.out.println(text);
        System.out.println("pValue1 = {pValue1} pValue2 = {pValue2}");
        System.out.println("Test is " + (pValue1 > 0.01 && pValue2 > 0.01 ? "Passed" : "Failed"));
    }

    private static double GetPsi(String text, int m)
    {
        var sum = 0.0;

        var n = text.length - m + 1;
        for (var i = 0; i < Math.pow(2, m); ++i)
        {
            var nextBin = Convert.ToString(i, 2).PadLeft(m, '0');
            var count = new Regex($"(?={nextBin})").Matches(text).Count;
            sum += count * count;
        }

        return Math.pow(2, m) * sum / n - n;
    }

    private static void EncryptOneRound(int keyNumber)
    {
        for (var i = 0; i < _text.length; i++)
        {
            var (x1, x2) = (_text[i++], _text[i]);
            var tmp = x2 ^ _keys[keyNumber];
            var (s1, s2) = (SBox1(tmp >> 4 & 0xF) << 4, SBox2(tmp & 0xF));
            tmp = s1 | s2;
            tmp = CycleShiftLeft(tmp, 3);
            tmp ^= x1;
            (_text[i - 1], _text[i]) = (x2, (byte) tmp);
        }
    }

    private static void DecryptOneRound(int keyNumber)
    {
        for (var i = 0; i < _text.length; i++)
        {
            byte (x1, x2) = (_text[i++], _text[i]);
            byte tmp = x1 ^ _keys[keyNumber];
            byte (s1, s2) = (SBox1(tmp >> 4 & 0xF) << 4, SBox2(tmp & 0xF));
            tmp = s1 | s2;
            tmp = CycleShiftLeft(tmp, 3);
            tmp ^= x2;
            (_text[i - 1], _text[i]) = ((byte) tmp, x1);
        }
    }

    private static int CycleShiftLeft(int a, int s) { return ((a << s) & 0xFF) | (a >> 8 - s); }
    private static int SBox1(int x) { return (int) (Math.pow(3, x) % 17 + 2) % 16; }
    private static int SBox2(int x) { return  (int) (Math.pow(5, x) % 17 + 7) % 16; }
}
}
