import java.io.*;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.util.ArrayList;
import java.util.List;

public class Client {
    //myServer
    BufferedReader in;
    final Mud.ServerInterface server;
    Mud.ClientInterface player;
    Mud.ClientInterface anotherPlayer;
    List<Integer> myCards = new ArrayList<>();

    public Client(InputStream inputStream) throws IOException, NotBoundException,
            InterruptedException {
        in = new BufferedReader(new InputStreamReader(inputStream));
        String hostname = "localhost";
        String serverName = "myServer";
        int PORT = 2020;
        server = (Mud.ServerInterface) Naming.lookup("rmi://" + hostname
                + ":" + PORT + "/" + serverName);
        System.out.println("You are connected to game server!!!");
        startGame();
    }

    public void printCards() {
        System.out.println("You have: ");
        for (int val : myCards)
            System.out.print(val + " ");
        System.out.println();
    }


    public void startGame() throws InterruptedException, IOException {
        player = new Person( "MyName", new PrintWriter(System.out));
        server.addPlayer(player);

        if (!server.ready()) {
            System.out.println("wait for connecting of second player");
            while (!server.ready()) {
                Thread.sleep(100);
            }
            System.out.println("Second player is connected");
        }
        anotherPlayer = server.getAnotherPlayer(player);
        synchronized (server){
            List<Integer> initCards = server.getCards(player, 2);
            myCards.addAll(initCards);
        }

        printCards();
        State s;
        synchronized (server){
            s = server.getState(player);
            player.changeState();
        }

        while (s == State.CONTINUE) {
            synchronized (server){
                System.out.println("How many cards you want to get?");
                int n = Integer.parseInt(in.readLine());
                myCards.addAll(server.getCards(player, n));
            }
            printCards();

            synchronized (server){
                s = server.getState(player);
                player.changeState();
            }

        }

        if(s==State.WIN)
            System.out.println("You win!!!");
        else
            System.out.println("You lose...");

    }

    public int getSum() {
        return myCards.stream().reduce(0, Integer::sum);
    }

    public static void main(String[] args) {
        try {
            new Client(System.in);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
