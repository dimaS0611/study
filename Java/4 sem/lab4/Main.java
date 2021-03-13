import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Print graph");

        frame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent ev) {
                System.exit(0);
            }
        });

        Printer printer = new Printer();

        frame.getContentPane().add(printer, BorderLayout.CENTER);
        frame.setSize(400, 170);
        frame.setResizable(false);
        frame.setVisible(true);
    }
}
