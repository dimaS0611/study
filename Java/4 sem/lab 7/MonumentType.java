import javafx.beans.property.SimpleStringProperty;

public class MonumentType {
    private SimpleStringProperty type;
    private SimpleStringProperty id;
    private SimpleStringProperty description;

    MonumentType(String type, String description) {
        this.type = new SimpleStringProperty(type);
        this.description = new SimpleStringProperty(description);
    }

    SimpleStringProperty getFieldBySQL(String sqlName) {
        SimpleStringProperty res;
        switch (sqlName) {
            case "type":
                res = this.type;
                break;
            case "id":
                res = this.id;
                break;
            case "description":
                res = this.description;
                break;
            default:
                res = null;
        }
        return res;
    }

    public String getType() {
        return type.get();
    }

    public SimpleStringProperty typeProperty() {
        return type;
    }

    public String getId() {
        return id.get();
    }

    public SimpleStringProperty idProperty() {
        return id;
    }

    public String getDescription() {
        return description.get();
    }

    public SimpleStringProperty descriptionProperty() {
        return description;
    }
}
