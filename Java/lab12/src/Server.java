import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Server extends UnicastRemoteObject implements Mud.ServerInterface {
    private static int PORT = 2020;
    Mud.ClientInterface player1, player2;
    static final String SERVER_NAME = "myServer";
    static List<Integer> cards;

    public Server() throws RemoteException, MalformedURLException {
        LocateRegistry.createRegistry(2020); //
        System.setProperty("java.rmi.server.hostname", "127.0.0.1");
        Naming.rebind("rmi://" + Mud.mudPrefix + ":" + PORT + "/" + SERVER_NAME, this);
        System.out.println("Server is working!");
        cards = new ArrayList<>(Arrays.asList
                (2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11));
        Collections.shuffle(cards);
    }

    @Override
    public boolean addPlayer(Mud.ClientInterface player) {
        if(player1 == null)
            player1 = player;
        else if(player2 == null)
            player2 = player;
        else return false;
        return true;
    }

    @Override
    public boolean ready() {
        return player2!=null;
    }


    private boolean flag = true;
    State state1 = State.CONTINUE, state2 = State.CONTINUE;
    int sum1 = 0, sum2 = 0;

    int counter = 0;
    @Override
    public synchronized List<Integer> getCards(Mud.ClientInterface player, int n){
        List<Integer> list = new ArrayList<>();
        for(int i = 0;i<n;i++){
            int x = cards.remove(0);
            list.add(x);
            if(player.equals(player1))
                sum1+=x;
            else
                sum2+=x;
        }

        System.out.println(sum1+" "+sum2);
        return list;
    }

    @Override
    public State getState(Mud.ClientInterface player) throws RemoteException {
        if(sum1==21 && sum2==21)
            return State.WIN;

        if(sum1 > 21 && sum2 <= 21)
            if(player.equals(player1))
                return State.LOSE;
            else
                return State.WIN;

        if(sum1 <= 21 && sum2 > 21)
            if(player.equals(player1))
                return State.WIN;
            else
                return State.LOSE;

        if(sum1<21 && sum2<21)
            return State.CONTINUE;

        if(sum1==21 && sum2!=21)
            if(player.equals(player1))
                return State.WIN;
            else
                return State.LOSE;

        if(sum1!=21 && sum2==21)
            if(player.equals(player1))
                return State.LOSE;
            else
                return State.WIN;

        return State.CONTINUE;
    }

    @Override
    public Mud.ClientInterface getAnotherPlayer(Mud.ClientInterface player) throws RemoteException {
        if(player.equals(player1))
            return player2;
        return player1;
    }

    public static void main(String[] args){
        try {
            new Server();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
