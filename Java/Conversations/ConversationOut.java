import java.io.*;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class ConversationOut {

    public static void out(int cmd, int By, String key) {

        int ans = cmd;

        try {
            if (ans == 1) {
                // Append file with new object from System.in
                // -a [file [encoding]]
                appendFile(false);
            } else if (ans == 2) {
                // Append file with compressed new object from System.in
                // -az [file [encoding]]
                appendFile(true);
            } else if (ans == 5) {
                // Prints data file
                String[][] data = printFile();
                Print.fillData(data);
            } else if (ans == 6) {
                // Prints data file sorted by key
                String[][] dataUnsorted = printFile();
                PrintSorted.fillData(dataUnsorted);

                int arg = By;
                String[] ag = new String[2];
                if (arg == 1) {
                    ag[1] = "a";
                }
                if (arg == 2) {
                    ag[1] = "i";
                }

                String[][] data = printFile(ag, false);
                PrintSorted.refillData(data);
            } else if (ans == 7) {
                // Prints data file reverse-sorted by key
                System.out.println("Enter args revers sorted by:\n\t1 - name\n\t2 - number\n\t 3 - tariff");
                int arg = By;
                String[] ag = new String[2];
                if (arg == 1) {
                    ag[1] = "a";
                }
                if (arg == 2) {
                    ag[1] = "i";
                }
                if (arg == 3) {
                    ag[1] = "n";
                }
                // if (!printFile(ag, true)) {
                System.exit(1);
            } else if (ans == 3) {
                // delete files
                deleteFile();
            } else if (ans == 4) {
                // Delete records by key
                System.out.println("Enter arg to delete by:\n\t1 - name\n\t2 - number\n\t 3 - tariff");
                int arg = By;
                String[] ag = new String[3];
                System.out.println("Enter the key: ");
                ag[2] = key;
                if (arg == 1) {
                    ag[1] = "a";
                }
                if (arg == 2) {
                    ag[1] = "i";
                }
                if (arg == 3) {
                    ag[1] = "n";
                }
                if (!deleteFile(ag)) {
                    DeleteBy.showMsgErr();
                }
                else {
                    DeleteBy.showMsg();
                }
            } else if (ans == 8) {
                // Find record(s) by key
                System.out.println("Enter arg to find by key:\n\t1 - name\n\t2 - number\n\t 3 - tariff");
                int arg = By;
                String[] ag = new String[3];
                System.out.println("Enter the key: ");
                if(key.isEmpty())
                {
                    Find.showMsgErr();
                }
                else {
                    ag[2] = key;
                    if (arg == 1) {
                        ag[1] = "a";
                    }
                    if (arg == 2) {
                        ag[1] = "i";
                    }
                    if (arg == 3) {
                        ag[1] = "n";
                    }

                    String[] data = findByKey(ag);
                    Find.fillData(data);
                }
            } else if (ans == 9) {
                // Find record(s) by key large then key
                System.out.println("Enter arg to find record large by key:\n\t1 - name\n\t2 - number\n\t 3 - tariff");
                int arg = By;
                String[] ag = new String[3];
                System.out.println("Enter the key: ");
                ag[2] = key;
                if (arg == 1) {
                    ag[1] = "a";
                }
                if (arg == 2) {
                    ag[1] = "i";
                }
                if (arg == 3) {
                    ag[1] = "n";
                }

                String[][] data = findByKey(ag, new KeyCompReverse());
                FindUp.fillData(data);
            } else if (ans == 10) {
                // Find record(s) by key less then key
                System.out.println("Enter arg to find record less by key:\n\t1 - name\n\t2 - number\n\t 3 - tariff");
                int arg = By;
                String[] ag = new String[3];
                System.out.println("Enter the key: ");
                ag[2] = key;
                if (arg == 1) {
                    ag[1] = "a";
                }
                if (arg == 2) {
                    ag[1] = "i";
                }
                if (arg == 3) {
                    ag[1] = "n";
                }
                String[][] data = findByKey(ag, new KeyComp()) ;
                FindDown.fillData(data);
            } else {
                System.err.println("Option is not realised: " + ans);
            }
        } catch (KeyNotUniqueException | IOException | ClassNotFoundException | ParseException keyNotUniqueException) {
            keyNotUniqueException.printStackTrace();
        }
    }

    static final String filename = "Conversation.dat";
    static final String filenameBak = "Conversation.~dat";
    static final String idxname = "Conversation.idx";
    static final String idxnameBak = "Conversation.~idx";

    // input file encoding:
    private static String encoding = "Cp866";
    private static PrintStream convOut = System.out;

    static Conversation readConversation() throws IOException, ParseException {
        return Conversation.read(convOut);
    }

    private static void deleteBackup() {
        new File(filenameBak).delete();
        new File(idxnameBak).delete();
    }

    static void deleteFile() {
        deleteBackup();
        new File(filename).delete();
        new File(idxname).delete();
    }

    private static void backup() {
        deleteBackup();
        new File(filename).renameTo(new File(filenameBak));
        new File(idxname).renameTo(new File(idxnameBak));
    }

    static boolean deleteFile(String[] args)
            throws ClassNotFoundException, IOException, KeyNotUniqueException {
        //-dk  {i|a|n} key      - clear data by key
        if (args.length != 3) {
            System.err.println("Invalid number of arguments");
            return false;
        }
        long[] poss = null;
        try (Index idx = Index.load(idxname)) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (pidx == null) {
                return false;
            }
            if (!pidx.contains(args[2])) {
                System.err.println("Key not found: " + args[2]);
                return false;
            }
            poss = pidx.get(args[2]);
        }
        backup();
        Arrays.sort(poss);
        try (Index idx = Index.load(idxname);
             RandomAccessFile fileBak = new RandomAccessFile(filenameBak, "rw");
             RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            boolean[] wasZipped = new boolean[]{false};
            long pos;
            while ((pos = fileBak.getFilePointer()) < fileBak.length()) {
                Conversation conv = (Conversation)
                        Buffer.readObject(fileBak, pos, wasZipped);
                if (Arrays.binarySearch(poss, pos) < 0) { // if not found in deleted
                    long ptr = Buffer.writeObject(file, conv, wasZipped[0]);
                    idx.put(conv, ptr);
                }
            }
        }
        return true;
    }

    static void appendFile(Boolean zipped)
            throws FileNotFoundException, IOException, ClassNotFoundException,
            KeyNotUniqueException, ParseException {
   //     Scanner fin = new Scanner(System.in, encoding);
     //   convOut.println("Enter conversation data*\n************************ ");
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            for (; ; ) {
                Conversation conv = readConversation();
                if (conv == null)
                    break;
                idx.test(conv);
                long pos = Buffer.writeObject(raf, conv, zipped);
                idx.put(conv, pos);
            }
        }
    }

    private static String[] printRecord(RandomAccessFile raf, long pos)
            throws ClassNotFoundException, IOException {
        boolean[] wasZipped = new boolean[]{false};
        Conversation conv = (Conversation) Buffer.readObject(raf, pos, wasZipped);
        DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
        String[] data = {conv.name, conv.number, conv.tariff, Double.toString(conv.reduction), df.format(conv.date), conv.startTalk, conv.endTalk};
        return data;
    }

    private static String[] printRecord(RandomAccessFile raf, String key,
                                    IndexBase pidx) throws ClassNotFoundException, IOException {
        long[] poss = pidx.get(key);
        String[] data = new String[7];
        for (long pos : poss) {
            data = printRecord(raf, pos);
        }
        return data;
    }

    static String[][] printFile()
            throws FileNotFoundException, IOException, ClassNotFoundException {
        long pos;
        int rec = 0;

        try (RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            String[][] data = new String[(int)raf.length()][7];
            String[] info;
            int idx = 0;
            while ((pos = raf.getFilePointer()) < raf.length()) {
                info = printRecord(raf, pos);
                data[idx] = info;
                idx++;
            }
            System.out.flush();
            return data;
        }
    }

    private static IndexBase indexByArg(String arg, Index idx) {
        if (arg == "i") {
            return idx.number;
        }
        if (arg == "a") {
            return idx.name;
        }
        if (arg == "n") {
            return idx.tariff;
        }

        System.err.println("Invalid index specified: " + arg);
        return null;
    }

    static String[][] printFile(String[] args, boolean reverse)
            throws ClassNotFoundException, IOException {

        try (Index indx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], indx);
            String[] keys =
                    pidx.getKeys(reverse ? new KeyCompReverse() : new KeyComp());
            String[][] data = new String[(int)keys.length][7];
            int idx =0;
            for (String key : keys) {
                data[idx] = printRecord(raf, key, pidx);
                idx++;
            }
            return data;
        }
    }

    static String[] findByKey(String[] args)
            throws ClassNotFoundException, IOException {
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], idx);
            String[] data = new String[7];
            if(printRecord(raf, args[2], pidx) == null)
            {
                Find.showMsgErr();
                String[] errData = {"","","","","","",""};
                return errData;
            }
            else
                return printRecord(raf,args[2],pidx);
        }
    }

    static String[][] findByKey(String[] args, Comparator<String> comp)
            throws ClassNotFoundException, IOException {
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], idx);
            String[] keys = pidx.getKeys(comp);
            String[][] data = new String[keys.length][7];
            for (int i = 0; i < keys.length; i++) {
                String key = keys[i];
                if (key.equals(args[2])) {
                    break;
                }
               data[i] = printRecord(raf, key, pidx);
            }
            return data;
        }
    }
}