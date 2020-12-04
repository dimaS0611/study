import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class Connector {
    private String path = "DB.txt";

    private FileOutputStream _OutputStm;
    {
        try {
            _OutputStm = new FileOutputStream(path);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    private ObjectOutputStream _ObjOutputStm;

    {
        try {
            _ObjOutputStm = new ObjectOutputStream(_OutputStm);
        } catch (IOException e) {
            e.getLocalizedMessage();
        }
    }

    public void save(Object obj)
    {
        try {
            this._ObjOutputStm.writeObject(obj);
            this._ObjOutputStm.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}
