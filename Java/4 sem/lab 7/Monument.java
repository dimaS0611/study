import javafx.beans.property.SimpleStringProperty;

public class Monument {
    private SimpleStringProperty name;
    private SimpleStringProperty type;
    private SimpleStringProperty number;

     Monument(String type, String name,
          String number) throws Exception {

         if (type == null || name.isEmpty()) {
             throw new Exception("Field 'type' is empty");
         }
         if (name == null || name.isEmpty()) {
             throw new Exception("Field 'name' is empty");
         }
         if (number == null || number.isEmpty()) {
             throw new Exception("Field 'number' is empty");
         }

         this.name = new SimpleStringProperty(name);
         this.type = new SimpleStringProperty(type);
         this.number = new SimpleStringProperty(number);
     }

    SimpleStringProperty getFieldBySQL(String sqlName) {
        SimpleStringProperty res;
        switch (sqlName) {
            case "name":
                res = this.name;
                break;
            case "type":
                res = this.type;
                break;
            case "number":
                res = this.number;
                break;
            default:
                res = null;
        }
        return res;
    }

    public String getName() {
        return name.get();
    }

    public SimpleStringProperty nameProperty() {
        return name;
    }

    public String getNumber() {
        return number.get();
    }

    public SimpleStringProperty numberProperty() {
        return number;
    }

    public String getType() {
        return type.get();
    }

    public SimpleStringProperty typeProperty() {
        return type;
    }
}

