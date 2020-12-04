import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;

public class Client implements Serializable {
    private static final long serialVersionUID = 2L;
    private Order _Order = new Order();
    private boolean _InBlackList = false;
    private String _Name;
    private Date _Date;

    Client(String name)
    {
        _Date = new Date();
        this._Name = name;
    }

    public void bookOrder(Product product) { this._Order.addToOrder(product); }
    public void bookGroupOrder(ArrayList<Product> order) { this._Order.addGroupOFProducts(order); }

    public Date getDate() { return _Date; }
    public String getName() {  return this._Name; }
    public Order getOrder() { return _Order; }
    public void inBlackList(boolean ans) { this._InBlackList = ans; }
    public void pay()
    {
        if(_Order.isPaid() == true)
            System.out.println(Localization.getString(Localization.payMsgTrue));
        else
            _Order.setPaid(true);
    }

    public void showOrder()
    {
        _Order.showOrder();
    }

    public void takeOrder()
    {
        if(_Order.isPaid() == true)
            System.out.println(Localization.getString(Localization.tnx) + " " + getName());
        else  if(_Order.isPaid() == false) {
            System.out.println(Localization.getString(Localization.payMsgFalse) + " " + getName());
            inBlackList(true);
        }if(_Order.isRegistered() == false)
            System.out.println(Localization.getString(Localization.registMsg) + " "+ getName());
    }

    public void info()
    {
        String blk = "******";
        if(_InBlackList) {
            blk = Localization.getString(Localization.blackListMsg);
        }
         System.out.println(getName());
         showOrder();
         System.out.println(blk);
    }

}
