import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface Mud {
    String mudPrefix = "localhost";

    interface ClientInterface extends Remote {
        void changeState() throws RemoteException;
    }

    interface ServerInterface extends Remote {
        boolean addPlayer(ClientInterface player) throws RemoteException;
        boolean ready() throws RemoteException;
        List<Integer> getCards(ClientInterface player, int n) throws RemoteException;
        State getState(ClientInterface player) throws RemoteException;
        ClientInterface getAnotherPlayer(ClientInterface player) throws RemoteException;
    }
}
