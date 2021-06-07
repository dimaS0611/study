package server;

import java.io.*;
import java.util.HashMap;

public class Writer implements Serializable
{
    public static File mapFile = new File("serializationMap");

    @SuppressWarnings(value="unchecked")
    public HashMap<Integer, String> init() {
        HashMap<Integer, String> map = new HashMap<>();
        if(mapFile.length() != 0) {
            try {
                FileInputStream fis = new FileInputStream(mapFile.getPath());
                ObjectInputStream ois = new ObjectInputStream(fis);
                map = (HashMap<Integer, String>) ois.readObject();
                ois.close();
                fis.close();
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        }

        return map;
    }

    public void save(HashMap<Integer, String> map) throws IOException {
        FileOutputStream fos = new FileOutputStream(mapFile.getPath());
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(map);
        oos.close();
        fos.close();
    }

}
