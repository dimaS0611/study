import java.util.ArrayList;
import java.util.Locale;
import java.util.Scanner;

public class Main {
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        Connector listProd = new Connector();
        Connector listClients = new Connector();

        Client Alex = new Client("Alex");
        Client Ksenya = new Client("Ksenya");
        Client Yura = new Client("Yura");

        Localization localization = new Localization();
        System.out.println("Choose localization:\nen - English\nru - Russian\nby - Belorussian");
        String l = in.next();
        switch (l) {
            case "en":
                Localization.set(Locale.ENGLISH);
                break;
            case "ru":
                Locale locRU = new Locale("ru", "RU");
                localization.set(locRU);
                break;
            case "by":
                Locale locBY = new Locale("by", "BY");
                Localization.set(locBY);
                break;
        }
        ArrayList<Client> ClientsDB= new ArrayList<>();
        ClientsDB.add(Alex);
        ClientsDB.add(Ksenya);
        ClientsDB.add(Yura);

        Administrator Dmitry = new Administrator("Dmitry");

        Product macBookAir = new Product("MacBook Air 13'", 1200);
        Product iPadAir = new Product("iPad Air 10.9'", 505);

        Dmitry.addProduct(macBookAir);
        Dmitry.addProduct(iPadAir);

        Alex.bookOrder(iPadAir);
        Alex.pay();

        Dmitry.createNewProduct("iPhone 6plus 64gb", 800);
        Dmitry.registerOrder(Alex);

        System.out.println("*******************************");
        Dmitry.info();
        System.out.println("*******************************");
        System.out.println(Localization.getString(Localization.listProd));
        Dmitry.productsToString();

        System.out.println("*******************************");

        Ksenya.bookOrder(macBookAir);
        Ksenya.pay();

        Dmitry.registerOrder(Ksenya);

        Ksenya.takeOrder();

        Yura.bookOrder(Dmitry.getProduct(2));
        Yura.takeOrder();

        System.out.println("*******************************");
        for (Client c: ClientsDB) {
            System.out.println(c.getDate());
            c.info();
        }

        listProd.save(Dmitry.getListOfProducts());
        listClients.save(ClientsDB);
   }
}
