package lab2;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class v21 {
    public static HashMap<Character, Integer> countOfElement(String str)
    {
        HashMap<Character, Integer> table = new HashMap<Character, Integer>();
        for (char ch : str.toCharArray())
        {
            Integer data = table.get(ch);
            if(data != null) {
                table.put(ch, data + 1);
            }
            else {
                table.put(ch, 1);
            }
        }
        return table;
    }

    public static void main(String[] args) {
        Scanner in;
        in = new Scanner(System.in);

        System.out.print("Input latter: ");
        String s = in.next();

        for (Map.Entry<Character, Integer> data : countOfElement(s).entrySet()) {
            Character ch = data.getKey();
            Integer counter = data.getValue();

            System.out.println(ch + " : " + counter);
        }

        in.close();
    }
}
