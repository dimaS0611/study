import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DataBase {
    public static Connection connection = null;
    public static Statement statement = null;
    public static ResultSet resultSet = null;

    public static ObservableList<Monument> MonumentsData = FXCollections.observableArrayList();
    public static ObservableList<MonumentType> MonumentTypesData = FXCollections.observableArrayList();

    public static void connectionDB()
    {
        try
        {
            connection = DriverManager.getConnection("jdbc:sqlite:E:\\JavaWorkSpace\\УП\\lab7\\src\\Monument.db");
            statement = connection.createStatement();
            statement.setQueryTimeout(30);

            resultSet = statement.executeQuery("select * from Monument;");

            while (resultSet.next()) {
                Monument monument = new Monument(resultSet.getString("type"),
                        resultSet.getString("name"),
                        resultSet.getString("number"));
                MonumentsData.add(monument);
            }

            ResultSet resultSetTypes = statement.executeQuery("select * from MonumentTypes");

            while(resultSetTypes.next())
            {
                MonumentType monumentType = new MonumentType(resultSetTypes.getString("type"),
                        resultSetTypes.getString("description"));
                MonumentTypesData.add(monumentType);
            }
        }
        catch (SQLException ex)
        {
            System.err.println((ex.getMessage()));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void createDB() {
        try {
            statement.execute("CREATE TABLE IF NOT EXISTS 'MonumentTypes' " +
                    "('type' TEXT, " +
                    "'description' TEXT);");

            statement.execute(
                    "CREATE TABLE IF NOT EXISTS 'Monument' " +
                            "('type' TEXT, "  +
                            "'name' TEXT,"+
                            " 'number' TEXT);");

        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public static void closeConnectionDB() {
        try {
            resultSet.close();
            connection.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
