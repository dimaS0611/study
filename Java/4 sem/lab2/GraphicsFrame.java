import javax.swing.*;
import java.awt.*;
import java.awt.geom.AffineTransform;


public class GraphicsFrame extends JFrame {

    public static int _win_width = 1600;
    public static int _win_height = 1000;

    void setupframe()
    {
        // Here we create the Frame
        JFrame frame = new JFrame(); // create the frame
        frame.setSize(_win_width,_win_height);
        frame.setLayout(new BorderLayout());
        frame.setResizable(false);

        frame.setTitle("Task1 - 13");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        frame.setContentPane(new DrawPane());
        frame.setVisible(true);
    }

    static class DrawPane extends JPanel
    {
        @Override
        protected void paintComponent(Graphics g)
        {
            super.paintComponent(g);

            Graphics2D g2d = (Graphics2D) g;

            drawRect(g2d);

            final int w2 = _win_width / 2;

            g2d.setTransform(
                    AffineTransform.getTranslateInstance(w2,0)
            );

            g2d.rotate(Math.toRadians(45), w2 / 2, _win_height / 2);
            drawRect(g2d);
        }

        private void drawRect(Graphics2D g2d)
        {
            final int _rect_x = 250;
            final int _rect_y = 250;
            final int _rect_width = 400;
            final int _rect_height = 250;

            Rectangle rect = new Rectangle(_rect_x, _rect_y, _rect_width, _rect_height);

            g2d.setPaint(Color.red);
            g2d.setStroke(new BasicStroke(10.0f));
            g2d.draw(rect);

            GradientPaint gp = new GradientPaint(
                    rect.x, rect.y, Color.white,
                    rect.x, (float) rect.getMaxY(),
                    Color.gray);

            g2d.setPaint(gp);
            g2d.fill(rect);

            g2d.setPaint(Color.red);
            g2d.setFont(new Font("Arial", Font.PLAIN, 100));
            g2d.drawString("STOP", rect.x + (_rect_width / 7.0f), _rect_y + (_rect_height / 1.5f));

            // создание transform для тени
            AffineTransform tr = new AffineTransform();
            tr.translate(rect.x,rect.getMaxY());
            tr.shear(-1.0,+0.0);
            tr.scale(1.0,0.5);
            tr.translate(-rect.x,-rect.y);

            Color shade = new Color(0, 0, 0, 100);
            g2d.setPaint(shade);
            g2d.fill(tr.createTransformedShape(rect));
        }
    }

}
