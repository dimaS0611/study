import java.io.Serializable;
import java.util.Date;

public class Product implements Serializable {
    private static final long serialVersionUID = 2L;
    private String _NameOfProduct;
    private double _Price;
    private Date _Date;

    public Product()
    {
        _Date = new Date();
    }

    public Product(String name, double price)
    {
        _Date = new Date();
        this._NameOfProduct = name;
        this._Price = price;
    }

    public String getName() { return _NameOfProduct; }
    public double getPrice() { return _Price; }
    public void setName(String name) { this._NameOfProduct = name; }
    public void setPrice(double price) { this._Price = price; }
    public Date getDate() { return  _Date;}

    @Override
    public String toString()
    {
        return Localization.getString(Localization.product) + " : " + getName() +  " "+
            Localization.getString(Localization.price) + " : " + getPrice();
    }

    public String info()
    {
        return (Localization.getString(Localization.product) + " : "  + getName() + " ");
    }

}
