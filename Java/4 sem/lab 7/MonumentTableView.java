import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.geometry.Insets;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.scene.control.Alert;

import java.sql.PreparedStatement;
import java.util.Optional;

public class MonumentTableView extends Application
{
    private TableView<Monument> MonumentTable = new TableView<>();
    private TableView<MonumentType> typesTable = new TableView<>();

    private final HBox addBox = new HBox(15);

    private int preferNameColumnWidth = 200;
    private int preferAgeColumnWidth = 300;
    private int prefertypeColumnWidth = 150;
    private int preferingTimeColumnWidth = 100;
    private int preferamountColumnWidth = 200;

    @Override
    public void start(Stage primaryStage) throws Exception {

        DataBase.connectionDB();
        DataBase.createDB();

        Scene scene = new Scene(new Group());
        primaryStage.setTitle("Monuments table");

        createMonumentsTable();
        createatypesTable();
        createAddBox();

        VBox allBox = new VBox(10);
        allBox.setPadding(new Insets(10, 10, 10, 10));
        allBox.getChildren().addAll(new Label("Monuments table"), MonumentTable, addBox, typesTable);

        ((Group) scene.getRoot()).getChildren().addAll(allBox);

        primaryStage.setScene(scene);
        primaryStage.show();
    }

    @Override
    public void stop() throws Exception {
        DataBase.closeConnectionDB();
    }

    private void createAddBox() {
        final TextField addedName = new TextField();
        addedName.setMaxWidth(preferNameColumnWidth);
        addedName.setPromptText("name");

        final TextField addedType = new TextField();
        addedType.setMaxWidth(preferAgeColumnWidth);
        addedType.setPromptText("type");

        final TextField addedingNumber = new TextField();
        addedingNumber.setMaxWidth(preferingTimeColumnWidth);
        addedingNumber.setPromptText("number");

        ObservableList<String> options =
                FXCollections.observableArrayList(
                        "Historical",
                        "Memorial",
                        "Commemorative"
                );

        final ComboBox<String> typeBox = new ComboBox<>(options);
        typeBox.setPrefWidth(prefertypeColumnWidth + 25);
        typeBox.setPromptText("type");


        final Button addAudioButton = new Button("Add monument");
        addAudioButton.setOnAction((ActionEvent e) -> {
            String type = typeBox.getSelectionModel().getSelectedItem();
            String name = addedName.getText();
            String number = addedingNumber.getText();

            try {
                Monument monument = new Monument(type, name, number);
                if (!amountExists(type)) {
                    String description = showAddingamountDescriptionDialog(type);
                    MonumentType newamount = new MonumentType(type,  description);
                    addTypeToDataBase(newamount);
                    DataBase.MonumentTypesData.add(newamount);
                }
                DataBase.MonumentsData.add(monument);
                addMonumentToDatabase(type, name, number);

                addedType.clear();
                addedName.clear();
                addedingNumber.clear();

            } catch (Exception exc) {
                showAddingError(exc.getMessage());
            }
        });

        addBox.getChildren().addAll(typeBox, addedName, addedingNumber,
                addAudioButton);
    }

    private void showAddingError(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Adding error");
        alert.setHeaderText("Can't add new Monument");
        alert.setContentText(message);
        alert.showAndWait();
    }

    private String showAddingamountDescriptionDialog(String type) {
        TextInputDialog dialog = new TextInputDialog("Enter monument type description");
        dialog.setTitle("Adding new monument type");

        dialog.setHeaderText("You have entered new monument type - '" +
                type +
                "'. \nPlease give some description of this: ");
        Optional<String> result = dialog.showAndWait();
        return result.orElse("no description");
    }

    private void addTypeToDataBase(MonumentType newtype) {
        String sql = "INSERT INTO MonumentTypes(type, description) VALUES(?,?)";
        try (PreparedStatement statement = DataBase.connection.prepareStatement(sql)) {
            statement.setString(1, newtype.getType());
            statement.setString(2, newtype.getDescription());

            statement.executeUpdate();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private boolean amountExists(String newType) {
        for (MonumentType monumentType : DataBase.MonumentTypesData) {
            if (monumentType.getType().equals(newType)) {
                return true;
            }
        }
        return false;
    }

    private void createatypesTable() {
        TableColumn<MonumentType, String> typeColumn = new TableColumn<>("type");
        TableColumn<MonumentType, String> descriptionColumn = new TableColumn<>("description");

        setTypeColumnValues(typeColumn, 200, "type");
        setTypeColumnValues(descriptionColumn, 500, "description");

        typesTable.setItems(DataBase.MonumentTypesData);
        typesTable.getColumns().addAll(typeColumn, descriptionColumn);
        typesTable.setMaxHeight(200);
    }

    private void createMonumentsTable() {
        TableColumn<Monument, String> nameColumn = new TableColumn<>("name");
        TableColumn<Monument, String> numberColumn = new TableColumn<>("number");
        TableColumn<Monument, String> typeColumn = new TableColumn<>("type");

        setMonumentColumnValues(nameColumn, preferNameColumnWidth, "name");
        setMonumentColumnValues(numberColumn, preferAgeColumnWidth, "number");
        setMonumentColumnValues(typeColumn, prefertypeColumnWidth, "type");

        MonumentTable.setItems(DataBase.MonumentsData);
        MonumentTable.getColumns().addAll(typeColumn,nameColumn,numberColumn);
        MonumentTable.setMaxHeight(300);

    }


    private void setTypeColumnValues(TableColumn<MonumentType, String> column, int width, String sqlName) {
        column.setPrefWidth(width);
        column.setCellValueFactory(param -> param.getValue().getFieldBySQL(sqlName));
    }

    private void setMonumentColumnValues(TableColumn<Monument, String> column, int width, String sqlName) {
        column.setPrefWidth(width);
        column.setCellValueFactory(param -> param.getValue().getFieldBySQL(sqlName));
    }

    private void addMonumentToDatabase(String name, String type, String number) {
        String sql = "INSERT INTO Monument(type, name, number) VALUES(?,?,?)";
        try (PreparedStatement statement = DataBase.connection.prepareStatement(sql)) {
            statement.setString(1, type);
            statement.setString(2, name);
            statement.setString(3, number);

            statement.executeUpdate();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

}
