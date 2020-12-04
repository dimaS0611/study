import java.awt.dnd.DropTarget;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;

    public class Administrator implements Serializable {
    private static final long serialVersionUID = 2L;
    private ArrayList<Product> _ProductsList = new ArrayList<>();
    private ArrayList<Client> _BlackList = new ArrayList<>();
    private String _Name;
    private Date _Date;

    Administrator(String name)
    {
        _Date = new Date();
        _Name = name;
    }
    public void registerOrder(Client client)
    {
        if(client.getOrder().isPaid() == true)
            client.getOrder().setRegistered(true);
        else if (client.getOrder().isPaid() == false) {
            _BlackList.add(client);
            blacklistIn(client);
        }
    }

    public void blacklistIn(Client client) { client.inBlackList(true);  }

    public void createNewProduct(String name, double price)
    {
        _ProductsList.add(new Product(name, price));
    }

    public void addProduct(Product product)
    {
        this._ProductsList.add(product);
    }

    public ArrayList<Product> getListOfProducts() { return this._ProductsList; }
    public Product getProduct(int indx) {  return this._ProductsList.get(indx);}
    public Date getDate() { return _Date; }

    public void productsToString()
    {
        for (Product prod: _ProductsList) {
            System.out.println(prod.getDate());
            System.out.println(prod.toString());
        }
    }

    public void info()
    {
        System.out.println(Localization.getString(Localization.administrator) + " " +_Name);
    }

}
