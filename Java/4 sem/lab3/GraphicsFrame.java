import javax.swing.*;
import java.awt.*;

class GraphicsFrame extends JFrame {

    public GraphicsFrame() { }

    protected void update() {
        paint(getGraphics());
    }

    public void setupframe() {
        JFrame frame = new JFrame(); // create the frame
        frame.setSize(1500,1500);
        frame.setLayout(new BorderLayout());
        frame.setResizable(false);

        frame.setTitle("Task3 - 13");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        frame.setContentPane(new DrawPane());
        frame.setVisible(true);
    }



}
