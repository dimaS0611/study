import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;

public class Order implements Serializable {
    private ArrayList<Product> _OrderList = new ArrayList<>();
    private boolean _Registered = false;
    private boolean _Paid = false;
    private Date _Date;

    Order()
    {
        _Date = new Date();
    }
    public void addToOrder(Product product)
    {
        _OrderList.add(product);
    }

    public void addGroupOFProducts(ArrayList<Product> products)
    {
        this._OrderList = products;
    }

    public boolean isPaid()
    {
        return this._Paid;
    }

    public void setPaid(boolean answer)
    {
        this._Paid = answer;
    }

    public boolean isRegistered()
    {
        return _Registered;
    }

    public void setRegistered(boolean answer)
    {
        this._Registered = answer;
    }

    public Date getDate() { return _Date; }

    public void showOrder()
    {
        System.out.println(Localization.getString(Localization.yourOrder));
        for (Product prod : _OrderList) {
            System.out.println(prod.info());
        }
    }


}
