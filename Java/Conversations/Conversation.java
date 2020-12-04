import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class Conversation implements Serializable {
    // class release version:
    private static final long serialVersionUID = 1L;
    // areas with prompts:
    String name;
    static final String _name = "Name";
    String number;
    static final String _number = "Number";
    String tariff;
    static final String _tariff = "Tariff";
    Date date;
    static final String _date = "Date";
    double reduction;
    static final String _reduction = "Reduction";
    String startTalk;
    static final String _startTalk = "Start talk";
    String endTalk;
    static final String _endTalk = "End talk";

    // validation methods:
    static Boolean validNumber(String str) {
        int i = 0, ndig = 0;
        for (; i < str.length(); i++) {
            char ch = str.charAt(i);
            if (Character.isDigit(ch)) {
                ndig++;
                continue;
            }
            if (ch != '-') {
                return false;
            }
        }
        return (ndig == 7 || ndig == 10 || ndig == 11 || ndig == 9);
    }

    static Date curDate = new Date();

    public static Date get_curDate() {
        return curDate;
    }

    static Boolean validDate(Date date) {
        final boolean b = (date.after(date = new Date("10/03/1876"))) && (date.before(get_curDate())) || (date == get_curDate());
        return b;
    }

    public static Boolean nextRead(Scanner fin, PrintStream out) {
        return nextRead(_number, fin, out);
    }

    static Boolean nextRead(final String prompt, Scanner fin, PrintStream out) {
        out.print(prompt);
        out.print(": ");
        return fin.hasNextLine();
    }

    public static final String authorDel = ",";

    public static Conversation read(PrintStream out)
            throws IOException, ParseException {
        String str;
        Conversation conv = new Conversation();
        conv.number = AppendData.tfNumber.getText();
        if (!Conversation.validNumber(conv.number)) {
            AppendData.err();
        }
        conv.name = AppendData.tfName.getText();
        if(conv.name == null)
            AppendData.err();

        conv.tariff = AppendData.tfTariff.getText();

        if(conv.tariff == null)
            AppendData.err();

        String date = AppendData.tfDate.getText();
        conv.date = new SimpleDateFormat("dd/MM/yyyy").parse(date);
        if (!Conversation.validDate(conv.date)) {
            AppendData.err();
        }

        conv.startTalk = AppendData.tfStart.getText();
        if (conv.startTalk == null)
            AppendData.err();

        conv.endTalk = AppendData.tfEnd.getText();
        if (conv.endTalk == null)
            AppendData.err();

        str = AppendData.tfReduction.getText();
        conv.reduction = Double.parseDouble(str);

        return conv;
    }

    public Conversation() {
    }

    public static final String areaDel = "\n";

    public String toString() {
        return number + areaDel +
                name + areaDel +
                tariff + areaDel +
                reduction + areaDel +
                date + areaDel +
                startTalk + areaDel +
                endTalk;
    }
}