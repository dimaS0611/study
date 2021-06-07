import java.io.PrintWriter;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Person extends UnicastRemoteObject implements Mud.ClientInterface {
    private String name;
    private PrintWriter out;
    boolean state = false;

    public Person(String name, PrintWriter out) throws RemoteException {
        this.name = name;
        this.out = out;
    }

    @Override
    public void changeState() throws RemoteException {
        if (!state)
            state = true;
        else
            state = false;
    }
}
