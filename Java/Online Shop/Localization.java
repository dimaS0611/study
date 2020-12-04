import java.util.Locale;
import java.util.ResourceBundle;

public class Localization {
    private static Locale _loc = Locale.ENGLISH;
    private static ResourceBundle _res = ResourceBundle.getBundle("data", _loc);

    public Localization()
    {
        set(_loc);
    }


    static Locale get() { return _loc; }

    static void set(Locale loc)
    {
        _loc = loc;
        Locale.setDefault(_loc);
        _res = ResourceBundle.getBundle("data", loc);
    }

    static ResourceBundle getBundle() { return Localization._res; }

    static ResourceBundle bundle() { return Localization._res; }

    static String getString(String data)
    {
        String str = bundle().getString(data);
        return str;
    }

    public static final String client = "client";
    public static final String administrator = "administrator";
    public static final String order = "order";
    public static final String product = "product";
    public static final String price = "price";
    public static final String yourOrder = "yourOrder";
    public static final String payMsgTrue = "payMsgTrue";
    public static final String tnx = "tnx";
    public static final String payMsgFalse = "payMsgFalse";
    public static final String registMsg = "registMsg";
    public static final String blackListMsg = "blackListMsg";
    public static final String listProd = "listProd";
    public static final String date = "date";
}
